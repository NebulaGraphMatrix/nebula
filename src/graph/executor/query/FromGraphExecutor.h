/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include "graph/executor/Executor.h"

namespace nebula {
namespace graph {

class FromGraphExecutor final : public Executor {
 public:
  FromGraphExecutor(const PlanNode *node, QueryContext *qctx)
      : Executor("FromGraphExecutor", node, qctx) {}

  folly::Future<Status> execute() override;
};

}  // namespace graph
}  // namespace nebula
