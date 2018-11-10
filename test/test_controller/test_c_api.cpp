// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "robust-palm-roi/c_api.h"
#include "util/b64.h"

namespace {

class CApiTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  CApiTestFixture() : RobustPalmRoiTestFixtureBase(0.1) {}
  void SetUp() override {
    RobustPalmRoiTestFixtureBase::SetUp();
    cv::imencode(".png", perfect_palm_.PrevHandleRes(), perfect_palm_bytes_);
    perfect_palm_base64_ = rpr::base64_encode(perfect_palm_bytes_.data(), perfect_palm_bytes_.size());
  }

 protected:
  std::string perfect_palm_base64_;
  std::vector<uchar> perfect_palm_bytes_;
};

TEST_F(CApiTestFixture, test_init_chain) {
  void* chain = init_chain(TEST_CONFIG_YAML_FILE);
  EXPECT_TRUE(chain != NULL);
}

TEST_F(CApiTestFixture, test_chain_process_base64) {
  void* chain = init_chain(TEST_CONFIG_YAML_FILE);
  unsigned long roi_base64_max_size = 1024 * 1024;
  char roi_base64[roi_base64_max_size];   // 1 MB can store about 768 KB of image.
  char status[128];
  chain_process_base64(chain, perfect_palm_base64_.c_str(), roi_base64, roi_base64_max_size, status);
  EXPECT_EQ(status[0], '\0');

  roi_base64_max_size = 10;
  chain_process_base64(chain, perfect_palm_base64_.c_str(), roi_base64, roi_base64_max_size, status);
  EXPECT_NE(status[0], '\0');
}

TEST_F(CApiTestFixture, test_chain_process_bytes) {
  void* chain = init_chain(TEST_CONFIG_YAML_FILE);
  char* plam_bytes = new char[perfect_palm_bytes_.size()];
  for (size_t i = 0; i < perfect_palm_bytes_.size(); ++i) {
    *(plam_bytes + i) = perfect_palm_bytes_[i];
  }
  unsigned long roi_bytes_max_size = 1024 * 1024;
  char roi_bytes[roi_bytes_max_size];   // 1 MB can store about 768 KB of image.
  unsigned long roi_bytes_size = 0;
  char status[128];
  chain_process_bytes(chain, plam_bytes, perfect_palm_bytes_.size(),
                      roi_bytes, roi_bytes_max_size, &roi_bytes_size, status);
  EXPECT_EQ(status[0], '\0');
  EXPECT_GT(roi_bytes_size, 0);

  roi_bytes_max_size = 10;
  chain_process_bytes(chain, plam_bytes, perfect_palm_bytes_.size(),
                      roi_bytes, roi_bytes_max_size, &roi_bytes_size, status);
  EXPECT_NE(status[0], '\0');
}

}