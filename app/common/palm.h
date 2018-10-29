// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_COMMON_PALM_H_
#define ROBUST_PALM_ROI_APP_COMMON_PALM_H_

#include <cassert>
#include <memory>
#include <vector>
#include <opencv2/opencv.hpp>
#include <utilities/imgop.h>
#include "common/types.h"

namespace rpr {

using utility::ImageOperator;

class PalmInfoDTO {
 public:
  PalmInfoDTO() {}
  PalmInfoDTO(const cv::Mat& orig) 
    : orig_(orig), handle_results_({orig}) {}
  void release() {
    handle_results_.clear();
    op_records_.clear();
    contour_.clear();
    peaks_.clear();
    valleys_.clear();
  }
  void SetCurHandleRes(const cv::Mat& res) {
    handle_results_.emplace_back(res);
  }
  void SetImageOperator(std::unique_ptr<ImageOperator> op) {
    op_records_.emplace_back(std::move(op));
  }
  void SetContour(const Points& contour) {
    contour_ = contour;
  }
  void SetPeakValley(const Points& peaks, const Points& valleys) {
    peaks_ = peaks;
    valleys_ = valleys;
  }
  void SetRoiAngle(double angle) {
    roi_angle_ = angle;
  }
  void SetRoi(const cv::Mat& roi) {
    roi_ = roi;
  }

  const Points& contour() { return contour_; }
  const cv::Mat& PrevHandleRes() {
    return handle_results_.back();
  }
  void ReflectPointsOnOrig(const Points& srcs, Points* dsts) {
    Points temp = srcs;
    for (auto it = op_records_.rbegin(); it != op_records_.rend(); ++it) {
      (*it)->ReflectPoints(temp, dsts);
      temp = *dsts;
      dsts->clear();
    }
  }
  const cv::Mat& orig() { return orig_; }
  const Points& peaks() { return peaks_; }
  const Points& valleys() { return valleys_; }
  double roi_angle() { return roi_angle_; }
  const cv::Mat& roi() { return roi_; }

 private:
  cv::Mat orig_;
  Mats handle_results_;
  std::vector< std::unique_ptr<ImageOperator> > op_records_;
  Points contour_;
  Points peaks_;    //  order is from left to right
  Points valleys_;  //  order is from left to right
  double roi_angle_;
  cv::Mat roi_;
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_COMMON_PALM_H_