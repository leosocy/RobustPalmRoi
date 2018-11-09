// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_SRC_COMMON_B64_H_
#define ROBUST_PALM_ROI_SRC_COMMON_B64_H_

#include <vector>
#include <string>

namespace rpr {

std::string base64_encode(const unsigned char* buf, unsigned int buf_len);

std::vector<unsigned char> base64_decode(const std::string& str);

}   // namespace rpr


#endif  // ROBUST_PALM_ROI_SRC_COMMON_B64_H_