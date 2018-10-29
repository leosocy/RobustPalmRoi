// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "handlers/normalizer.h"

namespace rpr {

Status OrigNormalizer::Handle(PalmInfoDTO& palm) {
  using utility::ResizeImageOperator;

  const cv::Mat& orig = palm.PrevHandleRes();
  cv::Mat res;
  ResizeImageOperator *op = new ResizeImageOperator(orig, width_ == 0 ? scaling_ * orig.cols : width_);
  op->Do(&res);

  palm.SetCurHandleRes(res);
  palm.SetImageOperator(std::unique_ptr<rpr::utility::ImageOperator>(op));
  return Status::Ok();
}


Status IncircleRoiNormalizer::Normalize(PalmInfoDTO& palm) {
  const cv::Mat& roi(palm.roi());
  cv::Mat balance_roi;
  ColorBalance(roi, &balance_roi);
  cv::Mat mask_roi;
  MaskIncircle(balance_roi, &mask_roi);
  
  palm.SetRoi(mask_roi);
  return Status::Ok();
}

void IncircleRoiNormalizer::MaskIncircle(const cv::Mat& src, cv::Mat* dst) {
  int radius = src.cols / 2;
  cv::Mat mask(cv::Mat::zeros(src.size(), CV_8UC1));
  circle(mask, cv::Point(src.cols / 2, src.rows / 2), radius, cv::Scalar(255), CV_FILLED);
  src.copyTo(*dst, mask);
}

void IncircleRoiNormalizer::ColorBalance(const cv::Mat& src, cv::Mat* dst) {
  std::vector<cv::Mat> rgb;
	split(src, rgb);

	double r, g, b;
	b = cv::mean(rgb[0])[0];
	g = cv::mean(rgb[1])[0];
	r = cv::mean(rgb[2])[0];

	double kr, kg, kb;
	kb = (r + g + b) / (3 * b);
	kg = (r + g + b) / (3 * g);
	kr = (r + g + b) / (3 * r);

	rgb[0] = rgb[0] * kb;
	rgb[1] = rgb[1] * kg;
	rgb[2] = rgb[2] * kr;

	merge(rgb, *dst);
}

}   // namespace rpr