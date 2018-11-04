// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_SRC_UTIL_IMAGE_OPERATOR_H_
#define ROBUST_PALM_ROI_SRC_UTIL_IMAGE_OPERATOR_H_

#include <vector>
#include <opencv2/opencv.hpp>

namespace rpr {

void GetCenterOfGravity(const cv::Mat& src, cv::Point* center, bool is_binary = true);
float CalcPointDist(const cv::Point& p1, const cv::Point& p2);


class ImageOperator {
 public:
  ImageOperator(const cv::Mat& src) : orig_(src) {}
  virtual void Do(cv::Mat* res) = 0;
  // Calculate points on the operated image corresponds to the coordinates on the original image.
  virtual void ReflectPoints(const std::vector<cv::Point>& srcs, std::vector<cv::Point>* dsts) = 0;

 protected:
  cv::Mat orig_;
  cv::Size res_size_;
};


class WarpAffineImageOperator : public ImageOperator {
 public:
  WarpAffineImageOperator(const cv::Mat& src, double angle = 0.0, double scale = 1.0);
  void Do(cv::Mat* res) override;
  void ReflectPoints(const std::vector<cv::Point>& srcs, std::vector<cv::Point>* dsts) override;

 private:
  double angle_;
  double radian_;
  double scale_;
};


class ResizeImageOperator : public ImageOperator {
 public:
  ResizeImageOperator(const cv::Mat& src, const cv::Size& dsize);
  ResizeImageOperator(const cv::Mat& src, int width);     // 指定宽度等比例缩放
  void Do(cv::Mat* res) override;
  void ReflectPoints(const std::vector<cv::Point>& srcs, std::vector<cv::Point>* dsts) override;
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_SRC_UTIL_IMAGE_OPERATOR_H_
