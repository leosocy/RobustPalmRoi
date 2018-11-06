// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <opencv2/highgui.hpp>
#include <robust-palm-roi/chain.h>


#define TEST_ROOT "../../../test"
const char* config_file_name = TEST_ROOT"/config.yaml";
const char* palm_image_file_name = TEST_ROOT"/palm_data/palm_perfect.jpg";

int main() {

  // Use chain builder to load config and build a handler chain.
  rpr::ChainBuilder builder;
  builder.SetConfigYaml(config_file_name);
  auto chain = builder.BuildAndInitChain();

  // Extract roi from image.
  cv::Mat img = cv::imread(palm_image_file_name);
  cv::Mat roi;
  auto status = chain->Process(img, &roi);
  if (status.IsOk()) {
    cv::imshow("from image", roi);
    cv::waitKey();
  }

  // Extract roi from video.

  // Extract roi from camera.

  return 0;
}
