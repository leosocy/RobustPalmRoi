# RobustPalmRoi Algorithm

## Handler Chain

Enhancer --> Filter --> Binarizer --> Adjuster --> Detector --> Normaliser --> Extractor

Handlers:

1. Enhancer: 图像增强处理
1. Filter: 图像滤波处理
1. Binarizer: 二值化
1. Adjuster: 膨胀、腐蚀、去噪
1. Detector: 检测是否有手掌、图片质量是否符合ROI提取标准
1. Normaliser: 归一化处理，调整手掌角度、尺寸归一化
1. Extractor: ROI(region of interested)提取器(最大内切圆提取法......)

