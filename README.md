# A robust algorithm for extracting ROI from palm image ***taken by mobile phone***

[![Build Status](https://travis-ci.org/Leosocy/RobustPalmRoi.svg?branch=master)](https://travis-ci.org/Leosocy/RobustPalmRoi)
[![codecov](https://codecov.io/gh/Leosocy/RobustPalmRoi/branch/master/graph/badge.svg)](https://codecov.io/gh/Leosocy/RobustPalmRoi)
[![Python version](https://img.shields.io/badge/python-3.4⤴️-brightgreen.svg)](https://github.com/Leosocy/RobustPalmRoi/tree/master/pypackage)
[![Tag](https://img.shields.io/badge/tag-v0.1.0-brightgreen.svg)](https://github.com/Leosocy/RobustPalmRoi/releases/tag/v0.1.0)
[![MIT licensed](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://raw.githubusercontent.com/Leosocy/RobustPalmRoi/master/LICENSE)
![Platform](https://img.shields.io/badge/platform-linux%20%7C%20unix-brightgreen.svg)

The palm image taken by the mobile phone has differences in angle, illumination, etc. The `RobustPalmRoi` algorithm reduces these differences through a series of handlers, thus extracting a stable ROI.

The following palms are taken by iPhoneX and have different angles. The corresponding ROI is below it.

![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/original_palm_set.jpg)
![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/roi_palm_set.jpg)

Advantages of `RobustPalmRoi` algorithm:

1. ***Lower*** extraction requirements, just use your mobile phone.
1. ***Faster*** extraction speed, just tens of milliseconds.
1. ***Higher*** extraction stability, eliminate the differences such as angle, illumination, etc.

Some *tips* for capturing palms on mobile phones:

1. Five fingers open.
1. Take the whole palm.
1. Low illumination on the background.

## Installation

### Install library

There are ***some requirements*** if you want to install `RobustPalmRoi` library:

- OS Linux/Unix like.
- [`OpenCV`](https://docs.opencv.org/3.4/d7/d9f/tutorial_linux_install.html) installed.
- [`yaml-cpp`](https://github.com/jbeder/yaml-cpp) installed.

*Steps:*

1. `git clone https://github.com/Leosocy/RobustPalmRoi.git`
1. `cd RobustPalmRoi && mkdir -p build && cd build`
1. `cmake .. && sudo make install`

### Install Python module

Please make sure the C++ library is installed successfully.

**Python3.x** required.

*Steps:*

1. `cd pypackage`
1. `python setup.py install`

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

### Python

```Python
from rpr import HandlerChain

chain = HandlerChain('your_config.yaml')

# Process image, and get bytes of roi, and save roi as image.
import io
with open('your_palm_image.png', 'rb') as palm:
    roi_bytes = chain.process_image(palm)
    roi = io.BytesIO(roi_bytes)
    with open('your_roi_image.png', 'wb') as roi_image:
        roi_image.write(roi.read())
```

You can find the detail under `samples/py_sample` directory.

## Run samples

Make sure you have installed `library` and `rpr.py` before running examples.

Before you run `cpp` or `python` sample, please prepare some date follow this:

1. `cd samples/palm_data`
1. `./download.sh`

### Run cpp sample

1. `cd cpp_sample`
1. `mkdir build; cd build; cmake ..; make -j`
1. `./run_cpp_sample`

### Run python sample

1. `cd py_sample`
1. `python run_sample.py`

## Contribute
