/*
 * @Author: 181830014 181830014@smail.nju.edu.cn
 * @Date: 2022-10-21 17:50:56
 * @LastEditors: 181830014 181830014@smail.nju.edu.cn
 * @LastEditTime: 2022-10-22 19:06:27
 * @FilePath: /source/ocean/src/observer/sql/stmt/stmt.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
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

#pragma once

#include "rc.h"
#include "sql/parser/parse_defs.h"

class Db;

enum class StmtType
{
  SELECT,
  INSERT,
  UPDATE,
  DELETE,
  CREATE_TABLE,
  DROP_TABLE,
  CREATE_INDEX,
  DROP_INDEX,
  SYNC,
  SHOW_TABLES,
  DESC_TABLE,
  BEGIN,
  COMMIT,
  ROLLBACK,
  LOAD_DATA,
  HELP,
  EXIT,

  PREDICATE,
};

class Stmt 
{
public:

  Stmt() = default;
  virtual ~Stmt() = default;

  virtual StmtType type() const = 0;

public:
  static RC create_stmt(Db *db, const Query &query, Stmt *&stmt);

private:
};

