// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_CONTROLLERS_CONFIG_MANAGER_H_
#define ROBUST_PALM_ROI_APP_CONTROLLERS_CONFIG_MANAGER_H_


#include <list>
#include <yaml-cpp/yaml.h>

namespace rpr {

class YamlConfigManager {
 public:
  YamlConfigManager(const std::string& file);
  YAML::Node GetHandlerChainOrder();

 private:
  YAML::Node root_;
};

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_CONTROLLERS_CONFIG_MANAGER_H_