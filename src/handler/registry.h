// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_SRC_HANDLER_REGISTRY_H_
#define ROBUST_PALM_ROI_SRC_HANDLER_REGISTRY_H_

#include "handler/handler.h"
#include "handler/normalizer.h"
#include "handler/enhancer.h"
#include "handler/filter.h"
#include "handler/binarizer.h"
#include "handler/adjuster.h"
#include "handler/detector.h"
#include "handler/extractor.h"

namespace rpr {

REGISTER_HANDLER(OrigNormalizer);
REGISTER_HANDLER(LaplaceEnhancer);
REGISTER_HANDLER(GaussianFilter);
REGISTER_HANDLER(OtsuBinarizer);
REGISTER_HANDLER(NoiseAdjuster);
REGISTER_HANDLER(AngleAdjuster);
REGISTER_HANDLER(PeakValleyDetector);
REGISTER_HANDLER(EffectiveIncircleExtractor);
REGISTER_HANDLER(IncircleRoiNormalizer);

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_SRC_HANDLER_REGISTRY_H_