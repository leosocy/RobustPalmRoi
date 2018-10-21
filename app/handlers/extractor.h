// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_EXTRACTOR_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_EXTRACTOR_H_

#include "common/types.h"
#include "handlers/handler.h"

namespace rpr {

class Extractor : public Handler {
 public:
  virtual Status Handle(PalmInfoDTO& palm);
 protected:
  virtual Status Extract(PalmInfoDTO& palm) = 0;
};

inline Status Extractor::Handle(PalmInfoDTO& palm) {
  if (palm.peaks().size() != 5 || palm.valleys().size() != 4 || palm.contour().size() == 0) {
    return Status::ImageLowQualityError("The quality of palm image is lower than the requirement of extraction.");
  }
  return Extract(palm);
}


class EffectiveIncircleExtractor : public Extractor {
 private:
  virtual Status Extract(PalmInfoDTO& palm);
  void ReduceSearchScope(PalmInfoDTO& palm, cv::Rect* rect);
  void CalcEffectiveIncircle(const cv::Mat& dist, const cv::Rect& scope, cv::Point* center, float* radius);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_EXTRACTOR_H_