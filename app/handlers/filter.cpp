// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <opencv2/imgproc.hpp>
#include "handlers/filter.h"

namespace rpr {

Status GaussianFilter::Blur(const cv::Mat& orig, cv::Mat* res) {
  cv::GaussianBlur(orig, *res, cv::Size(5, 5), 0, 0, cv::BORDER_DEFAULT);
  return Status::Ok();
}

}   // namespace rpr