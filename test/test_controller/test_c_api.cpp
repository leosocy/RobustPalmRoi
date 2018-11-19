// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#include "test_base.h"
#include "robust-palm-roi/c_api.h"

namespace {

class CApiTestFixture : public RobustPalmRoiTestFixtureBase {
 public:
  CApiTestFixture() : RobustPalmRoiTestFixtureBase(0.1) {}
  void SetUp() override {
    RobustPalmRoiTestFixtureBase::SetUp();
    cv::imencode(".png", perfect_palm_.PrevHandleRes(), perfect_palm_bytes_);
  }

 protected:
  std::vector<uchar> perfect_palm_bytes_;
};

TEST_F(CApiTestFixture, test_init_chain) {
  void* chain = init_chain(TEST_CONFIG_YAML_FILE);
  EXPECT_TRUE(chain != NULL);
}

TEST_F(CApiTestFixture, test_chain_process_bytes) {
  void* chain = init_chain(TEST_CONFIG_YAML_FILE);
  char* palm_bytes = new char[perfect_palm_bytes_.size()];
  memcpy(palm_bytes, perfect_palm_bytes_.data(), perfect_palm_bytes_.size());
  unsigned long roi_bytes_max_size = 1024 * 1024;
  char roi_bytes[roi_bytes_max_size];
  unsigned long roi_bytes_size = 0;
  char status[128];
  chain_process_bytes(chain, palm_bytes, perfect_palm_bytes_.size(),
                      roi_bytes, roi_bytes_max_size, &roi_bytes_size, status);
  EXPECT_EQ(status[0], '\0');
  EXPECT_GT(roi_bytes_size, 0);

  roi_bytes_max_size = 10;
  chain_process_bytes(chain, palm_bytes, perfect_palm_bytes_.size(),
                      roi_bytes, roi_bytes_max_size, &roi_bytes_size, status);
  EXPECT_NE(status[0], '\0');
}

}