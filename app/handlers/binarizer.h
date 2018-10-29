// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_BINARIZER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_BINARIZER_H_

#include "handlers/handler.h"

namespace rpr {

class Binarizer : public Handler {
 public:
  Status Handle(PalmInfoDTO& palm) override;

 protected:
  virtual Status Binary(PalmInfoDTO& palm) = 0;
};

inline Status Binarizer::Handle(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes();
  if (orig.empty()
      || (orig.channels() != 3 && orig.channels() != 1)) {
    return Status::LoadImageError("Original palm image must be colored or grayscale.");
  }
  return Binary(palm);
}


class OtsuBinarizer : public Binarizer {
 private:
  Status Binary(PalmInfoDTO& palm) override;
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_BINARIZER_H_