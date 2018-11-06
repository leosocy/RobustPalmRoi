// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <yaml-cpp/yaml.h>
#include "test_base.h"
#include "handler/handler.h"

namespace {

using cv::Mat;

using rpr::Status;

class DetectorTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  DetectorTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(DetectorTestFixture, test_peak_valley_detector) {
  auto detector = rpr::HandlerFactory::instance().GetHandler("PeakValleyDetector");
  auto status = detector->Init(YAML::Load("{step: 8}"));
  EXPECT_EQ(status.code(), Status::kLoadConfigYamlError);
  status = detector->Init(YAML::Load("{step: {value: 8}}"));
  EXPECT_EQ(status.code(), Status::kOk);
  status = detector->Handle(perfect_palm_);
  EXPECT_EQ(status.code(), Status::kLoadImageError);
}

}   // namespace
