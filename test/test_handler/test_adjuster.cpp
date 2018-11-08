// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "handler/handler.h"

namespace {

using cv::Mat;

using rpr::Status;

class AdjusterTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  AdjusterTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(AdjusterTestFixture, test_noise_adjuster) {
  auto adjuster = rpr::HandlerFactory::instance().GetHandler("NoiseAdjuster");
  auto status = adjuster->Handle(complex_env_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  auto binarizer = rpr::HandlerFactory::instance().GetHandler("OtsuBinarizer");
  binarizer->Handle(perfect_palm_);
  status = adjuster->Handle(perfect_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

TEST_F(AdjusterTestFixture, test_angle_adjuster) {
  auto adjuster = rpr::HandlerFactory::instance().GetHandler("AngleAdjuster");
  auto status = adjuster->Handle(complex_env_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  auto binarizer = rpr::HandlerFactory::instance().GetHandler("OtsuBinarizer");
  binarizer->Handle(perfect_palm_);
  status = adjuster->Handle(perfect_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace