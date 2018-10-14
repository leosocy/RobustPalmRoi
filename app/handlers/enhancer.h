// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_ENHANCER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_ENHANCER_H_

#include "handlers/handler.h"

namespace rpr {

class Enhancer : public Handler {
 public:
  virtual Status Handle(const cv::Mat& orig, cv::Mat* res);

 protected:
  virtual Status Enhance(const cv::Mat& orig, cv::Mat* res) = 0;
};

inline Status Enhancer::Handle(const cv::Mat& orig, cv::Mat* res) {
  assert (res != NULL);
  if (orig.empty() || orig.channels() != 3) {
    return Status::LoadImageError("Original palm image must be colored.");
  }
  return Enhance(orig, res);
}


class LaplaceEnhancer : public Enhancer {
 private:
  virtual Status Enhance(const cv::Mat& orig, cv::Mat* res);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_ENHANCER_H_
