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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/table_scan_operator.h"
#include "storage/common/table.h"
#include "rc.h"

RC TableScanOperator::open()
{
  // hsy add
  LOG_TRACE("Enter\n");
  RC rc = RC::SUCCESS;
  for (int i = 0; i < tables_.size(); i++) {
    rc = tables_[i]->get_record_scanner(*record_scanners_[i]);
  }
  if (rc == RC::SUCCESS) {
    for (int i = 0; i < tables_.size(); i++) {
      tuples_[i]->set_schema(tables_[i], tables_[i]->table_meta().field_metas());
    }
    for (int i = 0; i < tables_.size(); i++) {
      if (record_scanners_[i]->has_next()) {
        rc = record_scanners_[i]->next(*current_record_[i]);
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }
  LOG_TRACE("Exit\n");
  return rc;
}

RC TableScanOperator::next()
{
  LOG_TRACE("Enter\n");
  if (!record_scanners_[0]->has_next()) {
    return RC::RECORD_EOF;
  }
  const int size = tables_.size();
  int index = tables_.size() - 1;
  while(index >= 0) {
    if (record_scanners_[index]->has_next()) {
      break;
    } else {
      index--;
    }
  }
  RC rc = RC::SUCCESS;
  for (int i = index + 1; i < size; i++) {
    record_scanners_[i]->close_scan();
    rc = tables_[i]->get_record_scanner(*record_scanners_[i]);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  rc = record_scanners_[index]->next(*current_record_[index]);
  // RC rc = record_scanners_[index]->next(current_record_);
  LOG_TRACE("Exit\n");
  return rc;
}

RC TableScanOperator::close()
{
  for (int i = 0; i < record_scanners_.size(); i++) {
    (*record_scanners_[i]).close_scan();
  }
  return RC::SUCCESS;
}

Tuple * TableScanOperator::current_tuple()
{
  LOG_TRACE("Enter\n");
  for (int i = 0; i < tuples_.size(); i++) {
    tuples_[i]->set_record(current_record_[i]);
  }
  // create a temporary table stored in the memory
  table_ = new Table();
  RC rc = RC::SUCCESS;
  int attribute_count = 0;
  AttrInfo attr_info[1000];
  std::vector<FieldMeta> field_metas;
  for (int i = 0; i < tables_.size(); i++) {
    const TableMeta &table_meta = tables_[i]->table_meta();
    int index = 0;
    const std::vector<FieldMeta>* fields = table_meta.field_metas();
    while (index < table_meta.field_num()) {
      AttrInfo info = {.name = const_cast<char*>((*fields)[index].name()), 
      .type = (*fields)[index].type(), 
      .length = (*fields)[index].len()};
      attr_info[attribute_count] = info;
      field_metas.push_back((*fields)[index]);
      attribute_count++;
      index++;
    }
  }
  rc = table_->create_temporary("tmp", attribute_count, attr_info);
  tuple_.set_schema(table_, &field_metas);
  char* data;
  table_->merge_records(tables_, current_record_, data);
  record_.set_data(data);
  tuple_.set_record(&record_);
  LOG_TRACE("Exit\n");
  return &tuple_;
}
// RC TableScanOperator::tuple_cell_spec_at(int index, TupleCellSpec &spec) const
// {
//   return tuple_.cell_spec_at(index, spec);
// }
