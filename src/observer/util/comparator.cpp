/*
 * @Author: 181830014 181830014@smail.nju.edu.cn
 * @Date: 2022-10-21 17:50:56
 * @LastEditors: 181830014 181830014@smail.nju.edu.cn
 * @LastEditTime: 2022-10-22 02:08:38
 * @FilePath: /source/ocean/src/observer/util/comparator.cpp
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
// Created by wangyunlai on 2021/6/11.
//

#include <string.h>
#include <algorithm>
#include <regex>
#include "common/log/log.h"

const double epsilon = 1E-6;

int compare_int(void *arg1, void *arg2)
{
  int v1 = *(int *)arg1;
  int v2 = *(int *)arg2;
  return v1 - v2;
}

int compare_float(void *arg1, void *arg2)
{
  float v1 = *(float *)arg1; 
  float v2 = *(float *)arg2; 
  float cmp = v1 - v2;
  if (cmp > epsilon) {
    return 1;
  }
  if (cmp < -epsilon) {
    return -1;
  }
  return 0;
}

int compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  // LOG_ERROR("in compare_string() ... ");
  const char *s1 = (const char *)arg1;
  const char *s2 = (const char *)arg2;
  arg1_max_length = strlen(s1);
  arg2_max_length = strlen(s2);
  int maxlen = std::min(arg1_max_length, arg2_max_length);
  int result =  strncmp(s1, s2, maxlen);

  // czy add
  // 判断是否like, 是则返回1000
  LOG_ERROR("s1 = %s, s2 = %s, len1 = %d, len2 = %d", s1, s2, arg1_max_length, arg2_max_length);
  int pos = 0;
  std::string str1(s1);
  std::string str2(s2);
  while ((pos = str2.find("_")) != -1) {
    str2 = str2.replace(pos, 1, ".");
  }
  while ((pos = str2.find("%")) != -1) {
    str2 = str2.replace(pos, 1, ".*?");
  }
  std::cout<<"str1 = " << str1 << ", str2 = " << str2 << std::endl;
  std::regex reg(str2);
  int like_match = std::regex_match(str1, reg);
  LOG_ERROR("LIKE_MATCH = %d, result = %d", like_match, result);

  if ((result == 0 && arg1_max_length == arg2_max_length) || str1 == str2) {
    return 0;
  }
  else if (like_match) {
    return 1000;
  }
  else if (result != 0) {
    return result;
  }
  else if (arg1_max_length > maxlen) {
    return s1[maxlen] - 0;
  }

  else if (arg2_max_length > maxlen) {
    return 0 - s2[maxlen];
  }
  return 0;
}
