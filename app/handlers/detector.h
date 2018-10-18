// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_

#include <vector>
#include "handlers/handler.h"

namespace rpr {

class Detector : public Handler {
 public:
  virtual Status Handle(const cv::Mat& orig, cv::Mat* res);
 protected:
  bool ImageOneContour(const cv::Mat& src);
  virtual Status Detect(const cv::Mat& orig, cv::Mat* res) = 0;
  std::vector<cv::Point> palm_contour_;
};

inline Status Detector::Handle(const cv::Mat& orig, cv::Mat* res) {
  assert (res != NULL);
  if (orig.empty() || orig.channels() != 1 || !ImageOneContour(orig)) {
    return Status::LoadImageError("Original palm image must be binary and just has one contour.");
  }
  return Detect(orig, res);
}


class PeakValleyDetector : public Detector {
 private:
  enum PalmSide {
    LEFT = 1,
    RIGHT = -1
  };

  virtual Status Detect(const cv::Mat& orig, cv::Mat* res);
  void FindHalfSideInflectionPoints(PalmSide side);
  size_t FindNextInflectionPoint(const std::vector<cv::Point>& contour,
                                 size_t from_index, size_t to_index, int step, bool is_maximum,
                                  cv::Point* point);

  std::vector<cv::Point> peaks_;    //  order is from left to right
  std::vector<cv::Point> valleys_;  //  order is from left to right
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_