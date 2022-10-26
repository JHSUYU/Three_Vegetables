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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>

#include "rc.h"
#include "sql/stmt/stmt.h"
#include "storage/common/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

class SelectStmt : public Stmt
{
public:

  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }
public:
  static RC create(Db *db, const Selects &select_sql, Stmt *&stmt);
  void set_is_aggregation(bool flag) { is_aggregation_ = flag; }

public:
  const std::vector<Table *> &tables() const { return tables_; }
  const std::vector<Field> &query_fields() const { return query_fields_; }
  const std::vector<char *> &aggr_funcs() const { return aggr_funcs_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  bool is_aggregation() { return is_aggregation_; }

private:
  // czy add: check whether this is an aggregation select
  bool is_aggregation_ = false;
  std::vector<char *> aggr_funcs_;  // 形如 aggr_func(column_name) 的聚合函数
  std::vector<Field> query_fields_;
  std::vector<Table *> tables_;
  FilterStmt *filter_stmt_ = nullptr;
};

