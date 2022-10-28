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
// Created by Meiyi & Longda on 2021/4/13.
//

#include <string>
#include <sstream>

#include "execute_stage.h"

#include "common/io/io.h"
#include "common/log/log.h"
#include "common/lang/defer.h"
#include "common/seda/timer_stage.h"
#include "common/lang/string.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/expr/tuple.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/join_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/update_operator.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/table.h"
#include "storage/common/field.h"
#include "storage/index/index.h"
#include "storage/default/default_handler.h"
#include "storage/common/condition_filter.h"
#include "storage/trx/trx.h"
#include "storage/clog/clog.h"

using namespace common;

//RC create_selection_executor(
//   Trx *trx, const Selects &selects, const char *db, const char *table_name, SelectExeNode &select_node);

//! Constructor
ExecuteStage::ExecuteStage(const char *tag) : Stage(tag)
{}

//! Destructor
ExecuteStage::~ExecuteStage()
{}

//! Parse properties, instantiate a stage object
Stage *ExecuteStage::make_stage(const std::string &tag)
{
  ExecuteStage *stage = new (std::nothrow) ExecuteStage(tag.c_str());
  if (stage == nullptr) {
    LOG_ERROR("new ExecuteStage failed");
    return nullptr;
  }
  stage->set_properties();
  return stage;
}

//! Set properties for this object set in stage specific properties
bool ExecuteStage::set_properties()
{
  //  std::string stageNameStr(stageName);
  //  std::map<std::string, std::string> section = theGlobalProperties()->get(
  //    stageNameStr);
  //
  //  std::map<std::string, std::string>::iterator it;
  //
  //  std::string key;

  return true;
}

//! Initialize stage params and validate outputs
bool ExecuteStage::initialize()
{
  LOG_TRACE("Enter");

  std::list<Stage *>::iterator stgp = next_stage_list_.begin();
  default_storage_stage_ = *(stgp++);
  mem_storage_stage_ = *(stgp++);

  LOG_TRACE("Exit");
  return true;
}

//! Cleanup after disconnection
void ExecuteStage::cleanup()
{
  LOG_TRACE("Enter");

  LOG_TRACE("Exit");
}

void ExecuteStage::handle_event(StageEvent *event)
{
  LOG_TRACE("Enter\n");

  handle_request(event);

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::callback_event(StageEvent *event, CallbackContext *context)
{
  LOG_TRACE("Enter\n");

  // here finish read all data from disk or network, but do nothing here.

  LOG_TRACE("Exit\n");
  return;
}

void ExecuteStage::handle_request(common::StageEvent *event)
{
  LOG_TRACE("Enter\n");
  SQLStageEvent *sql_event = static_cast<SQLStageEvent *>(event);
  SessionEvent *session_event = sql_event->session_event();
  Stmt *stmt = sql_event->stmt();
  Session *session = session_event->session();
  Query *sql = sql_event->query();

  if (stmt != nullptr) {
    switch (stmt->type()) {
    case StmtType::SELECT: {
      do_select(sql_event);
    } break;
    case StmtType::INSERT: {
      do_insert(sql_event);
    } break;
    case StmtType::UPDATE: {
      //do_update((UpdateStmt *)stmt, session_event);
      do_update(sql_event);
    } break;
    case StmtType::DELETE: {
      do_delete(sql_event);
    } break;
    default: {
      LOG_WARN("should not happen. please implenment");
    } break;
    }
  } else {
    switch (sql->flag) {
    case SCF_HELP: {
      do_help(sql_event);
    } break;
    case SCF_CREATE_TABLE: {
      do_create_table(sql_event);
    } break;
    case SCF_CREATE_INDEX: {
      do_create_index(sql_event);
    } break;
    case SCF_SHOW_TABLES: {
      do_show_tables(sql_event);
    } break;
    case SCF_DESC_TABLE: {
      do_desc_table(sql_event);
    } break;

    case SCF_DROP_TABLE: {
      do_drop_table(sql_event);
      break;
    }
    case SCF_DROP_INDEX:
    case SCF_SHOW_INDEX:{
      LOG_TRACE("enter case switch show index\n");
      do_show_index(sql_event);
    } break;
    case SCF_LOAD_DATA: {
      default_storage_stage_->handle_event(event);
    } break;
    case SCF_SYNC: {
      /*
      RC rc = DefaultHandler::get_default().sync();
      session_event->set_response(strrc(rc));
      */
    } break;
    case SCF_BEGIN: {
      do_begin(sql_event);
      /*
      session_event->set_response("SUCCESS\n");
      */
    } break;
    case SCF_COMMIT: {
      do_commit(sql_event);
      /*
      Trx *trx = session->current_trx();
      RC rc = trx->commit();
      session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
      */
    } break;
    case SCF_CLOG_SYNC: {
      do_clog_sync(sql_event);
    }
    case SCF_ROLLBACK: {
      Trx *trx = session_event->get_client()->session->current_trx();
      RC rc = trx->rollback();
      session->set_trx_multi_operation_mode(false);
      session_event->set_response(strrc(rc));
    } break;
    case SCF_EXIT: {
      // do nothing
      const char *response = "Unsupported\n";
      session_event->set_response(response);
    } break;
    default: {
      LOG_ERROR("Unsupported command=%d\n", sql->flag);
    }
    }
  }
}

void end_trx_if_need(Session *session, Trx *trx, bool all_right)
{
  if (!session->is_trx_multi_operation_mode()) {
    if (all_right) {
      trx->commit();
    } else {
      trx->rollback();
    }
  }
}

void print_tuple_header(std::ostream &os, const ProjectOperator &oper, bool is_multi_table)
{
  LOG_TRACE("Enter\n");
  const int cell_num = oper.tuple_cell_num();
  const TupleCellSpec *cell_spec = nullptr;
  for (int i = 0; i < cell_num; i++) {
    oper.tuple_cell_spec_at(i, cell_spec);
    if (i != 0) {
      os << " | ";
    }

    if (cell_spec->alias().size() > 0) {
      if (is_multi_table) {
        os << cell_spec->alias();
      } else {
        std::vector<std::string> names;
        common::split_string(cell_spec->alias(), ".", names);
        os << names.back().c_str();
      }
    }
  }

  if (cell_num > 0) {
    os << '\n';
  }
  LOG_TRACE("Exit\n");
}

void print_aggr_tuple_header(std::ostream &os, const ProjectOperator &oper, std::vector<char *> aggr_funcs)
{
  const int cell_num = oper.tuple_cell_num();
  const TupleCellSpec *cell_spec = nullptr;
  int cell_index = cell_num - 1;
  for (int i = aggr_funcs.size() - 1; i >= 0; i--) {
    if (i != aggr_funcs.size() - 1) {
      os << " | ";
    }
    if (0 == strncmp(aggr_funcs[i], "COUNT(", 6)) {
      os << aggr_funcs[i];
      continue;
    }
    oper.tuple_cell_spec_at(cell_index--, cell_spec);

    if (cell_spec->alias().size() > 0) {
      os << aggr_funcs[i];
      os << "(";
      os << cell_spec->alias().c_str();
      os << ")";
    }
  }

  if (aggr_funcs.size() > 0) {
    os << '\n';
  }
}

void tuplecell_list_to_string(std::ostream &os, std::vector<TupleCell> tuple_cells) {
  bool first_field = true;
  for (int i = tuple_cells.size() - 1; i >= 0; i--) {
    TupleCell cell = tuple_cells[i];
    if (!first_field) {
      os << " | ";
    } else {
      first_field = false;
    }
    cell.to_string(os);
  }
}

void tuple_to_string(std::ostream &os, const Tuple &tuple)
{
  LOG_TRACE("Enter\n");
  TupleCell cell;
  RC rc = RC::SUCCESS;
  bool first_field = true;
  LOG_DEBUG("tuple cell_num = %d", tuple.cell_num());
  for (int i = 0; i < tuple.cell_num(); i++) {
    LOG_TRACE("before cell at");
    rc = tuple.cell_at(i, cell);
    LOG_TRACE("after cell at");
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", i, strrc(rc));
      break;
    }

    if (!first_field) {
      os << " | ";
    } else {
      first_field = false;
    }
    cell.to_string(os);
  }
}

IndexScanOperator *try_to_create_index_scan_operator(FilterStmt *filter_stmt)
{
  LOG_TRACE("Enter\n");
  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  if (filter_units.empty() ) {
    return nullptr;
  }

  // 在所有过滤条件中，找到字段与值做比较的条件，然后判断字段是否可以使用索引
  // 如果是多列索引，这里的处理需要更复杂。
  // 这里的查找规则是比较简单的，就是尽量找到使用相等比较的索引
  // 如果没有就找范围比较的，但是直接排除不等比较的索引查询. (你知道为什么?)
  const FilterUnit *better_filter = nullptr;
  for (const FilterUnit * filter_unit : filter_units) {
    if (filter_unit->comp() == NOT_EQUAL) {
      continue;
    }

    Expression *left = filter_unit->left();
    Expression *right = filter_unit->right();
    if (left->type() == ExprType::FIELD && right->type() == ExprType::VALUE) {
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
      std::swap(left, right);
    } else if (left->type() == ExprType::VALUE && right->type() == ExprType::VALUE) { // hsy add
      return nullptr;
    }
    FieldExpr &left_field_expr = *(FieldExpr *)left;
    const Field &field = left_field_expr.field();
    const Table *table = field.table();
    Index *index = table->find_index_by_field(field.field_name());
    if (index != nullptr) {
      if (better_filter == nullptr) {
        better_filter = filter_unit;
      } else if (filter_unit->comp() == EQUAL_TO) {
        better_filter = filter_unit;
    	break;
      }
    }
  }

  if (better_filter == nullptr) {
    return nullptr;
  }

  Expression *left = better_filter->left();
  Expression *right = better_filter->right();
  CompOp comp = better_filter->comp();
  if (left->type() == ExprType::VALUE && right->type() == ExprType::FIELD) {
    std::swap(left, right);
    switch (comp) {
    case EQUAL_TO:    { comp = EQUAL_TO; }    break;
    case LESS_EQUAL:  { comp = GREAT_THAN; }  break;
    case NOT_EQUAL:   { comp = NOT_EQUAL; }   break;
    case LESS_THAN:   { comp = GREAT_EQUAL; } break;
    case GREAT_EQUAL: { comp = LESS_THAN; }   break;
    case GREAT_THAN:  { comp = LESS_EQUAL; }  break;
    default: {
    	LOG_WARN("should not happen");
    }
    }
  }


  FieldExpr &left_field_expr = *(FieldExpr *)left;
  const Field &field = left_field_expr.field();
  const Table *table = field.table();
  Index *index = table->find_index_by_field(field.field_name());
  assert(index != nullptr);

  ValueExpr &right_value_expr = *(ValueExpr *)right;
  TupleCell value;
  right_value_expr.get_tuple_cell(value);

  const TupleCell *left_cell = nullptr;
  const TupleCell *right_cell = nullptr;
  bool left_inclusive = false;
  bool right_inclusive = false;

  switch (comp) {
  case EQUAL_TO: {
    left_cell = &value;
    right_cell = &value;
    left_inclusive = true;
    right_inclusive = true;
  } break;

  case LESS_EQUAL: {
    left_cell = nullptr;
    left_inclusive = false;
    right_cell = &value;
    right_inclusive = true;
  } break;

  case LESS_THAN: {
    left_cell = nullptr;
    left_inclusive = false;
    right_cell = &value;
    right_inclusive = false;
  } break;

  case GREAT_EQUAL: {
    left_cell = &value;
    left_inclusive = true;
    right_cell = nullptr;
    right_inclusive = false;
  } break;

  case GREAT_THAN: {
    left_cell = &value;
    left_inclusive = false;
    right_cell = nullptr;
    right_inclusive = false;
  } break;

  default: {
    LOG_WARN("should not happen. comp=%d", comp);
  } break;
  }

  IndexScanOperator *oper = new IndexScanOperator(table, index,
       left_cell, left_inclusive, right_cell, right_inclusive);

  LOG_INFO("use index for scan: %s in table %s", index->index_meta().name(), table->name());
  return oper;
}

