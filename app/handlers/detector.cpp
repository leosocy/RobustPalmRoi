// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <vector>
#include "handlers/detector.h"

namespace rpr {

bool Detector::ImageOneContour(const cv::Mat& src) {
  std::vector< std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(src, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
  if (contours.size() == 1) {
    palm_contour_ = contours[0];
  }
  return contours.size() == 1;
}


Status PeakValleyDetector::Detect(const cv::Mat& orig, cv::Mat* res) {
  peaks_.emplace_back(palm_contour_[0]);
  FindHalfSideInflectionPoints(PalmSide::LEFT);
  FindHalfSideInflectionPoints(PalmSide::RIGHT);

  if (peaks_.size() + valleys_.size() < 9) {
    return Status::ImageLowQualityError("Can't detect all peaks and valleys, please open your fingers");
  }
  for (size_t i = 0; i < peaks_.size() - 1; ++i) {
    if ((peaks_[i].x > peaks_[i + 1].x)) {
      return Status::ImageLowQualityError();
    }
  }
  if (!(peaks_[2].y < peaks_[1].y && peaks_[2].y < peaks_[3].y)
      || !(peaks_[1].y < peaks_[0].y && peaks_[3].y < peaks_[4].y)) {
    return Status::ImageLowQualityError();
  }
  for (size_t i = 0; i < valleys_.size() - 1; ++i) {
    if ((valleys_[i].x > valleys_[i + 1].x)) {
      return Status::ImageLowQualityError();
    }
  }
  return Status::Ok();
}

void PeakValleyDetector::FindHalfSideInflectionPoints(PalmSide side) {
  int step = 8 * static_cast<int>(side);
  size_t from = (side == PalmSide::LEFT ? 0 : palm_contour_.size() - 1);
  size_t to = palm_contour_.size() / 2;
  size_t founded = 0;
  bool is_peak = false;
  for (from += 2 * step;
       static_cast<int>(side) * from < static_cast<int>(side) * to;
       from += step, is_peak = !is_peak) {
    cv::Point point;
    from = FindNextInflectionPoint(palm_contour_, from, to, step, !is_peak, &point);
    if (from == 0) {
      break;
    }
    if (side == PalmSide::LEFT) {
      is_peak ? peaks_.insert(peaks_.begin(), point) : valleys_.insert(valleys_.begin(), point);
    } else {
      is_peak ? peaks_.emplace_back(point) : valleys_.emplace_back(point);
    }
    founded += 1;

    from += 2 * step;
    if (founded >= 4) {
      break;
    }
  }
}

size_t PeakValleyDetector::FindNextInflectionPoint(const std::vector<cv::Point>& contour,
                                                   size_t from_index, size_t to_index, int step, bool is_maximum,
                                                   cv::Point* point) {
  assert (point != NULL && step != 0);
  int reverse = (step > 0 ? 1 : -1);  // 顺时针/逆时针 遍历
  int sign = (is_maximum ? 1 : -1);
  size_t cur = from_index + step;
  for (; reverse * cur < reverse * to_index; cur += step) {
    if (sign * contour[cur].y <= sign * contour[cur - step].y
        && reverse * contour[cur].x < reverse * contour[cur - step].x) {
      size_t index;
      int datum = (is_maximum ? INT_MIN : INT_MAX);
      for (size_t i = cur - step; reverse * i <= reverse * cur; i += reverse) {
        if (sign * palm_contour_[i].y > sign * datum) {
          datum = palm_contour_[i].y;
          index = i;
        }
      }
      point->x = palm_contour_[index].x;
      point->y = palm_contour_[index].y;
      return index;
    }
  }
  return 0;
}

}   // namespace rpr