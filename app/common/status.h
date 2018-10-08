/****************************************************************************\
 * Created on Sat Oct 06 2018
 * 
 * The MIT License (MIT)
 * Copyright (c) 2018 leosocy
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the ",Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED ",AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
\*****************************************************************************/

#ifndef ROBUST_PALM_ROI_APP_COMMON_STATUS_H_
#define ROBUST_PALM_ROI_APP_COMMON_STATUS_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>


namespace rpr {

class Status {
 public:
  enum Code {
    kOk = 0,
    kLoadImageError,
  };
  static Status Ok(const char* msg = NULL) { return Status(kOk, msg); }
  static Status LoadImageError(const char* msg = NULL) { return Status(kLoadImageError, msg); }

  Status() : state_(NULL) {}
  Status(const Status& s) {
    state_ = (s.state_ == NULL ? NULL : CopyState(s.state_));
  }
  void operator=(const Status& s) {
    if (this != &s) {
      DeleteState();
      state_ = (s.state_ == NULL ? NULL : CopyState(s.state_));
    }
  }
  ~Status() { DeleteState(); }
  Code code() {
    assert (state_ != NULL);
    return static_cast<Code>(state_[0]);
  }
  const char* msg() {
    assert (state_ != NULL);
    return state_ + 1;
  }
  bool IsOk() { return code() == kOk; }

 private:
  Status(Code code, const char* msg = NULL);
  const char* CopyState(const char* state);
  void DeleteState();
  const char *state_;
};

inline Status::Status(Code code, const char* msg) {
  size_t msg_len = (msg == NULL) ? 0 : strlen(msg);
  char *result = new char[msg_len + 2];
  result[0] = static_cast<char>(code);
  strncpy(result + 1, msg, msg_len);
  result[msg_len + 1] = '\0';
  state_ = result;
}

inline const char* Status::CopyState(const char *state) {
  assert(state != NULL);
  size_t state_len = 1 + strlen(state + 1) + 1;     // code_len + msg_len + '\0'
  char *result = new char[state_len];
  memcpy(result, state, state_len);
  return result;
}

inline void Status::DeleteState() {
  if (state_ != NULL) {
    delete[] state_;
    state_ = NULL;
  }
}

}   // namespace rpr

#endif  // ROBUST_PALM_ROI_APP_COMMON_STATUS_H_