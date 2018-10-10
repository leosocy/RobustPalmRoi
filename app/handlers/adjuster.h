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

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_ADJUSTER_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_ADJUSTER_H_

#include "handlers/handler.h"

namespace rpr {

class Adjuster : public Handler {
 public:
  virtual Status Handle(const cv::Mat& orig, cv::Mat* res);
 private:
  bool IsOrigMatBinary(const cv::Mat& orig);
  virtual Status Adjust(const cv::Mat& orig, cv::Mat* res) = 0;
}

inline Status Handle(const cv::Mat& orig, cv::Mat* res) {
  assert (res != NULL);
  if (orig.empty() || orig.channels() != 1
      || !IsOrigMatBinary(orig)) {
    return Status::LoadImageError("Original palm image must be binary.");
  }
  return Status::Ok();
}

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_HANDLERS_ADJUSTER_H_