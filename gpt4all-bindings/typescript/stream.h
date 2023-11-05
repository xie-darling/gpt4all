#ifndef STREAM_H
#define STREAM_H

#include <napi.h>

using namespace Napi;
class AsyncIteratorStream : public ObjectWrap<AsyncIteratorStream> {
 public:
  AsyncIteratorStream(const CallbackInfo& info);
  Napi::Value Iterator(const CallbackInfo& info);

};
#endif
