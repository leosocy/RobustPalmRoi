# RobustPalmRoi: An algorithm of ROI extraction for palm ***captured by mobile phone***

[![Build Status](https://travis-ci.org/Leosocy/RobustPalmRoi.svg?branch=master)](https://travis-ci.org/Leosocy/RobustPalmRoi)
[![codecov](https://codecov.io/gh/Leosocy/RobustPalmRoi/branch/master/graph/badge.svg)](https://codecov.io/gh/Leosocy/RobustPalmRoi)
[![MIT licensed](https://img.shields.io/badge/license-MIT-green.svg)](https://raw.githubusercontent.com/Leosocy/RobustPalmRoi/master/LICENSE)

The palm image captured by the mobile phone has differences in angle, illumination, etc. The `RobustPalmRoi` algorithm reduces these differences through a series of handlers, thus extracting a stable ROI.

The following palms are captured by iPhoneX and have different angles. The corresponding ROI is below it.

![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/original_palm_set.jpg)
![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/roi_palm_set.jpg)

Advantages of `RobustPalmRoi` algorithm:

1. ***Lower*** extraction requirements, just use your mobile phone.
1. ***Faster*** extraction speed, just tens of milliseconds.
1. ***Higher*** extraction stability, eliminate the differences such as angle, illumination, etc.

Some *tips* for capturing palms on mobile phones:

1. Five fingers open.
1. Capture the whole palm.
1. As much light as possible.

## Installation

There are ***some requirements*** if you want to install `RobustPalmRoi`:

- OS Linux/Unix like.
- [`OpenCV`](https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html) installed.
- [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) installed.

*Steps:*

1. `git clone https://github.com/Leosocy/RobustPalmRoi.git`
1. `cd RobustPalmRoi && mkdir -p build && cd build`
1. `cmake .. && sudo make install`

## Usage

### C++

In your CMakeLists.txt, add these lines:

```cmake
add_definitions(-std=c++11)
find_package(robust-palm-roi REQUIRED)
include_directories(${ROBUST_PALM_ROI_INCLUDE_DIR})
...
add_dependencies(${YOUR_PROJECT} ${ROBUST_PALM_ROI_LIBRARIES})
target_link_libraries(${YOUR_PROJECT} ${ROBUST_PALM_ROI_LIBRARIES})
```

Then you can use it in your source code like this:

```c++
#include <opencv2/highgui.hpp>
#include <robust-palm-roi/chain.h>

int main() {
  rpr::ChainBuilder builder;
  builder.SetConfigYaml(config_file_name);
  auto chain = builder.BuildAndInitChain();

  cv::Mat img = cv::imread(palm_image_file_name);
  cv::Mat roi;
  auto status = chain->Process(img, &roi);
  if (status.IsOk()) {
    cv::imshow("roi", roi);
  }

  return 0;
}
```

You can find the detail under `samples/cpp_sample` directory.

- Python

## Run samples

Make sure you have installed `RobustPalmRoi` before running examples.

### Run cpp sample

### Run python sample

## License

Please see [LICENSE](https://github.com/Leosocy/RobustPalmRoi/blob/master/LICENSE)

## Contribute
