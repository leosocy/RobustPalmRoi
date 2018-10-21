// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "handlers/extractor.h"
#include "utilities/imgop.h"

namespace rpr {

Status EffectiveIncircleExtractor::Extract(PalmInfoDTO& palm) {
  using utility::WarpAffineImageOperator;

  const cv::Mat& orig = palm.PrevHandleRes();
  cv::Mat dist;
  cv::distanceTransform(orig, dist, CV_DIST_L2, CV_DIST_MASK_5);
  cv::Rect scope;
  ReduceSearchScope(palm, &scope);
  cv::Point center;
  float radius;
  CalcEffectiveIncircle(dist, scope, &center, &radius);
  cv::Point base(center.x, center.y - radius);
  cv::Point refer((palm.valleys().at(1).x + palm.valleys().at(2).x) / 2,
                  (palm.valleys().at(1).y + palm.valleys().at(2).y) / 2);

  Points reflect_points;
  palm.ReflectPointsOnOrig({center, base, refer}, &reflect_points);
  cv::Point orig_center = reflect_points[0];
  cv::Point orig_refer = reflect_points[2];
  float orig_radius = utility::CalcPointDist(orig_center, reflect_points[1]) * 0.95;
  cv::Mat rect_roi = cv::Mat(palm.orig(), cv::Rect(orig_center.x - orig_radius, orig_center.y - orig_radius,
                                                   2 * orig_radius, 2 * orig_radius));
  cv::Point sub(orig_refer.x - orig_center.x, orig_center.y - orig_refer.y);
  double angle = acos(sub.y / sqrt(sub.x * sub.x + sub.y * sub.y)) / CV_PI * 180.0;
  if (sub.x < 0) {
    angle *= -1;
  }
  WarpAffineImageOperator* op = new WarpAffineImageOperator(rect_roi, angle);
  op->Do(&rect_roi);

  cv::Mat mask(cv::Mat::zeros(rect_roi.size(), CV_8UC1));
  circle(mask, cv::Point(rect_roi.cols / 2, rect_roi.rows / 2), orig_radius, cv::Scalar(255), CV_FILLED);
  cv::Mat mask_roi;
  rect_roi.copyTo(mask_roi, mask);
  palm.SetRoi(cv::Mat(mask_roi, cv::Rect(rect_roi.cols / 2 - orig_radius, rect_roi.rows / 2 - orig_radius,
                      2 * orig_radius, 2 * orig_radius)));
  return Status::Ok();
}

void EffectiveIncircleExtractor::ReduceSearchScope(PalmInfoDTO& palm, cv::Rect* rect) {
  cv::Point farleft_peak = palm.peaks().front();
  cv::Point farright_peak = palm.peaks().back();
  cv::Point middle_finger_peak = palm.peaks().at(2);
  cv::Point left_valley_at_middle_finger = palm.valleys().at(1);
  cv::Point right_valley_at_middle_finger = palm.valleys().at(2);
  cv::Point middle_finger_base = cv::Point((left_valley_at_middle_finger.x + right_valley_at_middle_finger.x) / 2,
                                            (left_valley_at_middle_finger.y + right_valley_at_middle_finger.y) / 2);
  int bottom = middle_finger_base.y + (middle_finger_base.y - middle_finger_peak.y);

  rect->x = farleft_peak.x;
  rect->y = middle_finger_peak.y;
  rect->width = farright_peak.x - farleft_peak.x;
  rect->height = palm.valleys().front().y - middle_finger_peak.y;
}

void EffectiveIncircleExtractor::CalcEffectiveIncircle(
  const cv::Mat& dist, const cv::Rect& scope, cv::Point* center, float* radius) {
  assert (center != NULL && radius != NULL);
  int scope_x = scope.x;
  int scope_y = scope.y;
  for (int h = 0; h < scope.height; ++h) {
    const float *values = dist.ptr<float>(scope_y + h);
    for (int w = 0; w < scope.width; ++w) {
      float value = *(values + w + scope_x);
      if (value > *radius) {
        *radius = value;
        center->x = w + scope_x;
        center->y = h + scope_y;
      }
    }
  }
}

}   // namespace rpr