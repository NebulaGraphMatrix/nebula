/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "graph/executor/maintain/GraphExecutor.h"

#include "common/function/GraphCache.h"
#include "graph/planner/plan/Maintain.h"

namespace nebula::graph {

folly::Future<Status> CreateGraphExecutor::execute() {
  SCOPED_TIMER(&execTime_);
  auto node = asNode<CreateGraph>(this->node());
  if (qctx_->existGraph(node->name())) {
    return Status::Error("graph `%s' existed!", node->name().c_str());
  }

  auto value = ectx_->getValue(node->inputVar());
  if (!value.isDataSet()) {
    return Status::Error("Not dataset type: %s", value.typeName().c_str());
  }

  List edges;
  auto checkEdge = [&](Value &v) -> Status {
    if (v.isEdge()) {
      edges.values.emplace_back(v.moveEdge());
      return Status::OK();
    } else {
      return Status::Error("some element of list is not edge type.");
    }
  };
  auto ds = value.moveDataSet();
  for (auto &row : ds.rows) {
    if (row.size() != 1) {
      return Status::Error("Must be 1 column row.");
    }
    auto column = row.values[0];
    if (column.isList()) {
      for (auto &v : column.moveList().values) {
        NG_RETURN_IF_ERROR(checkEdge(v));
      }
    } else {
      NG_RETURN_IF_ERROR(checkEdge(column));
    }
  }

  auto sz = edges.size();
  GraphCache::instance().add(node->name(), std::move(edges));

  DataSet res;
  Row row;
  row.values.emplace_back(static_cast<int64_t>(sz));
  res.colNames = node->colNames();
  res.rows.emplace_back(std::move(row));

  return finish(Value(std::move(res)));
}

folly::Future<Status> DropGraphExecutor::execute() {
  // TODO(yee)
  auto n = asNode<DropGraph>(node());
  int64_t sz = 0;
  if (GraphCache::instance().exists(n->name())) {
    sz = GraphCache::instance().remove(n->name());
  }
  Row row;
  row.values.emplace_back(sz);
  DataSet ds({n->colNames()});
  ds.rows.emplace_back(std::move(row));
  return finish(Value(std::move(ds)));
}

}  // namespace nebula::graph
