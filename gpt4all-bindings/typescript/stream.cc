#include "stream.h"
#include "llmodel_c.h"
#include <iostream>

AsyncIteratorStream::AsyncIteratorStream(
        const CallbackInfo& info,
        llmodel_model model)
    : ObjectWrap<AsyncIteratorStream>(info), model_(model) {}

Napi::Value AsyncIteratorStream::Iterator(const CallbackInfo& info) {
    auto env = info.Env();
    auto iteratorObject = Napi::Object::New(env);

    auto next = Function::New(env, [](const CallbackInfo& info) {
        auto env = info.Env();
        auto deferred =
          std::make_shared<Promise::Deferred>(Promise::Deferred::New(env));
        auto iter = info.This().As<Object>();

        auto callback = Function::New(
            env,
            [=](const CallbackInfo& info) {
                  auto env = info.Env();
                  auto value = Object::New(env);
                  auto iter = info
                      .This()
                      .As<Object>();

                  auto done = 4 > 2;

                  if (done) {
                    value["done"] = Boolean::New(env, true);
                  } else {
                    value["done"] = Boolean::New(env, false);
                    value["value"] = Number::New(env, 1);
                    iter["current"] = Number::New(env, 2 + 1);
                  }
                  deferred->Resolve(value);
            },
            "next");
      env.Global()
          .Get("setTimeout")
          .As<Function>()
          .Call({callback.Get("bind").As<Function>().Call(callback,
                                                          {iter}),
                 Number::New(env, 1000)});

      return deferred->Promise();
    });

    //bind the next function to iteratorObject
    iteratorObject["next"] =
        next
        .Get("bind")
        .As<Function>()
        .Call(next, {iteratorObject});

    return iteratorObject;
}

