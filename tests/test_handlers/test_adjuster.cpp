// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "handlers/binarizer.h"
#include "handlers/adjuster.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::OtsuBinarizer;
using rpr::NoiseAdjuster;
using rpr::AngleAdjuster;

class AdjusterTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  AdjusterTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(AdjusterTestFixture, test_noise_adjuster) {
  NoiseAdjuster adjuster;
  auto status = adjuster.Handle(perfect_palm_, &perfect_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  cv::Mat res;
  OtsuBinarizer binarizer;
  binarizer.Handle(perfect_palm_, &res);
  status = adjuster.Handle(res, &res);
  EXPECT_EQ(status.code(), Status::kOk);
}

TEST_F(AdjusterTestFixture, test_angle_adjuster) {
  AngleAdjuster adjuster;
  auto status = adjuster.Handle(perfect_palm_, &perfect_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  cv::Mat res;
  OtsuBinarizer binarizer;
  binarizer.Handle(perfect_palm_, &res);
  status = adjuster.Handle(res, &res);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace