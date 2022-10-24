/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/13.
//

#include <limits.h>
#include <string.h>
#include <algorithm>
#include <regex>

#include "common/defs.h"
#include "storage/common/table.h"
#include "storage/common/table_meta.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/default/disk_buffer_pool.h"
#include "storage/record/record_manager.h"
#include "storage/common/condition_filter.h"
#include "storage/common/meta_util.h"
#include "storage/index/index.h"
#include "storage/index/bplus_tree_index.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"

Table::~Table()
{
  if (record_handler_ != nullptr) {
    delete record_handler_;
    record_handler_ = nullptr;
  }

  if (data_buffer_pool_ != nullptr) {
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
  }

  for (std::vector<Index *>::iterator it = indexes_.begin(); it != indexes_.end(); ++it) {
    Index *index = *it;
    delete index;
  }
  indexes_.clear();

  LOG_INFO("Table has been closed: %s", name());
}

RC Table::create(
    const char *path, const char *name, const char *base_dir, int attribute_count, const AttrInfo attributes[], CLogManager *clog_manager)
{

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attribute_count <= 0 || nullptr == attributes) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d, attributes=%p", name, attribute_count, attributes);
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = ::open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR;
  }

  close(fd);

  // 创建文件
  if ((rc = table_meta_.init(name, attribute_count, attributes)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  std::fstream fs;
  fs.open(path, std::ios_base::out | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  std::string data_file = table_data_file(base_dir, name);
  BufferPoolManager &bpm = BufferPoolManager::instance();
  rc = bpm.create_file(data_file.c_str());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create disk buffer pool of data file. file name=%s", data_file.c_str());
    return rc;
  }

  rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to create table %s due to init record handler failed.", data_file.c_str());
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;
  clog_manager_ = clog_manager;
  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC Table::open(const char *meta_file, const char *base_dir, CLogManager *clog_manager)
{
  // 加载元数据文件
  std::fstream fs;
  std::string meta_file_path = std::string(base_dir) + common::FILE_PATH_SPLIT_STR + meta_file;
  fs.open(meta_file_path, std::ios_base::in | std::ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open meta file for read. file name=%s, errmsg=%s", meta_file_path.c_str(), strerror(errno));
    return RC::IOERR;
  }
  if (table_meta_.deserialize(fs) < 0) {
    LOG_ERROR("Failed to deserialize table meta. file name=%s", meta_file_path.c_str());
    fs.close();
    return RC::GENERIC_ERROR;
  }
  fs.close();

  // 加载数据文件
  RC rc = init_record_handler(base_dir);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open table %s due to init record handler failed.", base_dir);
    // don't need to remove the data_file
    return rc;
  }

  base_dir_ = base_dir;

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {
    const IndexMeta *index_meta = table_meta_.index(i);
    const FieldMeta *field_meta = table_meta_.field(index_meta->field());
    if (field_meta == nullptr) {
      LOG_ERROR("Found invalid index meta info which has a non-exists field. table=%s, index=%s, field=%s",
          name(),
          index_meta->name(),
          index_meta->field());
      // skip cleanup
      //  do all cleanup action in destructive Table function
      return RC::GENERIC_ERROR;
    }

    BplusTreeIndex *index = new BplusTreeIndex();
    std::string index_file = table_index_file(base_dir, name(), index_meta->name());
    rc = index->open(index_file.c_str(), *index_meta, *field_meta);
    if (rc != RC::SUCCESS) {
      delete index;
      LOG_ERROR("Failed to open index. table=%s, index=%s, file=%s, rc=%d:%s",
          name(),
          index_meta->name(),
          index_file.c_str(),
          rc,
          strrc(rc));
      // skip cleanup
      //  do all cleanup action in destructive Table function.
      return rc;
    }
    indexes_.push_back(index);
  }

  if (clog_manager_ == nullptr) {
    clog_manager_ = clog_manager;
  }
  return rc;
}
/**
 * @func    destroy
 * @author  czy
 * @date    2022-09-27 07:12
 * @param   base_dir
 * @return  RC
 */
RC Table::destroy(const char *base_dir)
{
  RC rc = sync();
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to sync");
    return rc;
  }

  std::string meta_file_path = table_meta_file(base_dir, name());
  if (unlink(meta_file_path.c_str()) != 0) {
    LOG_ERROR("Failed to remove meta file=%s, errno=%d", meta_file_path.c_str(), errno);
    return RC::GENERIC_ERROR;
  }

  std::string data_file_path = table_data_file(base_dir, name());
  if(unlink(data_file_path.c_str()) != 0) {  // 删除描述表元数据的文件
    LOG_ERROR("Failed to remove data file=%s, errno=%d", data_file_path.c_str(), errno);
    return RC::GENERIC_ERROR;
  }

  // std::string text_data_file = std::string(dir) + "/" + name() + TABLE_TEXT_DATA_SUFFIX;
  // if(unlink(text_data_file.c_str()) != 0) { // 删除表实现text字段的数据文件（后续实现了text case时需要考虑，最开始可以不考虑这个逻辑）
  //     LOG_ERROR("Failed to remove text data file=%s, errno=%d", text_data_file.c_str(), errno);
  //     return RC::GENERIC_ERROR;
  // }

  const int index_num = table_meta_.index_num();
  for (int i = 0; i < index_num; i++) {  // 清理所有的索引相关文件数据与索引元数据
    ((BplusTreeIndex*)indexes_[i])->close();
    const IndexMeta* index_meta = table_meta_.index(i);
    std::string index_file = table_index_file(base_dir, name(), index_meta->name());
    if(unlink(index_file.c_str()) != 0) {
      LOG_ERROR("Failed to remove index file=%s, errno=%d", index_file.c_str(), errno);
      return RC::GENERIC_ERROR;
    }
  }

  return rc;
}
RC Table::commit_insert(Trx *trx, const RID &rid)
{
  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get record %s: %s", this->name(), rid.to_string().c_str());
    return rc;
  }

  return trx->commit_insert(this, record);
}

RC Table::rollback_insert(Trx *trx, const RID &rid)
{

  Record record;
  RC rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to get record %s: %s", this->name(), rid.to_string().c_str());
    return rc;
  }

  // remove all indexes
  rc = delete_entry_of_indexes(record.data(), rid, false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d) while rollback insert, rc=%d:%s",
        rid.page_num,
        rid.slot_num,
        rc,
        strrc(rc));
    return rc;
  }

  rc = record_handler_->delete_record(&rid);
  return rc;
}

RC Table::insert_record(Trx *trx, Record *record)
{
  LOG_TRACE("Enter\n");
  RC rc = RC::SUCCESS;

  if (trx != nullptr) {
    trx->init_trx_info(this, *record);
  }
  rc = record_handler_->insert_record(record->data(), table_meta_.record_size(), &record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->insert_record(this, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to log operation(insertion) to trx");

      RC rc2 = record_handler_->delete_record(&record->rid());
      if (rc2 != RC::SUCCESS) {
        LOG_ERROR("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
            name(),
            rc2,
            strrc(rc2));
      }
      return rc;
    }
  }

  rc = insert_entry_of_indexes(record->data(), record->rid());
  if (rc != RC::SUCCESS) {
    RC rc2 = delete_entry_of_indexes(record->data(), record->rid(), true);
    if (rc2 != RC::SUCCESS) {
      LOG_ERROR("Failed to rollback index data when insert index entries failed. table name=%s, rc=%d:%s",
          name(),
          rc2,
          strrc(rc2));
    }
    rc2 = record_handler_->delete_record(&record->rid());
    if (rc2 != RC::SUCCESS) {
      LOG_PANIC("Failed to rollback record data when insert index entries failed. table name=%s, rc=%d:%s",
          name(),
          rc2,
          strrc(rc2));
    }
    LOG_TRACE("Exit\n");
    return rc;
  }

  if (trx != nullptr) {
    // append clog record
    CLogRecord *clog_record = nullptr;
    rc = clog_manager_->clog_gen_record(CLogType::REDO_INSERT, trx->get_current_id(), clog_record, name(), table_meta_.record_size(), record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a clog record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    rc = clog_manager_->clog_append_record(clog_record);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  return rc;
}

RC Table::recover_insert_record(Record *record)
{
  RC rc = RC::SUCCESS;

  rc = record_handler_->recover_insert_record(record->data(), table_meta_.record_size(), &record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Insert record failed. table name=%s, rc=%d:%s", table_meta_.name(), rc, strrc(rc));
    return rc;
  }

  return rc;
}

RC Table::insert_record(Trx *trx, int value_num, const Value *values)
{
  LOG_TRACE("Enter\n");
  if (value_num <= 0 || nullptr == values) {
    LOG_ERROR("Invalid argument. table name: %s, value num=%d, values=%p", name(), value_num, values);
    return RC::INVALID_ARGUMENT;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  const int field_num = table_meta_.field_num() - normal_field_start_index;
  const int record_length = value_num / field_num;
  // std::cout << "record_length = " << record_length << std::endl;
  Record record_list[record_length];
  for (int i = 0; i < value_num; i += field_num) {
    char *record_data;
    int record_index = i / field_num;

    // temp test code start
    // if (i + field_num == value_num) {
    //   LOG_ERROR("ROLLBACK TEST STARTS...");
    //   for (int j = 0; j < record_index; j++) {
    //     RC delete_rc = delete_record(trx, &record_list[j]);
    //     if (delete_rc != RC::SUCCESS) {
    //       LOG_ERROR("Failed to roll back multiple insert operations");
    //       return delete_rc;
    //     }
    //   }
    //   break;
    // }
    // temp test code end

    RC rc = make_record(field_num, &values[i], record_data);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a record. rc=%d:%s", rc, strrc(rc));
      for (int j = 0; j < record_index; j++) {
        RC delete_rc = delete_record(trx, &record_list[j]);
        if (delete_rc != RC::SUCCESS) {
          LOG_ERROR("Failed to roll back multiple insert operations");
          return delete_rc;
        }
      }
      return rc;
    }

    Record record;
    record.set_data(record_data);
    rc = insert_record(trx, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to insert a record. rc=%d:%s", rc, strrc(rc));
      for (int j = 0; j < record_index; j++) {
        RC delete_rc = delete_record(trx, &record_list[j]);
        if (delete_rc != RC::SUCCESS) {
          LOG_ERROR("Failed to roll back multiple insert operations");
          return delete_rc;
        }
      }
      return rc;
    }
    record_list[record_index] = record;
    delete[] record_data;
  }

  return RC::SUCCESS;
}

const char *Table::name() const
{
  return table_meta_.name();
}

const TableMeta &Table::table_meta() const
{
  return table_meta_;
}
static bool check_date(int y, int m, int d)
{
    static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (y%400==0 || (y%100 && y%4==0));
    return (m > 0)&&(m <= 12)
        && (d > 0)&&(d <= ((m==2 && leap)?1:0) + mon[m]);
}
RC Table::make_record(int value_num, const Value *values, char *&record_out)
{
  LOG_TRACE("Enter\n");
  // 检查字段类型是否一致
  if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
    LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  const int normal_field_start_index = table_meta_.sys_field_num();
  const int field_num = table_meta_.field_num() - normal_field_start_index;
  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i % field_num + normal_field_start_index);
    const Value &value = values[i];
    const AttrType field_type = field->type();
    const AttrType value_type = value.type;
    // hsy add
    // date type transformation and typecast in the future
    LOG_DEBUG("field_type = %d, value_type = %d", field->type(), value.type);
    if (field->type() == DATES && value.type == CHARS) {
      LOG_TRACE("Enter\n");
      std::string str((char*)value.data);
      std::match_results<std::string::iterator> result;
      std::string pattern = "[0-9]{4}\-(0?[1-9]|1[012])\-(0?[1-9]|[12][0-9]|3[01])";
      std::regex r(pattern);
      std::regex_match(str.begin(), str.end(), result, r);
      if(result.size() == 0) {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      continue;
    } 
    if (field->type() != value.type) {
      if (field_type == INTS && value_type == FLOATS ||
      field_type == FLOATS && value_type == INTS ||
      field_type == CHARS && value_type == INTS ||
      field_type == INTS && value_type == CHARS ||
      field_type == FLOATS && value_type == CHARS || 
      field_type == CHARS && value_type == FLOATS) {
        continue;
      }
      LOG_ERROR("Invalid value type. table name =%s, field name=%s, type=%d, but given=%d",
          table_meta_.name(),
          field->name(),
          field->type(),
          value.type);
      return RC::SCHEMA_FIELD_TYPE_MISMATCH;
    }
  }

  // 复制所有字段的值
  int record_size = table_meta_.record_size();
  char *record = new char[record_size];

  for (int i = 0; i < value_num; i++) {
    const FieldMeta *field = table_meta_.field(i % field_num + normal_field_start_index);
    const Value &value = values[i];
    // hsy add
    Value value_for_copy = value;
    size_t copy_len = field->len();
    if (field->type() == CHARS && value.type == CHARS) {
      const size_t data_len = strlen((const char *)value.data);
      if (copy_len > data_len) {
        copy_len = data_len + 1;
      }
    } else if (field->type() == DATES) {
      std::string str((char*)value.data);
      std::match_results<std::string::iterator> result;
      std::string pattern =  "[0-9]{4}\-(0?[1-9]|1[012])\-(0?[1-9]|[12][0-9]|3[01])";
      std::regex r(pattern);
      std::regex_match(str.begin(), str.end(), result, r);
      if(result.size() == 0) {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      std::vector<std::string> date;
      common::split_string(result[0].str(), "-", date);
      if (date.size() != 3) {
        return RC::INVALID_ARGUMENT;
      }
      int y = atoi(date[0].c_str()), m = atoi(date[1].c_str()), d = atoi(date[2].c_str());
      LOG_DEBUG("y: %d, m: %d, d: %d", y, m, d);
      bool b = check_date(y, m, d);
      if (!b) return RC::INVALID_ARGUMENT;
      int data = y * 10000 + m * 100 + d;
      LOG_DEBUG("date = %d", data);
      memcpy(record + field->offset(), &data, sizeof(int));
      continue;
    } else if (field->type() == FLOATS && value.type == INTS) {
      int data = *(int*)value.data;
      *((float*)value_for_copy.data) = data;
    } else if (field->type() == INTS && value.type == FLOATS) {
      float data = *(float*)value.data;
      int num = (int)(data + 0.5);
      *((int*)value_for_copy.data) = num;
    } else if (field->type() == FLOATS && value.type == CHARS) {
      float data = atof((char*)value.data);
      // TODO invalid case
      *((float*)value_for_copy.data) = data;
    } else if (field->type() == INTS && value.type == CHARS) {
      int data = atoi((char*)value.data);
      *((int*)value_for_copy.data) = data;
    } else if (field->type() == CHARS && value.type == INTS) {
      std::string str = std::to_string(*((int*)value.data));
      value_for_copy.data = (void*)str.c_str();
      copy_len = str.size() + 1;
    } else if (field->type() == CHARS && value.type == FLOATS) {
      LOG_TRACE("Enter\n");
      std::string data = std::to_string(*(float*)value.data);
      (value_for_copy.data) = (void*)data.c_str();
      LOG_DEBUG("data = %s", (char*)value_for_copy.data);
      LOG_TRACE("Exit\n");
    }
    memcpy(record + field->offset(), value_for_copy.data, copy_len);
  } 

  record_out = record;
  return RC::SUCCESS;
}

RC Table::init_record_handler(const char *base_dir)
{
  std::string data_file = table_data_file(base_dir, table_meta_.name());

  RC rc = BufferPoolManager::instance().open_file(data_file.c_str(), data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to open disk buffer pool for file:%s. rc=%d:%s", data_file.c_str(), rc, strrc(rc));
    return rc;
  }

  record_handler_ = new RecordFileHandler();
  rc = record_handler_->init(data_buffer_pool_);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to init record handler. rc=%d:%s", rc, strrc(rc));
    data_buffer_pool_->close_file();
    data_buffer_pool_ = nullptr;
    delete record_handler_;
    record_handler_ = nullptr;
    return rc;
  }

  return rc;
}

RC Table::get_record_scanner(RecordFileScanner &scanner)
{
  RC rc = scanner.open_scan(*data_buffer_pool_, nullptr);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
  }
  return rc;
}

/**
 * 为了不把Record暴露出去，封装一下
 */
class RecordReaderScanAdapter {
public:
  explicit RecordReaderScanAdapter(void (*record_reader)(const char *data, void *context), void *context)
      : record_reader_(record_reader), context_(context)
  {}

  void consume(const Record *record)
  {
    record_reader_(record->data(), context_);
  }

private:
  void (*record_reader_)(const char *, void *);
  void *context_;
};

static RC scan_record_reader_adapter(Record *record, void *context)
{
  RecordReaderScanAdapter &adapter = *(RecordReaderScanAdapter *)context;
  adapter.consume(record);
  return RC::SUCCESS;
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter,
		      int limit, void *context,
		      void (*record_reader)(const char *data, void *context))
{
  RecordReaderScanAdapter adapter(record_reader, context);
  return scan_record(trx, filter, limit, (void *)&adapter, scan_record_reader_adapter);
}

RC Table::scan_record(Trx *trx, ConditionFilter *filter, int limit, void *context,
                      RC (*record_reader)(Record *record, void *context))
{
  LOG_TRACE("Enter\n");
  if (nullptr == record_reader) {
    return RC::INVALID_ARGUMENT;
  }

  if (0 == limit) {
    return RC::SUCCESS;
  }

  if (limit < 0) {
    limit = INT_MAX;
  }

  IndexScanner *index_scanner = find_index_for_scan(filter);
  if (index_scanner != nullptr) {
    LOG_TRACE("Scan record by index\n");
    return scan_record_by_index(trx, index_scanner, filter, limit, context, record_reader);
  }

  RC rc = RC::SUCCESS;
  RecordFileScanner scanner;
  rc = scanner.open_scan(*data_buffer_pool_, filter);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("failed to open scanner. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  int record_count = 0;
  Record record;
  LOG_TRACE("before while\n");
  while (scanner.has_next()) {
    rc = scanner.next(record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to fetch next record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    if (trx == nullptr || trx->is_visible(this, &record)) {
      LOG_TRACE("Call record reader\n");
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        break;
      }
      record_count++;
    }
  }

  scanner.close_scan();
  LOG_TRACE("Exit\n");
  return rc;
}

RC Table::scan_record_by_index(Trx *trx, IndexScanner *scanner, ConditionFilter *filter,
                               int limit, void *context,
                               RC (*record_reader)(Record *, void *))
{
  RC rc = RC::SUCCESS;
  RID rid;
  Record record;
  int record_count = 0;
  while (record_count < limit) {
    rc = scanner->next_entry(&rid);
    if (rc != RC::SUCCESS) {
      if (RC::RECORD_EOF == rc) {
        rc = RC::SUCCESS;
        break;
      }
      LOG_ERROR("Failed to scan table by index. rc=%d:%s", rc, strrc(rc));
      break;
    }

    rc = record_handler_->get_record(&rid, &record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to fetch record of rid=%d:%d, rc=%d:%s", rid.page_num, rid.slot_num, rc, strrc(rc));
      break;
    }

    if ((trx == nullptr || trx->is_visible(this, &record)) && (filter == nullptr || filter->filter(record))) {
      rc = record_reader(&record, context);
      if (rc != RC::SUCCESS) {
        LOG_TRACE("Record reader break the table scanning. rc=%d:%s", rc, strrc(rc));
        break;
      }
    }

    record_count++;
  }

  scanner->destroy();
  return rc;
}

class IndexInserter {
public:
  explicit IndexInserter(Index *index) : index_(index)
  {}

  RC insert_index(const Record *record)
  {
    return index_->insert_entry(record->data(), &record->rid());
  }

private:
  Index *index_;
};

static RC insert_index_record_reader_adapter(Record *record, void *context)
{
  IndexInserter &inserter = *(IndexInserter *)context;
  return inserter.insert_index(record);
}

RC Table::create_index(Trx *trx, const char *index_name, const char *attribute_name, const CreateIndex* create_index)
{
  std::string attribute_names_str=std::string(attribute_name);
  for(int i=1;i<create_index->attribute_num;i++){
    attribute_names_str=attribute_names_str+"_"+create_index->attribute_names[create_index->attribute_num-1-i];
  }
  const char* attribute_multi_name=attribute_names_str.c_str();
  
  if (common::is_blank(index_name) || common::is_blank(attribute_name)) {
    LOG_INFO("Invalid input arguments, table name is %s, index_name is blank or attribute_name is blank", name());
    return RC::INVALID_ARGUMENT;
  }
  const FieldMeta *field_meta_multi;
  for(int i=0;i<create_index->attribute_num;i++){
    field_meta_multi=table_meta_.field(create_index->attribute_names[i]);
    if(!field_meta_multi){
      LOG_INFO("Zhenyu multi Invalid input arguments, there is no field of %s in table:%s.", create_index->attribute_names[i], name());
      return RC::SCHEMA_FIELD_MISSING;
    }
  }
  if (table_meta_.index(index_name) != nullptr || table_meta_.find_index_by_multi_field(attribute_multi_name)) {
    LOG_INFO("Invalid input arguments, table name is %s, index %s exist or attribute %s exist index",
             name(), index_name, attribute_multi_name);
    return RC::SCHEMA_INDEX_EXIST;
  }

  const FieldMeta *field_meta = table_meta_.field(attribute_name);
  if (!field_meta) {
    LOG_INFO("Invalid input arguments, there is no field of %s in table:%s.", attribute_name, name());
    return RC::SCHEMA_FIELD_MISSING;
  }

  IndexMeta new_index_meta;
  RC rc = new_index_meta.init(index_name, *field_meta);

  if (rc != RC::SUCCESS) {
    LOG_INFO("Failed to init IndexMeta in table:%s, index_name:%s, field_name:%s",
             name(), index_name, attribute_name);
    return rc;
  }

  // 创建索引相关数据
  BplusTreeIndex *index = new BplusTreeIndex();
  LOG_INFO("index attribute num is %d",create_index->attribute_num);
  std::string index_file = table_index_file(base_dir_.c_str(), name(), index_name);
  LOG_INFO("index attribute num is %d",create_index->attribute_num);
  rc = index->create(index_file.c_str(), new_index_meta, *field_meta);
  LOG_INFO("index attribute num is %d",create_index->attribute_num);
  if (rc != RC::SUCCESS) {
    delete index;
    LOG_ERROR("Failed to create bplus tree index. file name=%s, rc=%d:%s", index_file.c_str(), rc, strrc(rc));
    return rc;
  }

  LOG_INFO("index attribute num is %d",create_index->attribute_num);
  new_index_meta.unique=create_index->unique_flag;
  new_index_meta.attribute_num=0;
  for(int i=0;i<create_index->attribute_num;i++){
    new_index_meta.attribute_name_list[i]=create_index->attribute_names[i];
    new_index_meta.attribute_num+=1;
  }

  // 遍历当前的所有数据，插入这个索引
  IndexInserter index_inserter(index);
  rc = scan_record(trx, nullptr, -1, &index_inserter, insert_index_record_reader_adapter);
  if (rc != RC::SUCCESS) {
    // rollback
    delete index;
    LOG_ERROR("Failed to insert index to all records. table=%s, rc=%d:%s", name(), rc, strrc(rc));
    return rc;
  }
  indexes_.push_back(index);

  TableMeta new_table_meta(table_meta_);
  rc = new_table_meta.add_index(new_index_meta);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to add index (%s) on table (%s). error=%d:%s", index_name, name(), rc, strrc(rc));
    return rc;
  }
  // 创建元数据临时文件
  std::string tmp_file = table_meta_file(base_dir_.c_str(), name()) + ".tmp";
  std::fstream fs;
  fs.open(tmp_file, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
  LOG_INFO("open file");
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", tmp_file.c_str(), strerror(errno));
    return RC::IOERR;  // 创建索引中途出错，要做还原操作
  }
  if (new_table_meta.serialize(fs) < 0) {
    LOG_ERROR("Failed to dump new table meta to file: %s. sys err=%d:%s", tmp_file.c_str(), errno, strerror(errno));
    return RC::IOERR;
  }
  fs.close();
  LOG_INFO("close file");

  // 覆盖原始元数据文件
  std::string meta_file = table_meta_file(base_dir_.c_str(), name());
  int ret = rename(tmp_file.c_str(), meta_file.c_str());
  if (ret != 0) {
    LOG_ERROR("Failed to rename tmp meta file (%s) to normal meta file (%s) while creating index (%s) on table (%s). "
              "system error=%d:%s",
        tmp_file.c_str(),
        meta_file.c_str(),
        index_name,
        name(),
        errno,
        strerror(errno));
    return RC::IOERR;
  }

  table_meta_.swap(new_table_meta);

  LOG_INFO("Successfully added a new index (%s) on the table (%s)", index_name, name());

  return rc;
}
// hsy add
class RecordUpdater {
public:
  RecordUpdater(Table &table, Trx *trx, const char *attribute_name, const Value *value): table_(table), trx_(trx),
  attribute_name_(attribute_name), value_(value)
  {}
  RC update_record(Record *record)
  {
    LOG_TRACE("Enter\n");
    RC rc = RC::SUCCESS;
    // generate new record
    // char *new_record;
    // int values_num = table_.table_meta().field_num();
    // Value values[values_num];
    // const IndexMeta *meta = table_.table_meta().find_index_by_field(attribute_name_);
    const FieldMeta* field_meta = table_.table_meta_.field(attribute_name_);
    int offset = field_meta->offset();
    // table_.make_record(values_num, values, new_record);
    // record->set_data(new_record);
    char* data = record->data();
    size_t copy_len = field_meta->len();
    if (field_meta->type() == CHARS) {
      const size_t data_len = strlen((const char *)value_->data);
      if (copy_len > data_len) {
        copy_len = data_len + 1;
      }
      memcpy(data + offset, value_->data, copy_len);
    } else if (field_meta->type() == DATES) {
      LOG_TRACE("Enter\n");
      std::string str((char*)value_->data);
      std::match_results<std::string::iterator> result;
      std::string pattern =  "[0-9]{4}\-(0?[1-9]|1[012])\-(0?[1-9]|[12][0-9]|3[01])";
      std::regex r(pattern);
      std::regex_match(str.begin(), str.end(), result, r);
      if(result.size() == 0) {
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      std::vector<std::string> date;
      common::split_string(result[0].str(), "-", date);
      if (date.size() != 3) {
        return RC::INVALID_ARGUMENT;
      }
      int y = atoi(date[0].c_str()), m = atoi(date[1].c_str()), d = atoi(date[2].c_str());
      LOG_DEBUG("y: %d, m: %d, d: %d", y, m, d);
      bool b = check_date(y, m, d);
      if (!b) return RC::INVALID_ARGUMENT;
      int date_data = y * 10000 + m * 100 + d;
      LOG_DEBUG("date = %d", data);
      memcpy(data + offset, &date_data, sizeof(int));
    } else {
      memcpy(data + offset, value_->data, copy_len);
    }
    record->set_data(data);
    rc = table_.update_record(trx_, record);
    if (rc == RC::SUCCESS) {
      updated_count_++;
    }
    LOG_TRACE("Exit\n");
    return rc;
  }

  int updated_count() const
  {
    return updated_count_;
  }
private:
  Table &table_;
  Trx *trx_;
  int updated_count_ = 0;
  const char *attribute_name_;
  const Value *value_;

};

// hsy add
static RC record_reader_update_adapter(Record *record, void *context) {
  RecordUpdater &record_updater = *(RecordUpdater *)context;
  return record_updater.update_record(record);
}

RC Table::update_record(Trx *trx, const char *attribute_name, const Value *value, int condition_num,
    const Condition conditions[], int *updated_count)
{
  // hsy add
  if(attribute_name == nullptr || value == nullptr) {
    LOG_ERROR("Invalid argument. table name: %s, attribute name=%s, values=%p", name(), attribute_name, value);
    return RC::INVALID_ARGUMENT;
  }
  RecordUpdater record_updater(*this, trx, attribute_name, value);
  RC rc = RC::SUCCESS;
  if(condition_num == 0) {
    LOG_TRACE("condition num = 0");
    rc = scan_record(trx, nullptr, -1, &record_updater, record_reader_update_adapter);
    if(updated_count != nullptr) {
      *updated_count = record_updater.updated_count();
    }
  } else {
    CompositeConditionFilter filter;
    filter.init(*this, conditions, condition_num);
    LOG_TRACE("start scan record for updating");
    LOG_DEBUG("attribute_name = %s, value:%s", attribute_name, (char*)value->data);
    rc = scan_record(trx, &filter, -1, &record_updater, record_reader_update_adapter);
    if(updated_count != nullptr) {
      *updated_count = record_updater.updated_count();
    }
    LOG_TRACE("after updating, the updated_count = %d", *updated_count);
  }
  return rc;
}
RC Table::update_record(Trx *trx, Record *record/* old record in the page, should be new */) {
  RC rc = RC::SUCCESS;
  if (trx != nullptr) {
    rc = trx->update_record(this, record);
  } else {
    LOG_TRACE("Enter\n");
    rc = update_entry_of_indexes(record->data(), record->rid(), false);  // 重复代码 refer to commit_delete
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to update indexes of record (rid=%d.%d). rc=%d:%s",
                 record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
    } else {
      LOG_TRACE("execute record_handler_'s update_record");
      rc = record_handler_->update_record(record);
    }
  }
  return rc;
}
class RecordDeleter {
public:
  RecordDeleter(Table &table, Trx *trx) : table_(table), trx_(trx)
  {}

  RC delete_record(Record *record)
  {
    RC rc = RC::SUCCESS;
    rc = table_.delete_record(trx_, record);
    if (rc == RC::SUCCESS) {
      deleted_count_++;
    }
    return rc;
  }

  int deleted_count() const
  {
    return deleted_count_;
  }

private:
  Table &table_;
  Trx *trx_;
  int deleted_count_ = 0;
};

static RC record_reader_delete_adapter(Record *record, void *context)
{
  RecordDeleter &record_deleter = *(RecordDeleter *)context;
  return record_deleter.delete_record(record);
}

RC Table::delete_record(Trx *trx, ConditionFilter *filter, int *deleted_count)
{
  RecordDeleter deleter(*this, trx);
  RC rc = scan_record(trx, filter, -1, &deleter, record_reader_delete_adapter);
  if (deleted_count != nullptr) {
    *deleted_count = deleter.deleted_count();
  }
  return rc;
}

RC Table::delete_record(Trx *trx, Record *record)
{
  RC rc = RC::SUCCESS;
  
  rc = delete_entry_of_indexes(record->data(), record->rid(), false);  // 重复代码 refer to commit_delete
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record (rid=%d.%d). rc=%d:%s",
                record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
    return rc;
  } 
  
  rc = record_handler_->delete_record(&record->rid());
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete record (rid=%d.%d). rc=%d:%s",
                record->rid().page_num, record->rid().slot_num, rc, strrc(rc));
    return rc;
  }

  if (trx != nullptr) {
    rc = trx->delete_record(this, record);
    
    CLogRecord *clog_record = nullptr;
    rc = clog_manager_->clog_gen_record(CLogType::REDO_DELETE, trx->get_current_id(), clog_record, name(), 0, record);
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to create a clog record. rc=%d:%s", rc, strrc(rc));
      return rc;
    }
    rc = clog_manager_->clog_append_record(clog_record);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }

  return rc;
}

RC Table::recover_delete_record(Record *record)
{
  RC rc = RC::SUCCESS;
  rc = record_handler_->delete_record(&record->rid());
  
  return rc;
}

RC Table::commit_delete(Trx *trx, const RID &rid)
{
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  rc = delete_entry_of_indexes(record.data(), record.rid(), false);
  if (rc != RC::SUCCESS) {
    LOG_ERROR("Failed to delete indexes of record(rid=%d.%d). rc=%d:%s",
        rid.page_num, rid.slot_num, rc, strrc(rc));  // panic?
  }

  rc = record_handler_->delete_record(&rid);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return rc;
}

RC Table::rollback_delete(Trx *trx, const RID &rid)
{
  RC rc = RC::SUCCESS;
  Record record;
  rc = record_handler_->get_record(&rid, &record);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return trx->rollback_delete(this, record);  // update record in place
}

RC Table::insert_entry_of_indexes(const char *record, const RID &rid)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->insert_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      break;
    }
  }
  return rc;
}

RC Table::delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->delete_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}
// hsy add
RC Table::update_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists)
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->update_entry(record, &rid);
    if (rc != RC::SUCCESS) {
      if (rc != RC::RECORD_INVALID_KEY || !error_on_not_exists) {
        break;
      }
    }
  }
  return rc;
}
Index *Table::find_index(const char *index_name) const
{
  for (Index *index : indexes_) {
    if (0 == strcmp(index->index_meta().name(), index_name)) {
      return index;
    }
  }
  return nullptr;
}
Index *Table::find_index_by_field(const char *field_name) const
{
  const TableMeta &table_meta = this->table_meta();
  const IndexMeta *index_meta = table_meta.find_index_by_field(field_name);
  if (index_meta != nullptr) {
    return this->find_index(index_meta->name());
  }
  return nullptr;
}

IndexScanner *Table::find_index_for_scan(const DefaultConditionFilter &filter)
{
  LOG_TRACE("Enter\n");
  const ConDesc *field_cond_desc = nullptr;
  const ConDesc *value_cond_desc = nullptr;
  if (filter.left().is_attr && !filter.right().is_attr) {
    field_cond_desc = &filter.left();
    value_cond_desc = &filter.right();
  } else if (filter.right().is_attr && !filter.left().is_attr) {
    field_cond_desc = &filter.right();
    value_cond_desc = &filter.left();
  }
  if (field_cond_desc == nullptr || value_cond_desc == nullptr) {
    return nullptr;
  }

  const FieldMeta *field_meta = table_meta_.find_field_by_offset(field_cond_desc->attr_offset);
  if (nullptr == field_meta) {
    LOG_PANIC("Cannot find field by offset %d. table=%s", field_cond_desc->attr_offset, name());
    return nullptr;
  }

  const IndexMeta *index_meta = table_meta_.find_index_by_field(field_meta->name());
  if (nullptr == index_meta) {
    return nullptr;
  }

  Index *index = find_index(index_meta->name());
  if (nullptr == index) {
    return nullptr;
  }
  LOG_TRACE("start compare");
  const char *left_key = nullptr;
  const char *right_key = nullptr;
  int left_len = 4;
  int right_len = 4;
  bool left_inclusive = false;
  bool right_inclusive = false;
  switch (filter.comp_op()) {
  case EQUAL_TO: {
    left_key = (const char *)value_cond_desc->value;
    right_key = (const char *)value_cond_desc->value;
    left_inclusive = true;
    right_inclusive = true;
  }
    break;
  case LESS_EQUAL: {
    right_key = (const char *)value_cond_desc->value;
    right_inclusive = true;
  }
    break;
  case GREAT_EQUAL: {
    left_key = (const char *)value_cond_desc->value;
    left_inclusive = true;
  }
    break;
  case LESS_THAN: {
    right_key = (const char *)value_cond_desc->value;
    right_inclusive = false;
  }
    break;
  case GREAT_THAN: {
    left_key = (const char *)value_cond_desc->value;
    left_inclusive = false;
  }
    break;
  default: {
    return nullptr;
  }
  }

  if (filter.attr_type() == CHARS) {
    left_len = left_key != nullptr ? strlen(left_key) : 0;
    right_len = right_key != nullptr ? strlen(right_key) : 0;
  }
  return index->create_scanner(left_key, left_len, left_inclusive, right_key, right_len, right_inclusive);
}

