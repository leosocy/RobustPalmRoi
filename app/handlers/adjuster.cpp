// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "handlers/adjuster.h"
#include "utilities/imgop.h"

namespace rpr {

Status NoiseAdjuster::Adjust(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes();
  cv::Mat res;

  SmoothBoundary(orig, &res);

  std::vector< std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(res, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
  int palm_index = FindMaxContourAreaIndex(contours, hierarchy);

  cv::Mat temp(cv::Mat::zeros(orig.size(),CV_8U));
  cv::drawContours(temp, contours, palm_index, CV_RGB(255, 255, 255), CV_FILLED);
  res = temp.clone();

  palm.SetCurHandleRes(res);
  return Status::Ok();
}

void NoiseAdjuster::SmoothBoundary(const cv::Mat& src, cv::Mat* dst) {
  cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
  cv::morphologyEx(src, *dst, cv::MORPH_ELLIPSE, element);
}

int NoiseAdjuster::FindMaxContourAreaIndex(const std::vector< std::vector<cv::Point> >& contours,
                                           const std::vector<cv::Vec4i>& hierarchy) {
  double max_con_area = 0.0;
  int max_con_index = 0;
  for (int index = 0; index >= 0; index = hierarchy[index][0]) {
    double con_area = cv::contourArea(contours[index]);
    if (con_area > max_con_area) {
      max_con_area = con_area;
      max_con_index = index;
    }
  }
  return max_con_index;
}


Status AngleAdjuster::Adjust(PalmInfoDTO& palm) {
  using utility::GetCenterOfGravity;
  using utility::WarpAffineImageOperator;

  const cv::Mat& orig = palm.PrevHandleRes();
  cv::Mat res;

  cv::Point center1;  // gravity of full palm
  GetCenterOfGravity(orig, &center1);

  cv::Mat erode_palm;
  ErodeFinger(orig, &erode_palm);
  cv::Point center2;  // gravity of palm which erode finger
  GetCenterOfGravity(erode_palm, &center2);

  cv::Point sub(center1.x - center2.x, center2.y - center1.y);
  if ((sub.x == 0 && sub.y == 0) || (sub.x >= orig.cols) || (sub.y >= orig.rows)) {
    return Status::ImageLowQualityError("The quality of the palm in the image "
                                        "does not meet the extraction requirements.");
  }
  double angle = acos(sub.y / sqrt(sub.x * sub.x + sub.y * sub.y)) / CV_PI * 180.0;
  if (sub.x < 0) {
    angle *= -1;
  }
  WarpAffineImageOperator* op = new WarpAffineImageOperator(orig, angle);
  op->Do(&res);

  palm.SetCurHandleRes(res);
  palm.SetImageOperator(std::unique_ptr<WarpAffineImageOperator>(op));
  return Status::Ok();
}

void AngleAdjuster::ErodeFinger(const cv::Mat& src, cv::Mat* dst) {
  cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
  cv::erode(src, *dst, element, cv::Point(-1, -1), 5);
}

}   // namespace rpr