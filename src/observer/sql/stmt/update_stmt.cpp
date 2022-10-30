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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "common/log/log.h"
#include "sql/parser/parse_defs.h"

#include <unordered_map>

UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount)
  : table_ (table), values_(values), value_amount_(value_amount)
{}

UpdateStmt::UpdateStmt(Table *table, Value *values, size_t value_amount, 
char* attribute_name, FilterStmt *filter_stmt, char* relation_name, Condition* conditions)
  : table_ (table), values_(values), value_amount_(value_amount), 
  filter_stmt_(filter_stmt), attribute_name_(attribute_name), 
  relation_name_(relation_name), conditions_(conditions)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  } 
}

RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
{
  // hsy add
  // stmt = nullptr;
  // return RC::INTERNAL;
  const char *table_name = update.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", 
             db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map,
			     update.conditions, update.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  stmt = new UpdateStmt(table, const_cast<Value*>(&(update.value)), update.condition_num, 
  update.attribute_name, filter_stmt, update.relation_name, const_cast<Condition*>(update.conditions));
  ((UpdateStmt*)stmt)->attribute_num=update.attribute_num;
  for(int i=0;i<update.attribute_num;i++){
    ((UpdateStmt*)stmt)->attribute_names[i]=update.attribute_names[i];
  }
  ((UpdateStmt*)stmt)->value_num=update.attribute_num;
  for(int i=0;i<update.value_num;i++){
    LOG_INFO("The type is %d",update.values[i].type);
    ((UpdateStmt*)stmt)->values_list[i]=const_cast<Value*>(&update.values[i]);
  }


  return rc;
}
