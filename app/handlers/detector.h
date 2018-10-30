// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_

#include <vector>
#include "common/types.h"
#include "handlers/handler.h"

namespace rpr {

class Detector : public Handler {
 public:
  Status Handle(PalmInfoDTO& palm) override;

 protected:
  bool ImageOneContour(PalmInfoDTO& palm);
  virtual Status Detect(PalmInfoDTO& palm) = 0;
};

inline Status Detector::Handle(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes(); 
  if (orig.empty() || orig.channels() != 1 || !ImageOneContour(palm)) {
    return Status::LoadImageError("Original palm image must be binary and just has one contour.");
  }
  return Detect(palm);
}


class PeakValleyDetector : public Detector {
 public:
  PeakValleyDetector();
  Status Init() override;

 private:
  enum PalmSide {
    LEFT = 1,
    RIGHT = -1
  };

  Status Detect(PalmInfoDTO& palm) override;
  void FindHalfSideInflectionPoints(const Points& contour, PalmSide side, Points& peaks, Points& valleys);
  size_t FindNextInflectionPoint(const Points& contour, size_t from_index, size_t to_index, int step, bool is_maximum);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_DETECTOR_H_