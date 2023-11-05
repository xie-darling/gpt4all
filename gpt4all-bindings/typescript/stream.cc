#include "stream.h"

AsyncIteratorStream::AsyncIteratorStream(const CallbackInfo& info)
    : ObjectWrap<AsyncIteratorStream>(info) {

}

Napi::Value Iterator(const CallbackInfo& info) {
    auto env = info.Env();
    auto iteratorObject = Napi::Object::New(env);

    iteratorObject["current"] = Number::New(env, 1);
    iteratorObject["last"] = Number::New(env, 2);
    auto next = Function::New(env, [](const CallbackInfo& info) {
      auto env = info.Env();
      auto deferred =
          std::make_shared<Promise::Deferred>(Promise::Deferred::New(env));
      auto iteratorObject = info.This().As<Object>();
      auto callback = Function::New(
          env,
          [=](const CallbackInfo& info) {
            auto env = info.Env();
            auto value = Object::New(env);
            auto iteratorObject = info
                .This()
                .As<Object>();

            int32_t current = iteratorObject
                .Get("current")
                .As<Number>();

            int32_t last = iteratorObject
                .Get("last")
                .As<Number>()
                .Int32Value();

            auto done = current > last;

            if (done) {
              value["done"] = Boolean::New(env, true);
            } else {
              value["done"] = Boolean::New(env, false);
              value["value"] = Number::New(env, current);
              iteratorObject["current"] = Number::New(env, current + 1);
            }
            deferred->Resolve(value);
          },
          "next");

      env.Global()
          .Get("setTimeout")
          .As<Function>()
          .Call({callback.Get("bind").As<Function>().Call(callback,
                                                          {iteratorObject}),
                 Number::New(env, 1000)});

      return deferred->Promise();
    });

    iteratorObject["next"] =
        next
        .Get("bind")
        .As<Function>()
        .Call(next, {iteratorObject});

    return iteratorObject;
}

