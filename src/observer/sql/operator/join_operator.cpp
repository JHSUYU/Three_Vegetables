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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/join_operator.h"
#include "storage/common/table.h"
#include "rc.h"

RC JoinOperator::open()
{
    LOG_TRACE("Enter\n");
    RC rc = RC::SUCCESS;
    rc = left_->open();
    if (rc != RC::SUCCESS) {
        LOG_WARN("Open left failed");
        return rc;
    }
    rc = right_->open();
    if (rc != RC::SUCCESS) {
        LOG_WARN("Open right failed");
        return rc;
    }
    round_done_ = false;
    merged_tuple_ = new RowTuple();
    return rc;
}

RC JoinOperator::next()
{
    LOG_TRACE("Enter, next_cnt = %d\n", next_cnt);
    next_cnt++;
    bool flag = true;
    if (round_done_) {
        return RC::RECORD_EOF;
    }
    RC rc = RC::SUCCESS;
    rc = right_->next();
    if (rc != RC::SUCCESS) {
        LOG_TRACE("Enter\n");
        flag = false;
        right_->close();
        right_->open();
        rc = right_->next();
        if (rc != RC::SUCCESS) {
            round_done_ = true;
            LOG_WARN("Error to get right tuple again");
            return RC::RECORD_EOF;
        }
        rc = left_->next();
        if (rc != RC::SUCCESS) {
            round_done_ = true;
            LOG_WARN("left reaches end, finish reading");
            return RC::RECORD_EOF;
        }
    }
    if ((next_cnt == 1) && flag) {
        rc = left_->next();
        if (rc != RC::SUCCESS) {
            round_done_ = true;
            LOG_WARN("left reaches end, finish reading");
            return RC::RECORD_EOF;
        }
    }
    Tuple* right_tuple = right_->current_tuple();
    Tuple* left_tuple = left_->current_tuple();
    rc = merge_tuple(left_tuple, right_tuple);
    LOG_TRACE("Exit\n");
    return rc;
}

RC JoinOperator::close()
{
    LOG_TRACE("Enter\n");
    RC rc = RC::SUCCESS;
    if (left_ != nullptr) {
        rc = left_->close();
    }
    
    if (rc != RC::SUCCESS) {
        LOG_WARN("close left failed");
        return rc;
    }
    if (right_ != nullptr) {
        rc = right_->close();
    }
    if (rc != RC::SUCCESS) {
        LOG_WARN("close right failed");
        return rc;
    }
    LOG_TRACE("Exit\n");
    return RC::SUCCESS;
}

Tuple* JoinOperator::current_tuple() {
    return merged_tuple_;
}

RC JoinOperator::merge_tuple(Tuple* left_tuple, Tuple* right_tuple) {
    LOG_TRACE("Enter\n");
    RowTuple* left_row_tuple = (RowTuple*)left_tuple;
    RowTuple* right_row_tuple = (RowTuple*)right_tuple;
    int left_num = left_row_tuple->cell_num();
    int right_num = right_row_tuple->cell_num();
    LOG_DEBUG("left_num = %d, right_num = %d", left_num, right_num);
    const TupleCellSpec* left_cell_spec;
    const TupleCellSpec* right_cell_spec;
    RC rc = RC::SUCCESS;

    rc = left_row_tuple->cell_spec_at(1, left_cell_spec);
    rc = right_row_tuple->cell_spec_at(1, right_cell_spec);

    int left_record_size = ((FieldExpr*)(left_cell_spec->expression()))->field().table()->table_meta().record_size();
    int right_record_size = ((FieldExpr*)(right_cell_spec->expression()))->field().table()->table_meta().record_size();

    if (next_cnt == 1) {
        rc = left_row_tuple->cell_spec_at(1, left_cell_spec);
        const TupleCellSpec* tsp_left = left_cell_spec;
        FieldExpr* expr = (FieldExpr*)tsp_left->expression();
        std::string table_name_left(expr->table_name());
        rc = right_row_tuple->cell_spec_at(1, right_cell_spec);
        const TupleCellSpec* tsp_right = right_cell_spec;
        expr = (FieldExpr*)tsp_right->expression();
        std::string table_name_right(expr->table_name());
        tmp_table_ = new Table();
        std::string table_name = table_name_left + "_" + table_name_right;
        tmp_table_->create_tmp_table(table_name);
        std::vector<FieldMeta> fields;

        for (int i = 0; i < left_num; i++) {
            rc = left_row_tuple->cell_spec_at(i, left_cell_spec);
            // LOG_DEBUG("left_cell_spec alias len = %d", left_cell_spec->alias().size());
            // merged_tuple_->add_spec(left_cell_spec);
            // LOG_DEBUG("left_cell_spec alias len = %d", left_cell_spec->alias().size());
            TupleCellSpec* tsp = const_cast<TupleCellSpec*>(left_cell_spec);
            FieldExpr* expr = (FieldExpr*)tsp->expression();
            const FieldMeta* meta = expr->field().meta();
            std::string origin_table_name(expr->field().table_name());
            std::string field_name(expr->field().field_name());
            std::string alias_name = origin_table_name + "." + field_name;
            LOG_TRACE("alias name = %s", alias_name.c_str());
            FieldMeta* new_field = new FieldMeta();
            new_field->init(expr->field().field_name(), expr->field().attr_type(), 
            meta->offset(), meta->len(), meta->visible());
            FieldExpr* new_expr = new FieldExpr(tmp_table_, new_field);
            new_expr->field().set_origin_table_name(origin_table_name);
            LOG_TRACE("FieldExpr field's table name = %s", new_expr->field().table_name());
            TupleCellSpec* new_tsp = new TupleCellSpec(new_expr);
            new_tsp->set_alias(alias_name.c_str());
            merged_tuple_->add_spec(new_tsp);
            fields.push_back(*new_field);
        }
        // tmp_table_->

        // shift
        for (int i = 0; i < right_num; i++) {
            rc = right_row_tuple->cell_spec_at(i, right_cell_spec);
            // LOG_DEBUG("right_cell_spec alias len = %d", right_cell_spec->alias().size());
            // FieldExpr* expr = (FieldExpr*)(right_cell_spec->expression());
            // const FieldMeta* meta = expr->field().meta();
            // FieldMeta* new_meta = new FieldMeta();
            // new_meta->set_offset(meta->offset() + left_record_size);
            // // LOG_DEBUG("meta->offset() + left_record_size = %d", new_meta->offset());
            // Field* new_field = new Field(expr->field().table(), new_meta);
            // FieldExpr* new_expr = new FieldExpr();
            // new_expr->set_field(*new_field);
            // TupleCellSpec* tsp = new TupleCellSpec(new_expr);
            // std::string table_name(expr->table_name());
            // std::string field_name(expr->field().field_name());
            // std::string alias_name = table_name + "." + field_name;
            // tsp->set_alias(alias_name.c_str());
            // merged_tuple_->add_spec(tsp);
            TupleCellSpec* tsp = const_cast<TupleCellSpec*>(right_cell_spec);
            FieldExpr* expr = (FieldExpr*)tsp->expression();
            const FieldMeta* meta = expr->field().meta();
            std::string origin_table_name(expr->field().table_name());
            std::string field_name(expr->field().field_name());
            std::string alias_name = table_name + "." + field_name;
            FieldMeta* new_field = new FieldMeta();
            new_field->init(expr->field().field_name(), expr->field().attr_type(), 
            meta->offset() + left_record_size, meta->len(), meta->visible());
            FieldExpr* new_expr = new FieldExpr(tmp_table_, new_field);
            new_expr->field().set_origin_table_name(origin_table_name);
            TupleCellSpec* new_tsp = new TupleCellSpec(new_expr);
            new_tsp->set_alias(alias_name.c_str());
            merged_tuple_->add_spec(new_tsp);
            fields.push_back(*new_field);
        }
        tmp_table_->get_meta().add_field_metas(fields);
    } 
    LOG_TRACE("Enter\n");
    
    char* record_data = new char[left_record_size + right_record_size + 4];
    LOG_DEBUG("total_record_size = %d", left_record_size + right_record_size);
    LOG_TRACE("Enter\n");
    
    char* left_data = left_row_tuple->record().data();
    LOG_TRACE("Enter\n");
    LOG_DEBUG("left_record_size = %d", left_record_size);
    memcpy(record_data, left_data, left_record_size);
    char* right_data = right_row_tuple->record().data();
    // for (int i = 0; i < right_record_size; i++) {
    //     LOG_DEBUG("right_data = %d", right_data[i]);
    // }
    memcpy(record_data + left_record_size, right_data, right_record_size);
    char zero[4] = {'\0', '\0', '\0', '\0'};
    memcpy(record_data + left_record_size + right_record_size, zero, 4);
    // for (int i = 0; i < left_record_size; i++) {
    //     record_data[i] = left_data[i];
    // }
    // for (int i = 0; i < right_record_size; i++) {
    //     record_data[i + left_record_size] = right_data[i];
    // }
    // record_data[left_record_size + right_record_size - 1] = '\0';
    // for (int i = 0; i < left_record_size + right_record_size; i++) {
    //     LOG_DEBUG("record_data = %d", record_data[i]);
    // }
    Record &record = merged_tuple_->record();
    if (record.data() != nullptr) {
        delete record.data();
        record.set_data(nullptr);
    }
    record.set_data(record_data);
    tmp_table_->get_meta_for_modify().set_record_size(left_record_size + right_record_size);
    LOG_TRACE("Exit\n");
    return rc;
} 