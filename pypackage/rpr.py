#  Copyright (c) 2018 leosocy. All rights reserved.
#  Use of this source code is governed by a MIT-style license
# that can be found in the LICENSE file.

"""A robust algorithm for extracting ROI from palm image taken by mobile phone"""

import ctypes
import platform

__author__ = 'Leosocy <leosocy@gmail.com>'
__version__ = '0.1.0'


class HandlerChain(object):

    """
    Init chain with `config.yml` file, and provide several methods for adapting the C++ library.
    """

    LIB_NAME = 'librobust-palm-roi'
    LIB_SUFFIX = 'so' if platform.uname()[0] == 'Linux' else 'dylib'
    LIB_INSTALLATION_URL = 'https://github.com/Leosocy/RobustPalmRoi/blob/master/README.md#Installation'    # NOQA F501

    def __init__(self, config='config.yml'):
        self.config = config
        try:
            self._lib = ctypes.cdll.LoadLibrary(
                '{}.{}'.format(self.LIB_NAME, self.LIB_SUFFIX))
        except OSError:
            raise OSError('Library [{:s}] not found.\nPlease see {}'
                          .format(self.LIB_NAME, self.LIB_INSTALLATION_URL))

        # init robust-palm-roi lib apis.
        self._lib.init_chain.argtypes = [ctypes.c_char_p]
        self._lib.init_chain.restype = ctypes.c_void_p

        self._lib.chain_process_base64.argtypes = [
            ctypes.c_void_p, ctypes.c_char_p,
            ctypes.c_char_p, ctypes.c_long, ctypes.c_char_p
        ]
        self._lib.chain_process_base64.restype = None

        self._lib.chain_process_bytes.argtypes = [
            ctypes.c_void_p, ctypes.c_char_p, ctypes.c_long,
            ctypes.c_char_p, ctypes.c_long, ctypes.POINTER(ctypes.c_long),
            ctypes.c_char_p
        ]
        self._lib.chain_process_bytes.restype = None

        self._chain = self._lib.init_chain(bytes(self.config, encoding='utf-8'))

    def process_image(self, image):
        '''
        Process palm image

        :param image: The palm image
        :type param: a file object which opening for [r]eading as [b]inary
        :return: roi
        :rtype: bytes
        '''
        palm_data = image.read()
        roi_bytes_max_size = 1024 * 1024
        roi_bytes = ctypes.create_string_buffer(roi_bytes_max_size)
        roi_bytes_size = ctypes.c_long(0)
        status = ctypes.create_string_buffer(128)
        self._lib.chain_process_bytes(self._chain, palm_data, len(palm_data),
                                      roi_bytes, roi_bytes_max_size, roi_bytes_size, status)
        self._check_status(status)
        return roi_bytes.raw[:roi_bytes_size.value]

    def process_base64(self, b64_str):
        '''
        Procees base64 encoded image

        :param str b64_str: The base64 encoding string for the image
        :return: the base64 encoding string for the roi
        :rtype: str
        '''
        roi_b64_size = 1024 * 1024
        roi_b64 = ctypes.create_string_buffer(roi_b64_size)  # can store about 768 KB of image.
        status = ctypes.create_string_buffer(128)
        self._lib.chain_process_base64(self._chain, b64_str, roi_b64, roi_b64_size, status)
        self._check_status(status)
        return roi_b64.value

    @staticmethod
    def _check_status(status):
        if status.raw[0] != 0:
            raise RuntimeError(status.raw[1:].decode())
