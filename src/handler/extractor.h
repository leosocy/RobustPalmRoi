// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_SRC_HANDLER_EXTRACTOR_H_
#define ROBUST_PALM_ROI_SRC_HANDLER_EXTRACTOR_H_

#include "robust-palm-roi/types.h"
#include "robust-palm-roi/handler.h"
#include "common/palm.h"

namespace rpr {

class Extractor : public Handler {
 public:
  Status Handle(PalmInfoDTO& palm) override;

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
 public:
  EffectiveIncircleExtractor();
  const char* name() override;

 private:
  Status Extract(PalmInfoDTO& palm) override;
  void ReduceSearchScope(PalmInfoDTO& palm, cv::Rect* rect);
  void CalcEffectiveIncircle(const cv::Mat& dist, const cv::Rect& scope, cv::Point* center, float* radius);
  void ReflectIncircleOnOrig(PalmInfoDTO& palm, cv::Point* center, float* radius, double* angle);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_SRC_HANDLER_EXTRACTOR_H_