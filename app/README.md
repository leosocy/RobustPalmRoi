# RobustPalmRoi Algorithm

## Handler Chain

                                        /-----------\
                                       /--> Adjuster \
    Enhancer --> Filter --> Binarizer ----> Adjuster ----> Detector --> Extractor
                                       \--> Adjuster /
                                        \-----------/

Handlers:

1. Enhancer: 图像增强处理
1. Filter: 图像滤波处理
1. Binarizer: 二值化
1. Adjuster: 填孔洞、去噪点，提取手掌唯一连通域，调整手掌角度
1. Detector: 检测是否有手掌、图片质量是否符合ROI提取标准
1. Extractor: ROI(region of interested)提取器(最大内切圆提取法......)


## Managers