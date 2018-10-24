// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#pragma once

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include "common/palm.h"
#include "utilities/imgop.h"

#define TEST_PALM_DATA_DIR "../tests/palm_data"

#define TEST_PERFECT_PALM_IMAGE TEST_PALM_DATA_DIR"/palm_perfect.jpg"
#define TEST_COMPLEX_ENV_PALM_IMAGE TEST_PALM_DATA_DIR"/palm_complex_env.jpg"


class RobustPalmRoiTestFixtureBase : public testing::Test {
 public:
  RobustPalmRoiTestFixtureBase(double scaling = 0.5)
    : scaling_(scaling) {
  }
  virtual void SetUp() {
    LoadPalmImage(TEST_PERFECT_PALM_IMAGE, &perfect_palm_);
    LoadPalmImage(TEST_COMPLEX_ENV_PALM_IMAGE, &complex_env_palm_);
    cv::Mat temp;
    invalid_palm_ = rpr::PalmInfoDTO(temp);
  }
  virtual void TearDown() {
    perfect_palm_.release();
    complex_env_palm_.release();
  }

 protected:
  void LoadPalmImage(const char* filename, rpr::PalmInfoDTO* palm) {
    using rpr::utility::ResizeImageOperator;
    assert (palm != NULL);
    cv::Mat img = cv::imread(filename);
    *palm = rpr::PalmInfoDTO(img);
    cv::Mat res;
    ResizeImageOperator *op = new ResizeImageOperator(palm->PrevHandleRes(), scaling_);
    op->Do(&res);
    palm->SetCurHandleRes(res);
    palm->SetImageOperator(std::unique_ptr<rpr::utility::ImageOperator>(op));
  }
  const double scaling_;
  rpr::PalmInfoDTO invalid_palm_;
  rpr::PalmInfoDTO perfect_palm_;
  rpr::PalmInfoDTO complex_env_palm_;
};
