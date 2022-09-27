/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-09-25 22:00:28
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-09-26 23:31:41
 * @FilePath: /miniob/src/observer/storage/common/meta_util.cpp
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

// Created by Meiyi & wangyunlai.wyl on 2021/5/18.
//

#include "common/defs.h"
#include "storage/common/meta_util.h"

std::string table_meta_file(const char *base_dir, const char *table_name)
{
  return std::string(base_dir) + common::FILE_PATH_SPLIT_STR + table_name + TABLE_META_SUFFIX;
}
std::string table_data_file(const char *base_dir, const char *table_name)
{
  return std::string(base_dir) + common::FILE_PATH_SPLIT_STR + table_name + TABLE_DATA_SUFFIX;
}

std::string table_index_file(const char *base_dir, const char *table_name, const char *index_name)
{
  return std::string(base_dir) + common::FILE_PATH_SPLIT_STR + table_name + "-" + index_name + TABLE_INDEX_SUFFIX;
}
