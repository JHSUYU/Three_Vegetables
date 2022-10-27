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
// Created by WangYunlai on 2021/6/7.
//

#pragma once

#include "sql/operator/operator.h"
#include "storage/record/record_manager.h"
#include "rc.h"

#include <vector>

class Table;

class TableScanOperator : public Operator
{
public:
  TableScanOperator(Table* table) {
    tables_.push_back(table);
    record_scanners_.assign(tables_.size(), new RecordFileScanner());
    tuples_.assign(tables_.size(), new RowTuple());
    current_record_.assign(tables_.size(), new Record());
  }
  TableScanOperator(std::vector<Table *>tables)
  {
    for (auto t: tables) {
      tables_.push_back(t);
    }
    record_scanners_.assign(tables.size(), new RecordFileScanner());
    tuples_.assign(tables.size(), new RowTuple());
    current_record_.assign(tables.size(), new Record());
  }

  ~TableScanOperator() {
    for (int i = 0; i < record_scanners_.size(); i++) {
      delete record_scanners_[i];
    }
  }

  RC open() override;
  RC next() override;
  RC close() override;

  Tuple * current_tuple() override;

  // int tuple_cell_num() const override
  // {
  //   return tuple_.cell_num();
  // }

  // RC tuple_cell_spec_at(int index, TupleCellSpec &spec) const override;
private:
  std::vector<Table *> tables_ ;
  std::vector<RecordFileScanner*> record_scanners_;
  std::vector<Record*> current_record_;
  std::vector<RowTuple*> tuples_;
  // temp data
  RowTuple tuple_;
  Table* table_;
  Record record_;
};
