// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_FILTER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_FILTER_H_

#include "handlers/handler.h"

namespace rpr {

class Filter : public Handler {
 public:
  virtual Status Handle(PalmInfoDTO& palm);

 protected:
  virtual Status Blur(PalmInfoDTO& palm) = 0;
};

inline Status Filter::Handle(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes();
  if (orig.empty() || orig.channels() != 3) {
    return Status::LoadImageError("Original palm image must be colored.");
  }
  return Blur(palm);
}


class GaussianFilter : public Filter {
 private:
  virtual Status Blur(PalmInfoDTO& palm);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_FILTER_H_