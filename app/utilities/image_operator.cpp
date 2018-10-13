/****************************************************************************\
 * Created on Fri Oct 12 2018
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

#include "utilities/image_operator.h"

namespace rpr {

namespace utility {

void GetCenterOfGravity(const cv::Mat& src, cv::Point* center, bool is_binary) {
  cv::Moments moment = cv::moments(src, is_binary);
  center->x = moment.m10 / moment.m00;
  center->y = moment.m01 / moment.m00;
}

void RotateImage(const cv::Mat& src, cv::Mat* dst, double angle) {
  double radian = angle / 180.0 * CV_PI;
  double sin_value = fabs(sin(radian));
  double cos_value = fabs(cos(radian));

  int diagonal = sqrt(src.cols * src.cols + src.rows * src.rows);
  int target_width = src.cols * cos_value + src.rows * sin_value;
  int target_height = src.rows * cos_value + src.cols * sin_value;
  cv::Rect target_rect((diagonal - target_width) / 2, (diagonal - target_height) / 2,
                       target_width, target_height);

  cv::Mat temp(diagonal, diagonal, src.type(), cv::Scalar());
  cv::Mat roi(temp, cv::Rect((diagonal - src.cols) / 2, (diagonal - src.rows) / 2, src.cols, src.rows));
  src.copyTo(roi);

  cv::Mat affine = cv::getRotationMatrix2D(cv::Point2f(diagonal / 2.0, diagonal / 2.0), angle, 1.0);
  cv::warpAffine(temp, *dst, affine, temp.size());
  *dst = cv::Mat(*dst, target_rect);
}

}   // namespace utility

}   // namespace rpr