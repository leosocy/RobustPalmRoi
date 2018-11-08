// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "robust-palm-roi/c_api.h"

namespace {

TEST(test_c_api, test_init_chain) {
  void* chain = init_chain(TEST_CONFIG_YAML_FILE);
  EXPECT_TRUE(chain != NULL);
}

}