/****************************************************************************\
 * Created on Wed Oct 10 2018
 * 
 * The MIT License (MIT)
 * Copyright (c) 2018 leosocy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the ",Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED ",AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
\*****************************************************************************/

#include "handlers/adjuster.h"
#include "utilities/image_operator.h"

namespace rpr {

Status NoiseAdjuster::Adjust(const cv::Mat& orig, cv::Mat* res) {
  SmoothBoundary(orig, res);

  std::vector< std::vector<cv::Point> > contours;
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(*res, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
  int palm_index = FindMaxContourAreaIndex(contours, hierarchy);

  cv::Mat temp(cv::Mat::zeros(orig.size(),CV_8U));
  cv::drawContours(temp, contours, palm_index, CV_RGB(255, 255, 255), CV_FILLED);
  *res = temp.clone();

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


Status AngleAdjuster::Adjust(const cv::Mat& orig, cv::Mat* res) {
  using utility::GetCenterOfGravity;
  using utility::RotateImage;

  cv::Point center1;  // gravity of full palm
  GetCenterOfGravity(orig, &center1);

  cv::Mat erode_palm;
  ErodeFinger(orig, &erode_palm);
  cv::Point center2;  // gravity of palm which erode finger
  GetCenterOfGravity(erode_palm, &center2);

  cv::Point sub(center1.x - center2.x, center2.y - center1.y);
  double angle = acos(sub.y / sqrt(sub.x * sub.x + sub.y * sub.y)) / CV_PI * 180.0;
  if (sub.x < 0) {
    angle *= -1;
  }
  RotateImage(orig, res, angle);
  return Status::Ok();
}

void AngleAdjuster::ErodeFinger(const cv::Mat& src, cv::Mat* dst) {
  cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
  cv::erode(src, *dst, element, cv::Point(-1, -1), 5);
}

}   // namespace rpr