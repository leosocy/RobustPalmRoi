// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_HANDLER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_HANDLER_H_

#include <opencv2/opencv.hpp>
#include "common/status.h"
#include "common/palm.h"


namespace rpr {

class Handler {
 public:
  virtual Status Handle(PalmInfoDTO& palm) = 0;
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_HANDLER_H_
