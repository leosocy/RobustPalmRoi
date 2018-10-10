/****************************************************************************\
 * Created on Mon Oct 08 2018
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
#include "handlers/filter.h"
#include "handlers/binarizer.h"
#include "handlers/adjuster.h"
#include "chain/chain.h"

namespace {

using cv::Mat;

using rpr::Status;
using rpr::Handler;
using rpr::LaplaceEnhancer;
using rpr::GaussianFilter;
using rpr::OtsuBinarizer;
using rpr::RemoveNoiseAdjuster;

using rpr::HandlerChain;

class HandlerChainTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  HandlerChainTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(HandlerChainTestFixture, test_handler_chain) {
  HandlerChain chain;
  chain.Join(std::unique_ptr<Handler>(new GaussianFilter));
  chain.Join(std::unique_ptr<Handler>(new LaplaceEnhancer));
  chain.Join(std::unique_ptr<Handler>(new OtsuBinarizer));
  chain.Join(std::unique_ptr<Handler>(new RemoveNoiseAdjuster));
  cv::Mat result;
  auto status = chain.Process(complex_env_palm_, &result);
  EXPECT_EQ(status.code(), Status::kOk);
}

}   // namespace
