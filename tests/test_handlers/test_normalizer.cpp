// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "handlers/normalizer.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::OrigNormalizer;
using rpr::IncircleRoiNormalizer;

class NormalizerTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  NormalizerTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(NormalizerTestFixture, test_orig_normalizer) {
  OrigNormalizer normalizer;
  auto status = normalizer.Handle(perfect_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

TEST_F(NormalizerTestFixture, test_incircle_roi_normalizer) {
  IncircleRoiNormalizer normalizer;
  auto status = normalizer.Handle(perfect_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);
}

}   // namespace