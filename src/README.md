# RobustPalmRoi Algorithm

## Handlers

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

## Controllers

### Handler Chain

                                                       /-----------\
                                                      /--> Adjuster \
    Normalizer --> Enhancer --> Filter --> Binarizer ----> Adjuster ----> Detector --> Extractor --> Normalizer
                                                      \--> Adjuster /
                                                       \-----------/

所有Handler通过读取配置文件(yaml)，形成处理链。输入原始的`PalmInfoDTO`，输出经过链处理后的`PalmInfoDTO`。

### Config Manager

负责读取yaml配置文件

```yaml
HandlerChain:
  order:
    - type: OrigNormalizer
      parameters:
        scaling:
          value: 0.1
          default: 1.0
          description: 原图缩放比例(0.0. 1.0]，可以加快chain处理速度。
        width:
          value: 256
          default: 350
          description: 按固定宽度等比例缩放，如果同时设置了scaling，则以此参数为准
    - type: LaplaceEnhancer
    - type: GaussianFilter
    - type: OtsuBinarizer
    - type: NoiseAdjuster
    - type: AngleAdjuster
    - type: PeakValleyDetector
      parameters:
        step:
          value: 5
          default: 5
          description: 遍历手掌轮廓的步进。过小会导致陷入局部极值，找不到指尖谷底；过大会导致找到的指尖谷底不准确。建议在5~10之间
    - type: EffectiveIncircleExtractor
    - type: IncircleRoiNormalizer
      parameters:
        width:
          value: 512
          default: 256
          description: ROI尺寸统一。设为0表示不缩放。
```

### Chain Builder

builder.SetConfig()
builder.BuildAndInitChain()
