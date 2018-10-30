// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "controllers/chain.h"

namespace {

using rpr::Status;
using rpr::ChainBuilder;

class ChainTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  ChainTestFixture() : RobustPalmRoiTestFixtureBase(1.0) {}
};


TEST_F(ChainTestFixture, test_chain_builder) {
  ChainBuilder builder;
  auto chain = builder.BuildAndInitChain();
  EXPECT_NE(chain.get(), nullptr);
}


TEST_F(ChainTestFixture, test_handler_chain) {
  ChainBuilder builder;
  auto chain = builder.BuildAndInitChain();
  auto status = chain->Process(complex_env_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
  status = chain->Process(perfect_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace
