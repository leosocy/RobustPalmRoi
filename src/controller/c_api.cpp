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

void chain_process_base64(
    void* chain_ptr, const char* palm_base64,
    char* roi_base64, unsigned long roi_base64_max_size,
    char* status_ptr) {
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

  if (roi_b64_str.size() > roi_base64_max_size - 1) {
    status = rpr::Status::CApiOutBufferInsufficient(
      "The size of roi base64 buffer is insufficient.");
  } else {
    memcpy(roi_base64, roi_b64_str.c_str(), roi_b64_str.size() + 1);
  }
  *status_ptr++ = status.code();
  memcpy(status_ptr, status.msg(), strlen(status.msg()) + 1);
}

void chain_process_bytes(
    void* chain_ptr, const char* palm_bytes, unsigned long palm_bytes_size,
    char* roi_bytes, unsigned long roi_bytes_max_size, unsigned long* roi_bytes_size,
    char* status_ptr) {
  rpr::HandlerChain* chain = reinterpret_cast<rpr::HandlerChain*>(chain_ptr);

  std::vector<uchar> vp_bytes;
  for (size_t i = 0; i < palm_bytes_size; ++i) {
    vp_bytes.push_back(*(palm_bytes + i));
  }
  cv::Mat palm(cv::imdecode(vp_bytes, 1));
  cv::Mat roi;
  auto status = chain->Process(palm, &roi);
  std::vector<uchar> vr_bytes;
  cv::imencode(".png", roi, vr_bytes);

  if (vr_bytes.size() > roi_bytes_max_size) {
    status = rpr::Status::CApiOutBufferInsufficient(
      "The size of roi bytes buffer is insufficient.");
  } else {
    *roi_bytes_size = vr_bytes.size();
    memcpy(roi_bytes, &vr_bytes[0], vr_bytes.size());
  }
  *status_ptr++ = status.code();
  memcpy(status_ptr, status.msg(), strlen(status.msg()) + 1);
}
