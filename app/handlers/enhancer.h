// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_ENHANCER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_ENHANCER_H_

#include "handlers/handler.h"

namespace rpr {

class Enhancer : public Handler {
 public:
  Status Handle(PalmInfoDTO& palm) override;

 protected:
  virtual Status Enhance(PalmInfoDTO& palm) = 0;
};

inline Status Enhancer::Handle(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes();
  if (orig.empty() || orig.channels() != 3) {
    return Status::LoadImageError("Original palm image must be colored.");
  }
  return Enhance(palm);
}


class LaplaceEnhancer : public Enhancer {
 public:
  LaplaceEnhancer();

 private:
  Status Enhance(PalmInfoDTO& palm) override;
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_ENHANCER_H_
