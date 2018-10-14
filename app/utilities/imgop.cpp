// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "utilities/imgop.h"

namespace rpr {

namespace utility {

void GetCenterOfGravity(const cv::Mat& src, cv::Point* center, bool is_binary) {
  cv::Moments moment = cv::moments(src, is_binary);
  center->x = moment.m10 / moment.m00;
  center->y = moment.m01 / moment.m00;
}


WarpAffineImageOperator::WarpAffineImageOperator(const cv::Mat& src, double angle, double scale)
  : ImageOperator(src), angle_(angle), radian_(angle_ / 180.0 * CV_PI), scale_(scale) {
}

void WarpAffineImageOperator::Do(cv::Mat* res) {
  double vsin = fabs(sin(radian_));
  double vcos = fabs(cos(radian_));
  int w = orig_.cols * scale_;
  int h = orig_.rows * scale_;
  int diagonal = sqrt(h * h + w * w);
  int target_width = w * vcos + h * vsin;
  int target_height = h * vcos + w * vsin;
  cv::Rect target_rect((diagonal - target_width) / 2, (diagonal - target_height) / 2,
                       target_width, target_height);

  cv::Mat temp(diagonal, diagonal, orig_.type(), cv::Scalar());
  cv::Mat roi(temp, cv::Rect((diagonal - w) / 2, (diagonal - h) / 2, w, h));
  orig_.copyTo(roi);
  cv::Mat affine = cv::getRotationMatrix2D(cv::Point2f(diagonal / 2.0, diagonal / 2.0), angle_, scale_);
  cv::warpAffine(temp, *res, affine, temp.size());
  *res = cv::Mat(*res, target_rect);
  res_size_ = res->size();
}

void WarpAffineImageOperator::ReflectPoints(const std::vector<cv::Point>& srcs,
                                            std::vector<cv::Point>* dsts) {
  assert (res_size_.height > 0 && res_size_.width > 0 && dsts != NULL);
  double vsin = sin(-radian_);
  double vcos = cos(-radian_);
  cv::Point2f center(res_size_.width / 2.0, res_size_.height / 2.0);
  for (auto p : srcs) {
    cv::Point dp;
    double x = p.x - center.x;
	  double y = p.y - center.y;
    dp.x = cvRound(x * vcos / scale_ + y * vsin / scale_ + center.x + (orig_.cols - res_size_.width) / 2);
    dp.y = cvRound(y * vcos / scale_ - x * vsin / scale_ + center.y + (orig_.rows - res_size_.height) / 2);
    dsts->emplace_back(dp);
  }
}

}   // namespace utility

}   // namespace rpr