// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include <ctime>
#include "controllers/chain.h"


namespace rpr {

HandlerChain& HandlerChain::Join(std::unique_ptr<Handler> handler) {
  handlers_.emplace_back(std::move(handler));
  return *this;
}

Status HandlerChain::Process(const cv::Mat& orig, cv::Mat* res) {
  cv::Mat temp(orig.clone());
  Status status(Status::Ok());
  clock_t start, end;
  auto it = handlers_.begin();
  while (it != handlers_.end() && status.IsOk()) {
    start = clock();
    status = (*it)->Handle(temp, &temp);
    end = clock();
    printf("Handler cost time: %f ms\n", double(end - start) / CLOCKS_PER_SEC * 1000);
    it++;
  }
  *res = temp.clone();
  return status;
}

}   // namespace rpr
