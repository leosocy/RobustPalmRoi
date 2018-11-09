// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "robust-palm-roi/c_api.h"
#include "robust-palm-roi/chain.h"
#include "util/b64.h"

static std::vector< std::unique_ptr<rpr::HandlerChain> > g_chain_ptr_vec;

void* init_chain(const char* config_file_name) {
  rpr::ChainBuilder builder;
  builder.SetConfigYaml(config_file_name);
  auto chain = builder.BuildAndInitChain();
  g_chain_ptr_vec.emplace_back(std::move(chain));
  return reinterpret_cast<void*>(g_chain_ptr_vec.back().get());
}

void chain_process_base64(void* chain_ptr, const char* palm_base64,
                          char* roi_base64, char* status_ptr) {
  rpr::HandlerChain* chain = reinterpret_cast<rpr::HandlerChain*>(chain_ptr);
  // base64 string to mat
  auto bytes = rpr::base64_decode(palm_base64);
  cv::Mat palm(cv::imdecode(bytes, 1));
  cv::Mat roi;

  auto status = chain->Process(palm, &roi);
  // mat to base64 string
  std::vector<uchar> roi_bytes;
  cv::imencode(".png", roi, roi_bytes);
  std::string roi_b64_str = rpr::base64_encode(roi_bytes.data(), roi_bytes.size());

  for (size_t i = 0; i < roi_b64_str.size(); ++i) {
    *roi_base64++ = roi_b64_str[i];
  }
  *roi_base64 = '\0';

  *status_ptr++ = status.code();
  for (size_t i = 0; i < std::string(status.msg()).length(); ++i) {
    *status_ptr++ = std::string(status.msg())[i];
  }
  *status_ptr = '\0';
}

void chain_process_bytes(void* chain_ptr,
                         const char* palm_bytes, unsigned long palm_bytes_size,
                         char* roi_bytes, unsigned long* roi_bytes_size,
                         char* status_ptr) {
  rpr::HandlerChain* chain = reinterpret_cast<rpr::HandlerChain*>(chain_ptr);
  // bytes to vector
  std::vector<uchar> p_bytes;
  for (size_t i = 0; i < palm_bytes_size; ++i) {
    p_bytes.push_back(*(palm_bytes + i));
  }
  cv::Mat palm(cv::imdecode(p_bytes, 1));
  cv::Mat roi;

  auto status = chain->Process(palm, &roi);
  std::vector<uchar> r_bytes;
  cv::imencode(".png", roi, r_bytes);

  *roi_bytes_size = r_bytes.size();
  for (size_t i = 0; i < r_bytes.size(); ++i) {
    *roi_bytes++ = r_bytes[i];
  }

  *status_ptr++ = status.code();
  for (size_t i = 0; i < std::string(status.msg()).length(); ++i) {
    *status_ptr++ = std::string(status.msg())[i];
  }
  *status_ptr = '\0';
}
