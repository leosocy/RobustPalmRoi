// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_CHAIN_H_
#define ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_CHAIN_H_

#include <memory>
#include <list>
#include <opencv2/opencv.hpp>
#include <yaml-cpp/yaml.h>
#include "robust-palm-roi/status.h"

namespace rpr {

// Forward Declare
class Handler;
class PalmInfoDTO;
class YamlConfigManager;

class HandlerChain {
 public:
  Status Process(const cv::Mat& src, cv::Mat* roi);
  Status Process(PalmInfoDTO& palm, cv::Mat* roi);

 private:
  friend class ChainBuilder;
  HandlerChain& Join(std::shared_ptr<Handler> handler);

  std::list< std::shared_ptr<Handler> > handlers_;
};


class ChainBuilder {
 public:
  ChainBuilder();
  ~ChainBuilder();

  ChainBuilder& SetConfigYaml(const std::string& filename);
  std::unique_ptr<HandlerChain> BuildAndInitChain();

 private:
  std::unique_ptr<YamlConfigManager> config_manager_;
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_CHAIN_H_
