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

  QueryExpressionContext qec;
  auto value = Expression::eval(fg->expr(), qec);
  return finish(std::move(value));
}

}  // namespace graph
}  // namespace nebula