static RC check_select_meta(SelectStmt *select_stmt) {
  LOG_TRACE("Enter\n");
  RC rc = RC::SUCCESS;
  std::vector<Table*> tables;
  for (Table* table: select_stmt->tables()) {
    tables.emplace_back(table);
    std::string table_name(table->name());
    std::string path = "./miniob/db/sys/" + table_name + ".data";
    int fd = ::open(path.c_str(), O_RDONLY);
    if (fd < 0) {
      rc = RC::INVALID_ARGUMENT;
      return rc;
    }
    close(fd);
  }

  BufferPoolManager &bpm = BufferPoolManager::instance();
  DiskBufferPool *buffer_pool;
  std::unordered_set<std::string> field_names;
  for (Table* table: tables) {
    TableMeta table_meta = table->table_meta();
    const std::vector<FieldMeta> *field_metas = table_meta.field_metas();
    std::string table_name(table->name());
    for (FieldMeta meta: (*field_metas)) {
      std::string meta_name(meta.name());
      field_names.insert(table_name + meta_name);
    }
  }
  std::vector<Field> fields = select_stmt->query_fields();
  for (Field field: fields) {
    std::string table_name(field.table_name());
    std::string field_name(field.field_name());
    if(field_names.find(table_name + field_name) == field_names.end()) {
      rc = RC::INVALID_ARGUMENT;
      break;
    }
  }
  LOG_TRACE("Exit\n");
  return rc;
}

