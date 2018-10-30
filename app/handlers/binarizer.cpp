// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "handlers/binarizer.h"

namespace rpr {

REGISTER_HANDLER(OtsuBinarizer);

Status OtsuBinarizer::Init() {
}

Status OtsuBinarizer::Binary(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes();
  cv::Mat res;

  if (orig.channels() == 3) {
    cv::Mat ycrcb, mv[3];
    cv::cvtColor(orig, ycrcb, CV_BGR2YCrCb);
    cv::split(ycrcb, mv);
    cv::threshold(mv[1], res, 0, 255, CV_THRESH_OTSU);
  } else {
    cv::threshold(orig, res, 0, 255, CV_THRESH_OTSU);
  }

  palm.SetCurHandleRes(res);
  return Status::Ok();
}

}   // namespace rpr