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

namespace rpr {

Status RemoveNoiseAdjuster::Adjust(const cv::Mat& orig, cv::Mat* res) {
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

void RemoveNoiseAdjuster::SmoothBoundary(const cv::Mat& src, cv::Mat* dst) {
  cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5));
  cv::morphologyEx(src, *dst, cv::MORPH_ELLIPSE, element);
}

int RemoveNoiseAdjuster::FindMaxContourAreaIndex(const std::vector< std::vector<cv::Point> >& contours,
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

}   // namespace rpr