std::vector<Index *> Table::find_all_index() {

  return indexes_;
}

IndexScanner *Table::find_index_for_scan(const ConditionFilter *filter)
{
  if (nullptr == filter) {
    return nullptr;
  }

  // remove dynamic_cast
  const DefaultConditionFilter *default_condition_filter = dynamic_cast<const DefaultConditionFilter *>(filter);
  if (default_condition_filter != nullptr) {
    return find_index_for_scan(*default_condition_filter);
  }

  const CompositeConditionFilter *composite_condition_filter = dynamic_cast<const CompositeConditionFilter *>(filter);
  if (composite_condition_filter != nullptr) {
    int filter_num = composite_condition_filter->filter_num();
    for (int i = 0; i < filter_num; i++) {
      IndexScanner *scanner = find_index_for_scan(&composite_condition_filter->filter(i));
      if (scanner != nullptr) {
        return scanner;  // 可以找到一个最优的，比如比较符号是=
      }
    }
  }
  return nullptr;
}

RC Table::sync()
{
  RC rc = RC::SUCCESS;
  for (Index *index : indexes_) {
    rc = index->sync();
    if (rc != RC::SUCCESS) {
      LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
          name(), index->index_meta().name(), rc, strrc(rc));
      return rc;
    }
  }
  LOG_INFO("Sync table over. table=%s", name());
  return rc;
}
