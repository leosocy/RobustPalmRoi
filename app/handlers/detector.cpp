// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <vector>
#include "handlers/detector.h"

namespace rpr {

bool Detector::ImageOneContour(PalmInfoDTO& palm) {
  std::vector< std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(palm.PrevHandleRes(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
  if (contours.size() == 1) {
    palm.SetContour(contours[0]);
  }
  return contours.size() == 1;
}


Status PeakValleyDetector::Detect(PalmInfoDTO& palm) {
  Points peaks, valleys;
  const Points& contour = palm.contour();

  peaks.emplace_back(contour[0]);
  FindHalfSideInflectionPoints(contour, PalmSide::LEFT, peaks, valleys);
  FindHalfSideInflectionPoints(contour, PalmSide::RIGHT, peaks, valleys);

  if (peaks.size() + valleys.size() < 9) {
    return Status::ImageLowQualityError("Can't detect all peaks and valleys, please open your fingers");
  }
  for (size_t i = 0; i < peaks.size() - 1; ++i) {
    if ((peaks[i].x > peaks[i + 1].x)) {
      return Status::ImageLowQualityError();
    }
  }
  if (!(peaks[2].y < peaks[1].y && peaks[2].y < peaks[3].y)
      || !(peaks[1].y < peaks[0].y && peaks[3].y < peaks[4].y)) {
    return Status::ImageLowQualityError();
  }
  for (size_t i = 0; i < valleys.size() - 1; ++i) {
    if ((valleys[i].x > valleys[i + 1].x)) {
      return Status::ImageLowQualityError();
    }
  }

  palm.SetPeakValley(peaks, valleys);
  return Status::Ok();
}

void PeakValleyDetector::FindHalfSideInflectionPoints(const Points& contour, PalmSide side,
                                                      Points& peaks, Points& valleys) {
  int step = 8 * static_cast<int>(side);
  size_t from = (side == PalmSide::LEFT ? 0 : contour.size() - 1);
  size_t to = contour.size() / 2;
  size_t founded = 0;
  bool is_peak = false;
  for (from += 2 * step;
       static_cast<int>(side) * from < static_cast<int>(side) * to;
       from += step, is_peak = !is_peak) {
    from = FindNextInflectionPoint(contour, from, to, step, !is_peak);
    if (from == 0) {
      break;
    }
    cv::Point point(contour[from]);
    if (side == PalmSide::LEFT) {
      is_peak ? peaks.insert(peaks.begin(), point) : valleys.insert(valleys.begin(), point);
    } else {
      is_peak ? peaks.emplace_back(point) : valleys.emplace_back(point);
    }
    founded += 1;

    from += 2 * step;
    if (founded >= 4) {
      break;
    }
  }
}

size_t PeakValleyDetector::FindNextInflectionPoint(const Points& contour, size_t from_index, size_t to_index,
                                                   int step, bool is_maximum) {
  assert (step != 0);
  int reverse = (step > 0 ? 1 : -1);  // 顺时针/逆时针 遍历
  int sign = (is_maximum ? 1 : -1);
  size_t cur = from_index + step;
  for (; reverse * cur < reverse * to_index; cur += step) {
    if (sign * contour[cur].y <= sign * contour[cur - step].y
        && reverse * contour[cur].x < reverse * contour[cur - step].x) {
      size_t index;
      int datum = (is_maximum ? INT_MIN : INT_MAX);
      for (size_t i = cur - step; reverse * i <= reverse * cur; i += reverse) {
        if (sign * contour[i].y > sign * datum) {
          datum = contour[i].y;
          index = i;
        }
      }
      return index;
    }
  }
  return 0;
}

}   // namespace rpr