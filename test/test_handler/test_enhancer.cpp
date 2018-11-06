// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "handler/handler.h"

namespace {

using cv::Mat;

using rpr::Status;

class EnhancerTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  EnhancerTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(EnhancerTestFixture, test_laplace_enhancer) {
  auto enhancer = rpr::HandlerFactory::instance().GetHandler("LaplaceEnhancer");
  auto status = enhancer->Handle(invalid_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  status = enhancer->Handle(complex_env_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace
