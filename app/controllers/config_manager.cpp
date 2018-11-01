// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "controllers/config_manager.h"
#include <cassert>

namespace rpr {

YamlConfigManager::YamlConfigManager(const std::string& filename) {
  root_ = YAML::LoadFile(filename);
}

YAML::Node YamlConfigManager::GetHandlerChainOrder() {
  assert (!root_.IsNull());
  return root_["HandlerChain"]["order"];
}

}   // namespace rpr