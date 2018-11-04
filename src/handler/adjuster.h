// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_SRC_HANDLER_ADJUSTER_H_
#define ROBUST_PALM_ROI_SRC_HANDLER_ADJUSTER_H_

#include <vector>
#include "robust-palm-roi/handler.h"
#include "common/palm.h"

namespace rpr {

class Adjuster : public Handler {
 public:
  Status Handle(PalmInfoDTO& palm) override;

 protected:
  virtual Status Adjust(PalmInfoDTO& palm) = 0;
};

inline Status Adjuster::Handle(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes(); 
  if (orig.empty() || orig.channels() != 1) {
    return Status::LoadImageError("Original palm image must be binary.");
  }
  return Adjust(palm);
}


class NoiseAdjuster : public Adjuster {
 public:
  NoiseAdjuster();
  const char* name() override;

 private:
  Status Adjust(PalmInfoDTO& palm) override;
  void SmoothBoundary(const cv::Mat& src, cv::Mat* dst);
  int FindMaxContourAreaIndex(const std::vector< std::vector<cv::Point> >& contours,
                              const std::vector<cv::Vec4i>& hierarchy);
};


class AngleAdjuster : public Adjuster {
 public:
  AngleAdjuster();
  const char* name() override;

 private:
  Status Adjust(PalmInfoDTO& palm) override;
  void ErodeFinger(const cv::Mat& src, cv::Mat* dst);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_SRC_HANDLER_ADJUSTER_H_