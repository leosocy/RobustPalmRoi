# Copyright (c) 2018 leosocy. All rights reserved.
# Use of this source code is governed by a MIT-style license
# that can be found in the LICENSE file.

import io
import os
from PIL import Image   # pip install pillow
from rpr import HandlerChain

SAMPLES_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
PALM_DATA_PATH = os.path.join(SAMPLES_ROOT, 'palm_data')

ALGORITHM_CONFIG = os.path.join(SAMPLES_ROOT, 'config.yaml')
IMAGE_SUFFIXES = ['.jpg', '.png']
PALM_IMAGES = [f for f in os.listdir(PALM_DATA_PATH) if os.path.splitext(f)[1] in IMAGE_SUFFIXES]


if __name__ == '__main__':
    chain = HandlerChain(ALGORITHM_CONFIG)

    # process bytes
    for image_name in PALM_IMAGES:
        with open(os.path.join(PALM_DATA_PATH, image_name), 'rb') as palm:
            roi_bytes = chain.process_image(palm)
            roi = Image.open(io.BytesIO(roi_bytes))
            roi.show()
