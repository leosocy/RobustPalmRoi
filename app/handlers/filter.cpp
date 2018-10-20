// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <opencv2/imgproc.hpp>
#include "handlers/filter.h"

namespace rpr {

Status GaussianFilter::Blur(PalmInfoDTO& palm) {
  cv::Mat res;

  cv::GaussianBlur(palm.PrevHandleRes(), res, cv::Size(5, 5), 0);

  palm.SetCurHandleRes(res);
  return Status::Ok();
}

}   // namespace rpr