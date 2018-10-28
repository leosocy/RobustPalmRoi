// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_NORMALIZER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_NORMALIZER_H_

#include "handlers/handler.h"

namespace rpr {

class OrigNormalizer : public Handler {
 public:
  OrigNormalizer() : scaling_(0.2), width_(0) {}

  Status Handle(PalmInfoDTO& palm) override;

 private:
  double scaling_;
  int width_;
};


class RoiNormalizer : public Handler {
 public:
  RoiNormalizer() : width_(512) {}

  Status Handle(PalmInfoDTO& palm) override;

 protected:
  virtual Status Normalize(PalmInfoDTO& palm) = 0;
  int width_;
};

inline Status RoiNormalizer::Handle(PalmInfoDTO& palm) {
  const cv::Mat& roi = palm.roi();
  if (roi.empty() || roi.channels() != 3) {
    return Status::LoadImageError("Roi of must be extracted from original palm image.");
  }
  return Normalize(palm);
}


class IncircleRoiNormalizer : public RoiNormalizer {
 private:
  Status Normalize(PalmInfoDTO& palm) override;
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_NORMALIZER_H_