// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "handlers/binarizer.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::OtsuBinarizer;

class BinarizerTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  BinarizerTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(BinarizerTestFixture, test_otsu_binarizer) {
  OtsuBinarizer binarizer;
  auto status = binarizer.Handle(invalid_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  status = binarizer.Handle(complex_env_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

}
