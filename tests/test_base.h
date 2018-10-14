// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#pragma once

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

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
  }
  virtual void TearDown() {
    perfect_palm_.release();
    complex_env_palm_.release();
  }

 protected:
  void LoadPalmImage(const char* filename, cv::Mat* palm) {
    assert (palm != NULL);
    *palm = cv::imread(filename);
    cv::resize(*palm, *palm, cv::Size(palm->cols * scaling_, palm->rows * scaling_));
  }
  const double scaling_;
  cv::Mat perfect_palm_;
  cv::Mat complex_env_palm_;
};
