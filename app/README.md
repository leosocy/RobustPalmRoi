# RobustPalmRoi Algorithm

## Handlers

1. Normalizer: 标准化处理
    - 对原图: 缩小图片，加快处理速度
    - 对ROI: 尺寸统一、光照平衡、circle遮罩
1. Enhancer: 图像增强处理
1. Filter: 图像滤波处理
1. Binarizer: 二值化
1. Adjuster: 填孔洞、去噪点，提取手掌唯一连通域，调整手掌角度
1. Detector: 检测是否有手掌、图片质量是否符合ROI提取标准
1. Extractor: ROI(region of interested)提取器(最大内切圆提取法......)

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
          description: 原图缩放比例，可以加快chain处理速度。
        width:
          value: 256
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
          description: 遍历手掌轮廓的步进。过小会导致陷入局部极值，找不到指尖谷底；过大会导致找到的指尖谷底不准确。建议在5~10之间
    - type: EffectiveIncircleExtractor
    - type: IncircleRoiNormalizer
      parameters:
        width:
          value: 512
          description: ROI尺寸统一。设为0表示不缩放。
```

### Chain Builder

builder.SetConfig()
builder.BuildAndInitChain()

## Apis

- GetPalmRoi(const cv::Mat& palm, cv::Mat* roi);
