// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_BINARIZER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_BINARIZER_H_

#include "handlers/handler.h"

namespace rpr {

class Binarizer : public Handler {
 public:
  virtual Status Handle(const cv::Mat& orig, cv::Mat* res);

 protected:
  virtual Status Binary(const cv::Mat& orig, cv::Mat* res) = 0;
};

inline Status Binarizer::Handle(const cv::Mat& orig, cv::Mat* res) {
  assert (res != NULL);
  if (orig.empty()
      || (orig.channels() != 3 && orig.channels() != 1)) {
    return Status::LoadImageError("Original palm image must be colored or grayscale.");
  }
  return Binary(orig, res);
}


class OtsuBinarizer : public Binarizer {
 private:
  virtual Status Binary(const cv::Mat& orig, cv::Mat* res);
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_BINARIZER_H_