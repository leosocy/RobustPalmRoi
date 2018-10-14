// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "utilities/imgop.h"

namespace {

using rpr::utility::WarpAffineImageOperator;

class ImageOperateTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  ImageOperateTestFixture() : RobustPalmRoiTestFixtureBase(0.2) {}
};


TEST_F(ImageOperateTestFixture, test_warp_affine_image_operator_do) {
  WarpAffineImageOperator op(perfect_palm_, 90, 0.5);
  cv::Mat res;
  op.Do(&res);
  EXPECT_EQ(res.size(), cv::Size(perfect_palm_.rows / 2, perfect_palm_.cols / 2));
}

TEST_F(ImageOperateTestFixture, test_warp_affine_image_operator_reflect_points) {
  WarpAffineImageOperator op(perfect_palm_, 90, 0.5);
  cv::Mat res;
  op.Do(&res);
  std::vector<cv::Point> srcs({cv::Point(0, 10)});
  std::vector<cv::Point> dsts;
  op.ReflectPoints(srcs, &dsts);
  EXPECT_EQ(dsts[0].x, perfect_palm_.cols - 20);
  EXPECT_EQ(dsts[0].y, 0);
}

}   // namespace
