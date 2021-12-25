
/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <folly/concurrency/ConcurrentHashMap.h>

#include "common/datatypes/List.h"
#include "common/function/GraphMatrix.h"

namespace nebula {
namespace graph {

class GraphCache final {
 public:
  explicit GraphCache(List edges) : edges_(std::move(edges)) {}

 private:
  List edges_;
  std::unique_ptr<GraphMatrix> matrix_;
};

using GraphCacheMap = folly::ConcurrentHashMap<std::string, std::shared_ptr<GraphCache>>;

}  // namespace graph
}  // namespace nebula
