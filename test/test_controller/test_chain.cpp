// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "robust-palm-roi/chain.h"

namespace {

using rpr::Status;
using rpr::ChainBuilder;

class ChainTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  ChainTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(ChainTestFixture, test_chain_builder) {
  ChainBuilder builder;
  builder.SetConfigYaml(TEST_CONFIG_YAML_FILE);
  auto chain = builder.BuildAndInitChain();
  EXPECT_NE(chain.get(), nullptr);
}


TEST_F(ChainTestFixture, test_handler_chain) {
  ChainBuilder builder;
  builder.SetConfigYaml(TEST_CONFIG_YAML_FILE);
  auto chain = builder.BuildAndInitChain();
  cv::Mat roi;
  auto status = chain->Process(complex_env_palm_, &roi);
  EXPECT_EQ(status.code(), Status::kOk);
  EXPECT_FALSE(roi.empty());
  status = chain->Process(perfect_palm_.orig(), &roi);
  EXPECT_FALSE(roi.empty());
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace
