// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_

#include "handlers/handler.h"

namespace rpr {

class Detector : public Handler {
 public:
  virtual Status Handle(const cv::Mat& orig, cv::Mat* res);
 protected:
  bool ImageOneContour(const cv::Mat& src);
  virtual Status Detect(const cv::Mat& orig, cv::Mat* res) = 0;
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
  virtual Status Detect(const cv::Mat& orig, cv::Mat* res);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_