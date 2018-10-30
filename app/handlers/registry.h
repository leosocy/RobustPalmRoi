// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_APP_HANDLERS_REGISTRY_H_
#define ROBUST_PALM_ROI_APP_HANDLERS_REGISTRY_H_

#include "handlers/handler.h"
#include "handlers/normalizer.h"
#include "handlers/enhancer.h"
#include "handlers/filter.h"
#include "handlers/binarizer.h"
#include "handlers/adjuster.h"
#include "handlers/detector.h"
#include "handlers/extractor.h"

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


#endif  // ROBUST_PALM_ROI_APP_HANDLERS_REGISTRY_H_