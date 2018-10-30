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

## Installation

## Run samples

## License
