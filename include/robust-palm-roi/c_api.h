// Copyright (c) 2018 leosocy. All rights reserved.
// Use of this source code is governed by a MIT-style license
// that can be found in the LICENSE file.

#ifndef ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_C_API_H
#define ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_C_API_H

#define ROBUST_PALM_ROI_API

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Create a handler chain.
 * @param config_file_name supplies a config file name which format is YAML.
 * @return void* a pointer of type `HandlerChain`.
 */
ROBUST_PALM_ROI_API void* init_chain(const char* config_file_name);

/**
 * Use chain to process an image which is encoded by Base64.
 * @param chain_ptr supplies a pointer of `HandlerChain` returned from `init_chain`.
 * @param palm_base64 supplies a string buffer of a base64 encoded image.
 * @param roi_base64 supplies a string buffer of a base64 encoded roi image.
 * @param status a pointer of status, status[0] stands for code, status[1:] stands for msg.
 */
ROBUST_PALM_ROI_API void chain_process_base64(void* chain_ptr, const char* palm_base64,
                                              char* roi_base64, char* status_ptr);

/**
 * Use chain to process an image bytes.
 * @param chain_ptr supplies a pointer of `HandlerChain` returned from `init_chain`.
 * @param palm_bytes supplies a bytes of image.
 * @param roi_bytes supplies a bytes of roi image.
 * @param status a pointer of status, status[0] stands for code, status[1:] stands for msg.
 */
ROBUST_PALM_ROI_API void chain_process_bytes(void* chain_ptr,
                                             const char* palm_bytes, unsigned long palm_bytes_size,
                                             char* roi_bytes, unsigned long* roi_bytes_size,
                                             char* status_ptr);

#ifdef __cplusplus
}
#endif

#endif  // ROBUST_PALM_ROI_INCLUDE_ROBUST_PALM_ROI_C_API_H