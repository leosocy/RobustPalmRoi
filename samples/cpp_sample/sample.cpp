// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <opencv2/opencv.hpp>
#include <robust-palm-roi/chain.h>


#define TEST_ROOT "../../../test"
const char* config_file_name = TEST_ROOT"/config.yaml";
const char* palm_image_file_name = TEST_ROOT"/palm_data/palm_perfect.jpg";

int main() {
  using rpr::ChainBuilder;

  ChainBuilder builder;
  builder.SetConfigYaml(config_file_name);
  auto chain = builder.BuildAndInitChain();

  cv::Mat img = cv::imread(palm_image_file_name);
  cv::Mat roi;
  auto status = chain->Process(img, &roi);
  printf("Handle result: status[%d]\tmsg[%s]\n", static_cast<int>(status.code()), status.msg());
  printf("roi size (%d, %d)\n", roi.cols, roi.rows);

  return 0;
}
