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

#include "test_base.h"
#include "handlers/enhancer.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::LaplaceEnhancer;

class EnhancerTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  EnhancerTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};

TEST_F(EnhancerTestFixture, test_laplace_enhancer) {
  Mat invalid_palm;
  LaplaceEnhancer enhancer;
  auto status = enhancer.Handle(invalid_palm, &invalid_palm);
  EXPECT_EQ(status.code(), Status::kLoadImageError);

  status = enhancer.Handle(perfect_palm_, &perfect_palm_);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace
