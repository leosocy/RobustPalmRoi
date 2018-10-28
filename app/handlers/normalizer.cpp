// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "handlers/normalizer.h"
#include "utilities/imgop.h"

namespace rpr {

using utility::ResizeImageOperator;

Status OrigNormalizer::Handle(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes();
  cv::Mat res;
  ResizeImageOperator *op = new ResizeImageOperator(orig, width_ == 0 ? scaling_ * orig.cols : width_);
  op->Do(&res);

  palm.SetCurHandleRes(res);
  palm.SetImageOperator(std::unique_ptr<rpr::utility::ImageOperator>(op));
  return Status::Ok();
}


Status IncircleRoiNormalizer::Normalize(PalmInfoDTO& palm) {
  cv::Mat roi(palm.roi());
  int radius = roi.cols / 2;

  cv::Mat mask(cv::Mat::zeros(roi.size(), CV_8UC1));
  circle(mask, cv::Point(roi.cols / 2, roi.rows / 2), radius, cv::Scalar(255), CV_FILLED);
  cv::Mat mask_roi;
  roi.copyTo(mask_roi, mask);
  ResizeImageOperator op(mask_roi, width_);
  op.Do(&mask_roi);

  palm.SetRoi(mask_roi);
  return Status::Ok();
}

}   // namespace rpr