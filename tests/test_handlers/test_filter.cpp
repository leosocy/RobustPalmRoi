/****************************************************************************\
 * Created on Tue Oct 09 2018
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
  Mat invalid_palm;
  GaussianFilter filter;
  auto status = filter.Handle(invalid_palm, &invalid_palm);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  status = filter.Handle(complex_env_palm_, &complex_env_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace
