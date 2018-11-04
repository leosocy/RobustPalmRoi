// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "handler/enhancer.h"

namespace rpr {

Status LaplaceEnhancer::Enhance(PalmInfoDTO& palm) {
  cv::Mat res;
  cv::Mat kernel = (cv::Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
  const cv::Mat& orig = palm.PrevHandleRes();

  cv::filter2D(orig, res, orig.depth(), kernel);

  palm.SetCurHandleRes(res);
  return Status::Ok();
}

}   // namespace rpr
