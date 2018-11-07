# RobustPalmRoi: An algorithm to extract the interested region of palm image in complex environment.

[![Build Status](https://travis-ci.org/Leosocy/RobustPalmRoi.svg?branch=master)](https://travis-ci.org/Leosocy/RobustPalmRoi)
[![codecov](https://codecov.io/gh/Leosocy/RobustPalmRoi/branch/master/graph/badge.svg)](https://codecov.io/gh/Leosocy/RobustPalmRoi)
[![MIT licensed](https://img.shields.io/badge/license-MIT-green.svg)](https://raw.githubusercontent.com/Leosocy/RobustPalmRoi/master/LICENSE)

## How does it work

                                                       /-----------\
                                                      /--> Adjuster \
    Normalizer --> Enhancer --> Filter --> Binarizer ----> Adjuster ----> Detector --> Extractor --> Normalizer
                                                      \--> Adjuster /
                                                       \-----------/

通过组合不同的handler，形成处理链，对原始的手掌图像进行一系列的处理，目前包括以下handler：

| handler | 功能 |
|:-------:|:----:|
|`OrigNormalizer`|对原始手掌图像进行尺寸统一缩减，增加后续handler处理速度|
|`LaplaceEnhancer`|对手掌图像进行拉普拉斯增强，突出手掌前景|
|`GaussianFilter`|去除图像噪声|
|`OtsuBinarizer`|最大类间方差法进行二值化|
|`NoiseAdjuster`|去除二值化中的噪点，只保留一个手掌连通域|
|`AngleAdjuster`|根据重心法寻找中指指尖，并且旋转二值图|
|`PeakValleyDetector`|检测手掌的5个指尖，以及4个谷底|
|`EffectiveIncircleExtractor`|最大有效内切圆算法提取ROI|
|`IncircleRoiNormalizer`|对ROI进行尺寸统一、光照平衡、circle遮罩|

| Description | Original Image | ROI |
| :---------: | :------------: |:---:|
|Left Palm No Rotating|![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/20181107225449.png)|![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/20181107225814.png)|
|Left Palm Left Rotating|![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/20181107230103.png)|![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/20181107230130.png)|
|Left Palm Right Rotating|![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/20181107230208.png)|![](https://blog-images-1257621236.cos.ap-shanghai.myqcloud.com/20181107230221.png)|

## Installation

There are ***some requirements*** if you want to install `RobustPalmRoi`:

- OS Linux/Unix like.
- OpenCV installed.
- yaml-cpp installed.
    ```shell
    git clone https://github.com/jbeder/yaml-cpp.git
    cd yaml-cpp && mkdir -p build && cd build
    cmake -DYAML_CPP_BUILD_TESTS=OFF -DYAML_CPP_BUILD_TOOLS=OFF -DBUILD_SHARED_LIBS=ON ..
    make -j2 && sudo make install
    ```

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
#include <robust-palm-roi/chain.h>

int main() {
    rpr::ChainBuilder builder;
    builder.SetConfigYaml(config_file_name);
    auto chain = builder.BuildAndInitChain();

    cv::Mat img = cv::imread(palm_image_file_name);
    cv::Mat roi;
    auto status = chain->Process(img, &roi);

    return 0;
}
```

You can find the detail under `samples/cpp_sample`.

- Python

## Run samples

### Run cpp sample

### Run python sample

## License

Please see [LICENSE](https://github.com/Leosocy/RobustPalmRoi/blob/master/LICENSE)

## Contribute
