// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "handlers/filter.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::GaussianFilter;

class FilterTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  FilterTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(FilterTestFixture, test_gaussian_filter) {
  GaussianFilter filter;
  auto status = filter.Handle(invalid_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  status = filter.Handle(complex_env_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace
