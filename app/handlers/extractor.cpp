// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "handlers/extractor.h"
#include "handlers/detector.h"
#include "utilities/imgop.h"

namespace rpr {

Status EffectiveIncircleExtractor::Init() {
}

Status EffectiveIncircleExtractor::Extract(PalmInfoDTO& palm) {
  const cv::Mat& orig = palm.PrevHandleRes();
  cv::Mat dist;
  cv::distanceTransform(orig, dist, CV_DIST_L2, CV_DIST_MASK_3);
  cv::Rect scope;
  ReduceSearchScope(palm, &scope);

  cv::Point center;
  float radius;
  double angle;
  CalcEffectiveIncircle(dist, scope, &center, &radius);
  ReflectIncircleOnOrig(palm, &center, &radius, &angle);
  cv::Mat rect_roi = cv::Mat(palm.orig(), cv::Rect(center.x - radius, center.y - radius,
                                                   2 * radius, 2 * radius));

  palm.SetRoiAngle(angle);
  palm.SetRoi(cv::Mat(rect_roi, cv::Rect(rect_roi.cols / 2 - radius, rect_roi.rows / 2 - radius,
                                         2 * radius, 2 * radius)));
  return Status::Ok();
}

void EffectiveIncircleExtractor::ReduceSearchScope(PalmInfoDTO& palm, cv::Rect* rect) {
  cv::Point farleft_valley = palm.valleys().front();
  cv::Point left_valley = palm.valleys().at(1);
  cv::Point farleft_peak = palm.peaks().front();
  cv::Point farright_peak = palm.peaks().back();
  cv::Point middle_finger_peak = palm.peaks().at(2);
  rect->x = farleft_valley.x;
  rect->y = left_valley.y;
  rect->width = farright_peak.x - farleft_peak.x;
  rect->height = farleft_valley.y - left_valley.y;
}

void EffectiveIncircleExtractor::CalcEffectiveIncircle(
    const cv::Mat& dist, const cv::Rect& scope, cv::Point* center, float* radius) {
  assert (center != NULL && radius != NULL);
  int scope_x = scope.x;
  int scope_y = scope.y;
  for (int h = 0; h < scope.height; ++h) {
    const float* values = dist.ptr<float>(scope_y + h);
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

void EffectiveIncircleExtractor::ReflectIncircleOnOrig(
    PalmInfoDTO& palm, cv::Point* center, float* radius, double* angle) {
  using utility::CalcPointDist;

  cv::Point base(center->x, center->y - *radius);
  cv::Point refer((palm.valleys().at(1).x + palm.valleys().at(2).x) / 2,
                  (palm.valleys().at(1).y + palm.valleys().at(2).y) / 2);
  Points reflect_points;
  palm.ReflectPointsOnOrig({*center, base, refer}, &reflect_points);
  *center = reflect_points[0];
  refer = reflect_points[2];
  *radius = CalcPointDist(*center, reflect_points[1]) * 0.95;
  cv::Point sub(refer.x - center->x, center->y - refer.y);
  *angle = acos(sub.y / sqrt(sub.x * sub.x + sub.y * sub.y)) / CV_PI * 180.0;
  if (sub.x < 0) {
    *angle *= -1;
  }
}

}   // namespace rpr