/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#pragma once

extern "C" {
#include <GraphBLAS.h>
}

#include <unordered_map>
#include <vector>

#include "common/base/Logging.h"
#include "common/datatypes/Edge.h"
#include "common/datatypes/List.h"

namespace nebula {

class GraphMatrix final {
 public:
  using ValueRef = std::reference_wrapper<const Value>;
  using IdListType = std::vector<ValueRef>;
  using IdMapType = std::unordered_map<ValueRef, GrB_Index, std::hash<Value>, std::equal_to<Value>>;

  GraphMatrix(const List &edges, IdListType *vids, GrB_Matrix *m)
      : edges_(edges), vids_(vids), maxVid_(0), m_(m) {
    srcs_.reserve(edges.size());
    dsts_.reserve(edges.size());
    idMap_.reserve(2 * edges.size());
    if (vids_) {
      vids_->resize(2 * edges.size(), Value::kNullValue);
    }
  }

  ~GraphMatrix() {
    if (m_ && *m_) {
      GrB_Matrix_free(m_);
    }
  }

  int init() {
    for (const auto &value : edges_.values) {
      if (!value.isEdge()) {
        return -1;
      }

      auto &edge = value.getEdge();

      auto src = getVid(edge.src);
      auto dst = getVid(edge.dst);

      if (edge.type > 0) {
        srcs_.emplace_back(src);
        dsts_.emplace_back(dst);
      } else {
        srcs_.emplace_back(dst);
        dsts_.emplace_back(src);
      }
    }
    CHECK_LT(maxVid_, GrB_INDEX_MAX);

    int retval = GrB_Matrix_new(m_, GrB_UINT32, maxVid_, maxVid_);
    if (retval != 0) {
      return retval;
    }

    std::vector<uint32_t> weights(edges_.size(), 1U);
    return GrB_Matrix_build_UINT32(*m_,
                                   srcs_.data(),
                                   dsts_.data(),
                                   weights.data(),
                                   static_cast<GrB_Index>(edges_.size()),
                                   GrB_SECOND_UINT32);
  }

 private:
  GrB_Index getVid(const Value &vid) { return idMap_.count(vid) ? idMap_[vid] : addVid(vid); }
  GrB_Index addVid(const Value &vid) {
    auto id = maxVid_++;
    if (vids_) {
      (*vids_)[id] = std::cref(vid);
    }
    idMap_.emplace(std::cref(vid), id);
    return id;
  }

  const List &edges_;
  IdListType *vids_;
  GrB_Index maxVid_;
  GrB_Matrix *m_{nullptr};
  std::vector<GrB_Index> srcs_;
  std::vector<GrB_Index> dsts_;

  IdMapType idMap_;
};

}  // namespace nebula
