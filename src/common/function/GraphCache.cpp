/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include "common/function/GraphCache.h"

namespace nebula {

GraphCache& GraphCache::instance() {
  static GraphCache cache;
  return cache;
}

}  // namespace nebula
