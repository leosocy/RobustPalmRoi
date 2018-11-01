// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <yaml-cpp/yaml.h>
#include "test_base.h"
#include "handlers/detector.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::PeakValleyDetector;

class DetectorTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  DetectorTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(DetectorTestFixture, test_peak_valley_detector) {
  PeakValleyDetector detector;
  detector.Init(YAML::Load("{step: {value: 8}}"));
  auto status = detector.Handle(perfect_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);
}

}   // namespace