RC do_aggregation(SQLStageEvent *sql_event, ProjectOperator &project_oper) {
  LOG_INFO("DO AGGREGATION 1 1 1!! !! !!");
  RC rc = RC::SUCCESS;
  std::stringstream ss;
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  const int cell_num = project_oper.tuple_cell_num();
  // 新建vector <> aggr_funcs, 存储除了COUNT(1)/COUNT(*)以外的聚合函数
  std::vector <char *> aggr_funcs;
  for (int i = 0; i < select_stmt->aggr_funcs().size(); i++) {
    char *aggr_func = select_stmt->aggr_funcs()[i];
    if (0 != strncmp(aggr_func, "COUNT(", 6))
      aggr_funcs.push_back(aggr_func);
  }
  if (aggr_funcs.size() != cell_num) {
    LOG_WARN("aggr_funcs.size() = %d, but cell_num = %d", aggr_funcs.size(), cell_num);
    return RC::SQL_SYNTAX;
  }
  print_aggr_tuple_header(ss, project_oper, select_stmt->aggr_funcs());
  
  LOG_INFO("DO AGGREGATION 2 2 2!! !! !!");
  int tuple_num = 0;
  bool first_tuple = true;
  std::vector <TupleCell> aggr_result;
  while ((rc = project_oper.next()) == RC::SUCCESS) {
    // get current record
    // write to response
    tuple_num ++;
    LOG_INFO("tuple_index = %d", tuple_num);
    Tuple * tuple = project_oper.current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }
    TupleCell cell;
    int *int_cur_sum = new int;
    float *cur_sum = new float;
    float *cell_data = new float;
    int cell_index = 0;
    for (int i = 0; i < select_stmt->aggr_funcs().size(); i++) {
      char *aggr_func = select_stmt->aggr_funcs()[i];
      if (0 == strncmp(aggr_func, "COUNT(", 6)) {
        if (first_tuple) {
          TupleCell *tmp = new TupleCell();
          aggr_result.push_back(*tmp);
        }
        continue;
      }
      RC rc_cell = tuple->cell_at(cell_index++, cell);
      if (rc_cell != RC::SUCCESS) {
        LOG_WARN("failed to fetch field of cell. index=%d, rc=%s", i, strrc(rc));
        return rc_cell;
      }
      if (first_tuple) {
        aggr_result.push_back(cell);
      } 
      else {
        if (0 == strcmp(aggr_func, "MAX")) {
          TupleCell ans_cell = aggr_result[i];
          if (ans_cell.compare(cell) < 0)
            aggr_result[i] = cell;
        } else if (0 == strcmp(aggr_func, "MIN")) {
          TupleCell ans_cell = aggr_result[i];
          if (ans_cell.compare(cell) > 0)
            aggr_result[i] = cell;
        } else if (0 == strcmp(aggr_func, "SUM") || 0 == strcmp(aggr_func, "AVG")) {

          TupleCell ans_cell = aggr_result[i];
          if (ans_cell.attr_type() != INTS && ans_cell.attr_type() != FLOATS && ans_cell.attr_type() != CHARS)
            return RC::INVALID_ARGUMENT;

          // LOG_WARN("HERE 1......");
          switch(ans_cell.attr_type()) {
            case INTS: *cur_sum = *(int *)ans_cell.data(); break;
            case FLOATS: *cur_sum = *(float *)ans_cell.data(); break;
            case CHARS: *cur_sum = atof(ans_cell.data()); break;
            default: return RC::INVALID_ARGUMENT;
          }
          // LOG_WARN("HERE 2......");
          switch(cell.attr_type()) {
            case INTS: *cell_data = *(int *)cell.data(); break;
            case FLOATS: *cell_data = *(float *)cell.data(); break;
            case CHARS: *cell_data = atof(cell.data());break;
            default: return RC::INVALID_ARGUMENT;
          }

          *cur_sum += *cell_data;
          LOG_INFO("cur_sum = %.2lf, cell_data = %.2lf", *cur_sum, *cell_data);
          switch (ans_cell.attr_type()) {
            case INTS: {*int_cur_sum = *cur_sum; ans_cell.set_data((char *)int_cur_sum);} break;
            case FLOATS: {ans_cell.set_data((char *)cur_sum);} break;
            case CHARS: {ans_cell.set_type(FLOATS); ans_cell.set_data((char *)cur_sum);} break;
          }
          aggr_result[i] = ans_cell;
        } else if (0 == strcmp(aggr_func, "COUNT")) {
          continue;
        }
        else return RC::INVALID_ARGUMENT;
          
      } 
    }
  
    first_tuple = false;
  }

  LOG_INFO("tuple_num = %d", tuple_num);
  // 处理空表情况 default=0, TODO: 改为非INT类型
  if (tuple_num == 0) {
    for (int i = 0; i < aggr_result.size(); i++) {
      char *aggr_func = select_stmt->aggr_funcs()[i];
      TupleCell cell;
      int *data = new int;
      *data = 0;
      cell.set_type(INTS);
      cell.set_data((char *)data);
    }
  }
  // 处理空表结束

  for (int i = 0; i < aggr_result.size(); i++) {
    TupleCell cell = aggr_result[i];
    char *aggr_func = select_stmt->aggr_funcs()[i];
    if (0 == strncmp(aggr_func, "COUNT", 5)) {
      int *count = new int;
      *count = tuple_num;
      LOG_INFO("COUNT = %d", *count);
      cell.set_type(INTS);
      cell.set_data((char *)count);
      aggr_result[i] = cell;
    }
    else if (0 == strcmp(aggr_func, "AVG")) {
      float sum = 0;
      if (cell.attr_type() == INTS) sum = *(int *)cell.data();
      else sum = *(float *)cell.data();
      float *avg = new float;
      *avg = sum / tuple_num;
      LOG_INFO("AVERAGE = %.2lf", *avg);
      cell.set_type(FLOATS);
      cell.set_data((char *)avg);
      aggr_result[i] = cell;
    }
  }
  // apply_aggr_to_tuple(select_stmt, *tuple);
  tuplecell_list_to_string(ss, aggr_result);
  ss << std::endl;
  

  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    project_oper.close();
  } else {
    rc = project_oper.close();
  }
  session_event->set_response(ss.str());
  return rc;
}

RC ExecuteStage::do_select(SQLStageEvent *sql_event)
{
  LOG_TRACE("Enter\n");
  LOG_INFO("Enter DO_SELECT!!!");
  SelectStmt *select_stmt = (SelectStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;
  // if (select_stmt->tables().size() != 1) {
  //   LOG_WARN("select more than 1 tables is not supported");
  //   rc = RC::UNIMPLENMENT;
  //   return rc;
  // }
  
  rc = check_select_meta(select_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("check select meta failed!");
    return rc;
  }
  bool is_multi_table = select_stmt->tables().size() > 1;
  Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
  std::vector<Operator*> scan_ops;
  if (nullptr == scan_oper) {
    scan_oper = new TableScanOperator(select_stmt->tables()[0]);
  }
  if (is_multi_table) {
    for (int i = 0; i < select_stmt->tables().size(); i++) {
      scan_ops.push_back(new TableScanOperator(select_stmt->tables()[i]));
    }
    LOG_DEBUG("table num = %d", select_stmt->tables().size());
  }
  LOG_INFO("BEFORE DEFER ... is_aggr = %d", (int)select_stmt->is_aggregation());
  // if (!is_multi_table) {
  //   DEFER([&] () {delete scan_oper;});
  // } else {
  //   for (int i = 0; i < select_stmt->tables().size(); i++) {
  //     DEFER([&] () {delete scan_ops[i];});
  //   }
  // }
  LOG_TRACE("Before initialize pred_oper");
  PredicateOperator pred_oper(select_stmt->filter_stmt());
  if (!is_multi_table) {
    LOG_TRACE("Enter\n");
    pred_oper.add_child(scan_oper);
  } else {
    LOG_TRACE("Enter\n");
    JoinOperator* join_oper = new JoinOperator(scan_ops[0], scan_ops[1]);
    JoinOperator* final_join_oper = join_oper;
    for (int i = 2; i < select_stmt->tables().size(); i++) {
      JoinOperator *new_join = new JoinOperator(join_oper, scan_ops[i]);
      final_join_oper = new_join;
      join_oper = final_join_oper;
    }
    
    pred_oper.add_child(final_join_oper);
  }
  LOG_TRACE("Before proj oper\n");
  ProjectOperator project_oper;
  project_oper.add_child(&pred_oper);
  for (const Field &field : select_stmt->query_fields()) {
    project_oper.add_projection(field.table(), field.meta());
  }
  rc = project_oper.open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open operator");
    return rc;
  }
  LOG_TRACE("Before Agg check\n");
  if (select_stmt->is_aggregation() == true) {
    rc = do_aggregation(sql_event, project_oper);
    if (rc != RC::SUCCESS) {
      session_event->set_response("FAILURE\n");
    }
    return rc;
  }

  std::stringstream ss;
  LOG_TRACE("Before print");
  print_tuple_header(ss, project_oper, is_multi_table);
  while ((rc = project_oper.next()) == RC::SUCCESS) {
    // get current record
    // write to response
    LOG_TRACE("Get tuple\n");
    Tuple * tuple = project_oper.current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get current record. rc=%s", strrc(rc));
      break;
    }
    LOG_TRACE("TO_STRING\n");
    tuple_to_string(ss, *tuple);
    ss << std::endl;
  }

  if (rc != RC::RECORD_EOF) {
    LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
    project_oper.close();
  } else {
    rc = project_oper.close();
  }
  session_event->set_response(ss.str());
  return rc;
}

// hsy add
RC ExecuteStage::do_update(SQLStageEvent *sql_event)
{
  if (sql_event->stmt() == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }
  UpdateStmt *update_stmt = (UpdateStmt *)(sql_event->stmt());
  SessionEvent *session_event = sql_event->session_event();
  RC rc = RC::SUCCESS;
  if (update_stmt->table() == nullptr) {
    LOG_WARN("target table for updating does not exist.");
    rc = RC::INVALID_ARGUMENT;
    session_event->set_response("FAILURE\n");
    return rc;
  }
  std::string table_name = update_stmt->table()->name();
  BufferPoolManager &bpm = BufferPoolManager::instance();
  DiskBufferPool *buffer_pool;
  std::string path = "./miniob/db/sys/" + table_name + ".data";
  int fd = ::open(path.c_str(), O_RDONLY);
  if (fd < 0) {
    rc = RC::INVALID_ARGUMENT;
    session_event->set_response("FAILURE\n");
    return rc;
  }
  close(fd);
  Table *table = update_stmt->table();
  TableMeta table_meta = table->table_meta();
  std::unordered_set<std::string> field_names;
  const std::vector<FieldMeta> *field_metas = table_meta.field_metas();
  for (FieldMeta meta: (*field_metas)) {
    field_names.insert(meta.name());
  }
  if (field_names.find(update_stmt->attribute_name()) == field_names.end()) {
    LOG_WARN("invalid target column: %s", update_stmt->attribute_name());
    rc = RC::INVALID_ARGUMENT;
    session_event->set_response("FAILURE\n");
    return rc;
  }
  Condition* conditions = update_stmt->conditions();
  int condition_num = update_stmt->value_amount();
  LOG_TRACE("condition_num = %d", condition_num);
  for (int i = 0; i < condition_num; i++) {
    LOG_TRACE("condition judge:i = %d", i);
    const Condition condition = conditions[i];
    if (field_names.find(condition.left_attr.attribute_name) == field_names.end()) {
      rc = RC::INVALID_ARGUMENT;
      session_event->set_response("FAILURE\n");
      return rc;
    } 
  }
  LOG_DEBUG("try to create scan_oper");
  Operator *scan_oper = try_to_create_index_scan_operator(update_stmt->filter_stmt());
  if (nullptr == scan_oper) {
    LOG_DEBUG("create index scan operator failed, start to create table scan operator");
    scan_oper = new TableScanOperator(update_stmt->table());
  }

  DEFER([&] () {delete scan_oper;});
  LOG_DEBUG("create pred_oper");
  PredicateOperator pred_oper(update_stmt->filter_stmt());
  pred_oper.add_child(scan_oper);
  UpdateOperator update_oper(update_stmt);
  update_oper.add_child(&pred_oper);
  rc = update_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }
  return rc;
}

RC ExecuteStage::do_help(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  const char *response = "show tables;\n"
                         "desc `table name`;\n"
                         "create table `table name` (`column name` `column type`, ...);\n"
                         "create index `index name` on `table` (`column`);\n"
                         "insert into `table` values(`value1`,`value2`);\n"
                         "update `table` set column=value [where `column`=`value`];\n"
                         "delete from `table` [where `column`=`value`];\n"
                         "select [ * | `columns` ] from `table`;\n";
  session_event->set_response(response);
  return RC::SUCCESS;
}

RC ExecuteStage::do_create_table(SQLStageEvent *sql_event)
{
  const CreateTable &create_table = sql_event->query()->sstr.create_table;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  RC rc = db->create_table(create_table.relation_name,
			create_table.attribute_count, create_table.attributes);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}
RC ExecuteStage::do_create_index(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  const CreateIndex &create_index = sql_event->query()->sstr.create_index;
  LOG_INFO("num is %d",create_index.attribute_num);
  Table *table = db->find_table(create_index.relation_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SUCCESS;
  }
  RC rc = table->create_index(nullptr, create_index.index_name, create_index.attribute_name, &create_index);
  sql_event->session_event()->set_response(rc == RC::SUCCESS ? "SUCCESS\n" : "FAILURE\n");
  return rc;
}

RC ExecuteStage::do_show_index(SQLStageEvent *sql_event){
  LOG_TRACE("enter do show index\n");
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  const ShowIndex &show_index=sql_event->query()->sstr.show_index;
  Table* table=db->find_table(show_index.table_name);
  if (nullptr == table) {
    session_event->set_response("FAILURE\n");
    return RC::SUCCESS;
  }
  const TableMeta tableMeta=table->table_meta();
  std::vector<Index *> all_indexes;
  all_indexes=table->find_all_index();
  const char* response="TABLE | NON_UNIQUE | KEY_NAME | SEQ_IN_INDEX | COLUMN_NAME";

  std::stringstream ss;
  int j;
  int i;
  if(table==nullptr){
    sql_event->session_event()->set_response("FAILURE\n");
    return RC::SUCCESS;
  }
  ss<<response<<std::endl;
  for(j=0;j<tableMeta.index_num();j++){
    const IndexMeta* cur_index=tableMeta.index(j);
    for(i=cur_index->attribute_num-1;i>=0;i--){
      ss<<show_index.table_name<<"|"<<1-cur_index->unique<<"|"<<cur_index->name()<<"|"<<cur_index->attribute_num-i<<"|"<<cur_index->attribute_name_list[i]<<std::endl;
    }
  }

  session_event->set_response(ss.str().c_str());
  LOG_TRACE("exit do show index\n");
  return RC::SUCCESS;
    
}

RC ExecuteStage::do_show_tables(SQLStageEvent *sql_event)
{
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  std::vector<std::string> all_tables;
  db->all_tables(all_tables);
  if (all_tables.empty()) {
    session_event->set_response("No table\n");
  } else {
    std::stringstream ss;
    for (const auto &table : all_tables) {
      ss << table << std::endl;
    }
    session_event->set_response(ss.str().c_str());
  }
  return RC::SUCCESS;
}

