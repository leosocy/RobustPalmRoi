// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "robust-palm-roi/c_api.h"
#include "robust-palm-roi/chain.h"

static std::unique_ptr<rpr::HandlerChain> g_chain_ptr;

void* init_chain(const char* config_file_name) {
  rpr::ChainBuilder builder;
  builder.SetConfigYaml(config_file_name);
  g_chain_ptr = builder.BuildAndInitChain();
  return static_cast<void*>(g_chain_ptr.get());
}
