/****************************************************************************\
 * Created on Sun Oct 07 2018
 * 
 * The MIT License (MIT)
 * Copyright (c) 2018 leosocy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the ",Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED ",AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
\*****************************************************************************/

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
