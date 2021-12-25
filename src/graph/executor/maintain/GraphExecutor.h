/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include "graph/executor/Executor.h"

namespace nebula::graph {

class CreateGraphExecutor final : public Executor {
 public:
  CreateGraphExecutor(const PlanNode *node, QueryContext *qctx)
      : Executor("CreateGraphExecutor", node, qctx) {}

  folly::Future<Status> execute() override;
};

class DropGraphExecutor final : public Executor {
 public:
  DropGraphExecutor(const PlanNode *node, QueryContext *qctx)
      : Executor("DropGraphExecutor", node, qctx) {}

  folly::Future<Status> execute() override;
};

}  // namespace nebula::graph
