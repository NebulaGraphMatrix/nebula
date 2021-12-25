/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "graph/executor/query/FromGraphExecutor.h"

#include "common/function/GraphCache.h"
#include "graph/planner/plan/Query.h"

namespace nebula {
namespace graph {

folly::Future<Status> FromGraphExecutor::execute() {
  SCOPED_TIMER(&execTime_);
  auto fg = asNode<FromGraph>(node());
  if (!GraphCache::instance().exists(fg->name())) {
    return error(Status::Error("graph `%s' not exists.", fg->name().c_str()));
  }

  DataSet ds;
  List row;
  QueryExpressionContext qec(qctx_->ectx());
  row.values.emplace_back(Expression::eval(fg->expr(), qec));
  ds.rows.emplace_back(std::move(row));
  ds.colNames = fg->colNames();
  return finish(Value(std::move(ds)));
}

}  // namespace graph
}  // namespace nebula
