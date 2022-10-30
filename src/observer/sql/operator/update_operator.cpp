#include "common/log/log.h"
#include "sql/operator/update_operator.h"
#include "storage/record/record.h"
#include "storage/common/table.h"
#include "sql/stmt/update_stmt.h"

RC UpdateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("delete operator must has 1 child");
    return RC::INTERNAL;
  }

  Operator *child = children_[0];
  RC rc = child->open();
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  Table *table = update_stmt_->table();
  LOG_DEBUG("table info: table name = %s", table->name());
  while (RC::SUCCESS == (rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }
    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    const TupleCellSpec *spec = nullptr;
    row_tuple->cell_spec_at(1, spec);
    LOG_INFO("current tuple info: %s", spec->alias());

    Record &record = row_tuple->record();
    int update_count = 0;
    rc = table->update_record(nullptr, update_stmt_->attribute_name(), update_stmt_->values(),
    update_stmt_->value_amount(), update_stmt_->conditions(), &update_count);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      return rc;
    }
    if(update_count == 0) {
        return rc;
    }
  }
  return RC::SUCCESS;
}

RC UpdateOperator::next()
{
  return RC::RECORD_EOF;
}

RC UpdateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}