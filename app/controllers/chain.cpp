// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "controllers/chain.h"
#include <ctime>

namespace rpr {

HandlerChain& HandlerChain::Join(std::shared_ptr<Handler> handler) {
  handlers_.emplace_back(std::move(handler));
  return *this;
}

Status HandlerChain::Process(PalmInfoDTO& palm) {
  Status status(Status::Ok());
  clock_t start, end;
  auto it = handlers_.begin();
  while (it != handlers_.end() && status.IsOk()) {
    start = clock();
    status = (*it)->Handle(palm);
    end = clock();
    printf("Handler cost time: %f ms\n", double(end - start) / CLOCKS_PER_SEC * 1000);
    it++;
  }
  return status;
}


std::unique_ptr<HandlerChain> ChainBuilder::BuildAndInitChain() {
  // TODO: 从ConfigManager 加载 HandlerChain
  auto handler_factory = HandlerFactory::instance();
  auto handlers = handler_factory.handers();
  for (auto it = handlers.begin(); it != handlers.end(); ++it) {
    it->second->Init();
  }

  HandlerChain* chain = new HandlerChain();
  chain->Join(handler_factory.GetHandler("OrigNormalizer"));
  chain->Join(handler_factory.GetHandler("GaussianFilter"));
  chain->Join(handler_factory.GetHandler("LaplaceEnhancer"));
  chain->Join(handler_factory.GetHandler("OtsuBinarizer"));
  chain->Join(handler_factory.GetHandler("NoiseAdjuster"));
  chain->Join(handler_factory.GetHandler("AngleAdjuster"));
  chain->Join(handler_factory.GetHandler("PeakValleyDetector"));
  chain->Join(handler_factory.GetHandler("EffectiveIncircleExtractor"));
  chain->Join(handler_factory.GetHandler("IncircleRoiNormalizer"));

  return std::unique_ptr<HandlerChain>(chain);
}

}   // namespace rpr
