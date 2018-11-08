// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <opencv2/highgui.hpp>
#include <robust-palm-roi/chain.h>


#define SAMPLES_ROOT "../.."
const char* config_file_name = SAMPLES_ROOT"/config.yaml";
const char* palm_images[] = {
  SAMPLES_ROOT"/palm_data/left_palm_not_rotating.jpg",
  SAMPLES_ROOT"/palm_data/left_palm_left_rotating.jpg",
  SAMPLES_ROOT"/palm_data/left_palm_right_rotating.jpg"
};

int main() {

  // Use chain builder to load config and build a handler chain.
  rpr::ChainBuilder builder;
  builder.SetConfigYaml(config_file_name);
  auto chain = builder.BuildAndInitChain();

  // Extract roi from image.
  for (int i = 0; i < sizeof(palm_images) / sizeof(palm_images[0]); ++i) {
    cv::Mat palm = cv::imread(palm_images[i]);
    assert (!palm.empty());
    cv::Mat roi;
    auto status = chain->Process(palm, &roi);
    if (status.IsOk()) {
      std::string window_name = std::string(palm_images[i]).substr(std::string(palm_images[i]).rfind("/") + 1);
      cv::resize(palm, palm, cv::Size(256, palm.rows * 256 / palm.cols));
      cv::imshow(std::string("origin_") + window_name, palm);
      cv::imshow(std::string("roi_") + window_name, roi);
    }
  }
  cv::waitKey();

  return 0;
}
