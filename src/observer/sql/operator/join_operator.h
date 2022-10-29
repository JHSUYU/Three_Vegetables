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
// Created by WangYunlai on 2021/6/10.
//

#pragma once

#include <vector>

#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "rc.h"

// TODO fixme
class JoinOperator : public Operator
{
public:
  JoinOperator(){}
  JoinOperator(Operator *left, Operator *right): left_(left), right_(right)
  {

  }

  ~JoinOperator() {
    if (merged_tuple_->record().data() != nullptr) {
      delete merged_tuple_->record().data();
    }
    
    delete &(merged_tuple_->record());
    delete merged_tuple_;
    // const std::vector<FieldMeta> *metas = tmp_table_->table_meta().field_metas();
    // for (int i = 0; i < metas->size(); i++) {
    //   delete &metas[i];
    // }
    delete tmp_table_; 
  }

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;

private:

  RC merge_tuple(Tuple* left, Tuple* right);

  Operator *left_ = nullptr;
  Operator *right_ = nullptr;
  bool round_done_ = true;

  RowTuple *merged_tuple_;
  
  int next_cnt = 0;

  Table* tmp_table_;
};
