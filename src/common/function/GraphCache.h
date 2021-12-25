
/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

#include <folly/concurrency/ConcurrentHashMap.h>

#include "common/datatypes/List.h"
#include "common/function/GraphMatrix.h"

namespace nebula {

class GraphCache final {
  struct Cache;
  using GraphCacheMap = folly::ConcurrentHashMap<std::string, std::shared_ptr<Cache>>;

 public:
  static GraphCache& instance() {
    static GraphCache cache;
    return cache;
  }

  void add(const std::string& name, List edges) {
    // FIXME(yee): let it thread-safe
    graphMap_.insert_or_assign(name, std::make_shared<Cache>(std::move(edges)));
  }

  std::size_t remove(const std::string& name) {
    auto iter = graphMap_.find(name);
    if (iter != graphMap_.end()) {
      auto sz = iter->second->edges.size();
      graphMap_.erase(iter);
      return sz;
    }
    return 0UL;
  }

  const List& edges(const std::string& name) const {
    CHECK(exists(name));
    return graphMap_.find(name)->second->edges;
  }

  bool exists(const std::string& name) const { return graphMap_.find(name) != graphMap_.end(); }

 private:
  GraphCache() = default;

  struct Cache {
    List edges;
    std::unique_ptr<GraphMatrix> matrix;

    explicit Cache(List es) : edges(es) {}
  };

  GraphCacheMap graphMap_;
};

}  // namespace nebula