RC ExecuteStage::do_desc_table(SQLStageEvent *sql_event)
{
  Query *query = sql_event->query();
  Db *db = sql_event->session_event()->session()->get_current_db();
  const char *table_name = query->sstr.desc_table.relation_name;
  Table *table = db->find_table(table_name);
  std::stringstream ss;
  if (table != nullptr) {
    table->table_meta().desc(ss);
  } else {
    ss << "No such table: " << table_name << std::endl;
  }
  sql_event->session_event()->set_response(ss.str().c_str());
  return RC::SUCCESS;
}

RC ExecuteStage::do_insert(SQLStageEvent *sql_event)
{
  LOG_TRACE("Enter\n");
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();
  LOG_TRACE("After initialization\n");
  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }
  LOG_TRACE("Before insert convert\n");
  InsertStmt *insert_stmt = (InsertStmt *)stmt;
  Table *table = insert_stmt->table();
  LOG_TRACE("after insert convert\n");
  RC rc = table->insert_record(trx, insert_stmt->value_amount(), insert_stmt->values());
  if (rc == RC::SUCCESS) {
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      } 

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    } else {
      session_event->set_response("SUCCESS\n");
    }
  } else {
    session_event->set_response("FAILURE\n");
  }
  LOG_TRACE("Exit\n");
  return rc;
}

RC ExecuteStage::do_delete(SQLStageEvent *sql_event)
{
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  if (stmt == nullptr) {
    LOG_WARN("cannot find statement");
    return RC::GENERIC_ERROR;
  }

  DeleteStmt *delete_stmt = (DeleteStmt *)stmt;
  TableScanOperator scan_oper(delete_stmt->table());
  PredicateOperator pred_oper(delete_stmt->filter_stmt());
  pred_oper.add_child(&scan_oper);
  DeleteOperator delete_oper(delete_stmt, trx);
  delete_oper.add_child(&pred_oper);

  RC rc = delete_oper.open();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
    if (!session->is_trx_multi_operation_mode()) {
      CLogRecord *clog_record = nullptr;
      rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
      if (rc != RC::SUCCESS || clog_record == nullptr) {
        session_event->set_response("FAILURE\n");
        return rc;
      }

      rc = clog_manager->clog_append_record(clog_record);
      if (rc != RC::SUCCESS) {
        session_event->set_response("FAILURE\n");
        return rc;
      } 

      trx->next_current_id();
      session_event->set_response("SUCCESS\n");
    }
  }
  return rc;
}

/**
 * @func    do_drop_table
 * @author  czy
 * @date    2022-09-27 07:12
 * @param   sql_event
 * @return  RC
 */
RC ExecuteStage::do_drop_table(SQLStageEvent *sql_event)
{
  const DropTable &drop_table = sql_event->query()->sstr.drop_table;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  RC rc = db->drop_table(drop_table.relation_name);
  if (rc == RC::SUCCESS) {
    session_event->set_response("SUCCESS\n");
  } else {
    session_event->set_response("FAILURE\n");
  }
  return rc;
}
RC ExecuteStage::do_begin(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(true);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_BEGIN, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}

RC ExecuteStage::do_commit(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  Db *db = session->get_current_db();
  Trx *trx = session->current_trx();
  CLogManager *clog_manager = db->get_clog_manager();

  session->set_trx_multi_operation_mode(false);

  CLogRecord *clog_record = nullptr;
  rc = clog_manager->clog_gen_record(CLogType::REDO_MTR_COMMIT, trx->get_current_id(), clog_record);
  if (rc != RC::SUCCESS || clog_record == nullptr) {
    session_event->set_response("FAILURE\n");
    return rc;
  }

  rc = clog_manager->clog_append_record(clog_record);
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  trx->next_current_id();

  return rc;
}

RC ExecuteStage::do_clog_sync(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  SessionEvent *session_event = sql_event->session_event();
  Db *db = session_event->session()->get_current_db();
  CLogManager *clog_manager = db->get_clog_manager();

  rc = clog_manager->clog_sync();
  if (rc != RC::SUCCESS) {
    session_event->set_response("FAILURE\n");
  } else {
    session_event->set_response("SUCCESS\n");
  }

  return rc;
}
