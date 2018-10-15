// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <vector>
#include "handlers/detector.h"

namespace rpr {

bool Detector::ImageOneContour(const cv::Mat& src) {
  std::vector< std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(src, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
  return contours.size() == 1;
}

Status PeakValleyDetector::Detect(const cv::Mat& orig, cv::Mat* res) {
  return Status::Ok();
}

}   // namespace rpr