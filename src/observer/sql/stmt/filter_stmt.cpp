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

#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

#include <vector>
#include <regex>

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
		      const Condition *conditions, int condition_num,
		      FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  FilterStmt *tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    rc = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
		       const RelAttr &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name)) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(std::string(attr.relation_name));
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name);
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  field = table->table_meta().field(attr.attribute_name);
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name);
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}
static bool check_date(int y, int m, int d)
{
    static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (y%400==0 || (y%100 && y%4==0));
    return (m > 0)&&(m <= 12)
        && (d > 0)&&(d <= ((m==2 && leap)?1:0) + mon[m]);
}
RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
				  const Condition &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;
  
  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  Expression *left = nullptr;
  Expression *right = nullptr;
  if (condition.left_is_attr) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    LOG_TRACE("Enter\n");
    left = new FieldExpr(table, field);
  } else {
    LOG_TRACE("Enter\n");
    left = new ValueExpr(condition.left_value);
  }

  if (condition.right_is_attr) {
     LOG_TRACE("Enter\n");
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);  
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      delete left;
      return rc;
    }
    right = new FieldExpr(table, field);
    Condition condition_cpy = condition;
    if (((FieldExpr*)right)->field().attr_type() == DATES) {
        std::vector<std::string> date;
        common::split_string((char*)condition.left_value.data, "-", date);
      if (date.size() != 3) {
        return RC::INVALID_ARGUMENT;
      }
      int y = atoi(date[0].c_str()), m = atoi(date[1].c_str()), d = atoi(date[2].c_str());
      LOG_DEBUG("y: %d, m: %d, d: %d", y, m, d);
      bool b = check_date(y, m, d);
      if (!b) return RC::INVALID_ARGUMENT;
      int date_data = y * 10000 + m * 100 + d;
      LOG_DEBUG("date = %d", date_data);
      const char* dates = std::to_string(date_data).c_str();
      *(int*)condition_cpy.left_value.data = atoi(dates);
      LOG_DEBUG("condition_cpy.left_value.data = %d", (int*)condition_cpy.left_value.data);
      condition_cpy.left_value.type = DATES;
      delete left;
      left = new ValueExpr(condition_cpy.left_value);
    }
  } else {
    LOG_TRACE("Enter\n");
    Condition condition_cpy = condition;
    if (((FieldExpr*)left)->field().attr_type() == DATES) {
        std::vector<std::string> date;
        common::split_string((char*)condition.right_value.data, "-", date);
      if (date.size() != 3) {
        return RC::INVALID_ARGUMENT;
      }
      int y = atoi(date[0].c_str()), m = atoi(date[1].c_str()), d = atoi(date[2].c_str());
      LOG_DEBUG("y: %d, m: %d, d: %d", y, m, d);
      bool b = check_date(y, m, d);
      if (!b) return RC::INVALID_ARGUMENT;
      int date_data = y * 10000 + m * 100 + d;
      LOG_DEBUG("date = %d", date_data);
      const char* dates = std::to_string(date_data).c_str();
      *(int*)condition_cpy.right_value.data = atoi(dates);
      LOG_DEBUG("condition_cpy.right_value.data = %d", *(int*)condition_cpy.right_value.data);
      condition_cpy.right_value.type = DATES;
    }
    right = new ValueExpr(condition_cpy.right_value);
  }

  filter_unit = new FilterUnit;
  filter_unit->set_comp(comp);
  filter_unit->set_left(left);
  filter_unit->set_right(right);

  // 检查两个类型是否能够比较
  return rc;
}
