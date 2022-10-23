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
// Created by WangYunlai on 2022/07/05.
//

#include "sql/expr/tuple_cell.h"
#include "storage/common/field.h"
#include "common/log/log.h"
#include "util/comparator.h"
#include "util/util.h"

#include <regex>

void TupleCell::to_string(std::ostream &os) const
{
  switch (attr_type_) {
  case INTS: { 
    os << *(int *)data_;
  } break;
  case DATES: {
    int value = *(int*)data_;
    char buf[16] = {0};
    snprintf(buf,sizeof(buf),"%04d-%02d-%02d",value/10000, (value%10000)/100,value%100); // 注意这里月份和天数，不足两位时需要填充0
    os << buf;
  } break;
  case FLOATS: {
    float v = *(float *)data_;
    os << double2string(v);
  } break;
  case CHARS: {
    for (int i = 0; i < length_; i++) {
      if (data_[i] == '\0') {
        break;
      }
      os << data_[i];
    }
  } break;
  default: {
    LOG_WARN("unsupported attr type: %d", attr_type_);
  } break;
  }
}
static bool check_date(int y, int m, int d)
{
    static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leap = (y%400==0 || (y%100 && y%4==0));
    return (m > 0)&&(m <= 12)
        && (d > 0)&&(d <= ((m==2 && leap)?1:0) + mon[m]);
}
int TupleCell::compare(const TupleCell &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
    case INTS: 
    case DATES: return compare_int(this->data_, other.data_);
    case FLOATS: return compare_float(this->data_, other.data_);
    case CHARS: return compare_string(this->data_, this->length_, other.data_, other.length_);
    default: {
      LOG_WARN("unsupported type: %d", this->attr_type_);
    }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = *(int *)data_;
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = *(int *)other.data_;
    return compare_float(data_, &other_data);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
    int other_data = atoi(other.data_);
    return compare_int(this->data_, &other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
    int this_data = atoi(this->data_);
    return compare_int(&this_data, other.data_);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    float this_data = atof(this->data_);
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    float other_data = atof(other.data_);
    return compare_float(data_, &other_data);
  } else if (this->attr_type_ == DATES && other.attr_type_ == CHARS) {
      std::string str((char*)other.data());
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
      LOG_DEBUG("date = %d", date_data);
      return (*(int*)this->data()) - date_data;
  }
  LOG_WARN("not supported");
  return -1; // TODO return rc?
}
