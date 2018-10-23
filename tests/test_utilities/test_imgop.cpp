// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "utilities/imgop.h"

namespace {

using rpr::utility::WarpAffineImageOperator;
using rpr::utility::ResizeImageOperator;

class ImageOperateTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  ImageOperateTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(ImageOperateTestFixture, test_warp_affine_image_operator_do) {
  WarpAffineImageOperator op(perfect_palm_.PrevHandleRes(), 90, 0.5);
  cv::Mat res;
  op.Do(&res);
  EXPECT_EQ(res.size(), cv::Size(perfect_palm_.PrevHandleRes().rows / 2, perfect_palm_.PrevHandleRes().cols / 2));
}

TEST_F(ImageOperateTestFixture, test_warp_affine_image_operator_reflect_points) {
  WarpAffineImageOperator op(perfect_palm_.PrevHandleRes(), 90, 0.5);
  cv::Mat res;
  op.Do(&res);
  std::vector<cv::Point> srcs({cv::Point(0, 10)});
  std::vector<cv::Point> dsts;
  op.ReflectPoints(srcs, &dsts);
  EXPECT_EQ(dsts[0].x, perfect_palm_.PrevHandleRes().cols - 20);
  EXPECT_EQ(dsts[0].y, 0);
}

TEST_F(ImageOperateTestFixture, test_resize_image_operator_do) {
  cv::Mat res;
  ResizeImageOperator op1(perfect_palm_.PrevHandleRes(), cv::Size(100, 200));
  op1.Do(&res);
  EXPECT_EQ(res.size(), cv::Size(100, 200));

  ResizeImageOperator op2(perfect_palm_.PrevHandleRes(), 0.5);
  op2.Do(&res);
  EXPECT_EQ(res.size(), cv::Size(perfect_palm_.PrevHandleRes().cols * 0.5, perfect_palm_.PrevHandleRes().rows * 0.5));

  ResizeImageOperator op3(perfect_palm_.PrevHandleRes(), 256);
  op3.Do(&res);
  EXPECT_EQ(res.size(), cv::Size(256, perfect_palm_.PrevHandleRes().rows * 256 / perfect_palm_.PrevHandleRes().cols));
}

TEST_F(ImageOperateTestFixture, test_resize_image_operator_reflect_points) {
  ResizeImageOperator op(perfect_palm_.PrevHandleRes(), 256);
  cv::Mat res;
  op.Do(&res);
  std::vector<cv::Point> srcs({cv::Point(0, 0), cv::Point(128, 128)});
  std::vector<cv::Point> dsts;
  op.ReflectPoints(srcs, &dsts);
  ASSERT_EQ(dsts.size(), 2);
  EXPECT_EQ(dsts[0], cv::Point(0, 0));
  EXPECT_EQ(dsts[1].x, cvRound(128 * (double)perfect_palm_.PrevHandleRes().cols / 256));
  EXPECT_EQ(dsts[1].y, cvRound(128 * (double)perfect_palm_.PrevHandleRes().cols / 256));
}

}   // namespace
