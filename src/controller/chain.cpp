// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "robust-palm-roi/chain.h"
#include <ctime>
#include "common/palm.h"
#include "handler/registry.h"

namespace rpr {

HandlerChain& HandlerChain::Join(std::shared_ptr<Handler> handler) {
  handlers_.emplace_back(std::move(handler));
  return *this;
}

Status HandlerChain::Process(const cv::Mat& src, cv::Mat* roi) {
  PalmInfoDTO palm(src);
  return Process(palm, roi);
}

Status HandlerChain::Process(PalmInfoDTO& palm, cv::Mat* roi) {
  Status status(Status::Ok());
  clock_t start, end;
  double total_cost = 0.0;
  auto it = handlers_.begin();
  while (it != handlers_.end() && status.IsOk()) {
    start = clock();
    status = (*it)->Handle(palm);
    end = clock();
    double cost = double(end - start) / CLOCKS_PER_SEC * 1000;
    total_cost += cost;
    printf("%s cost time: %f ms\n", (*it)->name(), cost);
    it++;
  }
  printf("HandlerChain total cost time: %lf ms\n", total_cost);
  *roi = palm.roi().clone();

  return status;
}


ChainBuilder& ChainBuilder::SetConfigYaml(const std::string& filename) {
  YamlConfigManager* manager = new YamlConfigManager(filename);
  config_manager_ = std::unique_ptr<YamlConfigManager>(manager);
  return *this;
}

std::unique_ptr<HandlerChain> ChainBuilder::BuildAndInitChain() {
  assert (config_manager_.get() != nullptr);
  auto handlers_config = config_manager_->GetHandlerChainOrder();
  HandlerChain* chain = new HandlerChain();

  for (auto handler_config : handlers_config) {
    const std::string& name = handler_config["type"].as<std::string>();
    auto handler = HandlerFactory::instance().GetHandler(name);
    handler->Init(handler_config["parameters"]);
    chain->Join(handler);
  }

  return std::unique_ptr<HandlerChain>(chain);
}

}   // namespace rpr
