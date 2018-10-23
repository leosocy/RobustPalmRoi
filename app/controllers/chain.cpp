// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "controllers/chain.h"
#include <ctime>


namespace rpr {

HandlerChain& HandlerChain::Join(std::unique_ptr<Handler> handler) {
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

}   // namespace rpr
