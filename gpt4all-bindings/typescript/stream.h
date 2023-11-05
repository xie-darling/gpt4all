#ifndef STREAM_H
#define STREAM_H

#include <napi.h>
#include "llmodel_c.h"
using namespace Napi;
class AsyncIteratorStream : public ObjectWrap<AsyncIteratorStream> {
 public:
  AsyncIteratorStream(const CallbackInfo& info, llmodel_model model);
  Napi::Value Iterator(const CallbackInfo& info);
 private:
  bool is_running = false;
  llmodel_model model_;
};
#endif
