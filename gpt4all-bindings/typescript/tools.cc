#include "tools.h"
#include <ostream>

namespace Tools {
    llmodel_prompt_context JSObjectToContext(Napi::Object const& inputObject) {
        //defaults copied from python bindings
        llmodel_prompt_context promptContext =  {
            .logits = nullptr,
            .tokens = nullptr,
            .n_past = 0,
            .n_ctx = 1024,
            .n_predict = 128,
            .top_k = 40,
            .top_p = 0.9f,
            .temp = 0.72f,
            .n_batch = 8,
            .repeat_penalty = 1.0f,
            .repeat_last_n = 10,
            .context_erase = 0.5
        };
        if(inputObject.Has("n_past")) 
             promptContext.n_past = inputObject.Get("n_past").As<Napi::Number>();
        if(inputObject.Has("n_ctx")) 
             promptContext.n_ctx = inputObject.Get("n_ctx").As<Napi::Number>();
        if(inputObject.Has("n_predict"))
             promptContext.n_predict = inputObject.Get("n_predict").As<Napi::Number>();
        if(inputObject.Has("top_k"))
             promptContext.top_k = inputObject.Get("top_k").As<Napi::Number>();
        if(inputObject.Has("top_p")) 
             promptContext.top_p = inputObject.Get("top_p").As<Napi::Number>();
        if(inputObject.Has("temp")) 
             promptContext.temp = inputObject.Get("temp").As<Napi::Number>();
        if(inputObject.Has("n_batch")) 
             promptContext.n_batch = inputObject.Get("n_batch").As<Napi::Number>();
        if(inputObject.Has("repeat_penalty")) 
             promptContext.repeat_penalty = inputObject.Get("repeat_penalty").As<Napi::Number>();
        if(inputObject.Has("repeat_last_n")) 
             promptContext.repeat_last_n = inputObject.Get("repeat_last_n").As<Napi::Number>();
        if(inputObject.Has("context_erase")) 
             promptContext.context_erase = inputObject.Get("context_erase").As<Napi::Number>();
        return promptContext;
    }

    Napi::Object ContextToJsObject(llmodel_prompt_context const& promptContext, Napi::Env& env) {
        auto js_object = Napi::Object::New(env);
        js_object.Set("n_past", promptContext.n_past);
        js_object.Set("n_ctx", promptContext.n_ctx);
        js_object.Set("n_predict", promptContext.n_predict);
        js_object.Set("top_k", promptContext.top_k);
        js_object.Set("top_p", promptContext.top_p);
        js_object.Set("temp", promptContext.temp);
        js_object.Set("n_batch", promptContext.n_batch);
        js_object.Set("repeat_penalty", promptContext.repeat_penalty);
        js_object.Set("repeat_penalty", promptContext.repeat_penalty);
        js_object.Set("repeat_last_n", promptContext.repeat_last_n);
        js_object.Set("context_erase", promptContext.context_erase);
        return js_object;
    }

    void print_llmodel_context(llmodel_prompt_context const& pc, std::ostream& out) {
        out << "{\n";
        out << "  \"logits\": " << reinterpret_cast<void*>(pc.logits) << ",\n";
        out << "  \"logits_size\": " << pc.logits_size << ",\n";
        out << "  \"tokens\": " << reinterpret_cast<void*>(pc.tokens) << ",\n";
        out << "  \"tokens_size\": " << pc.tokens_size << ",\n";
        out << "  \"n_past\": " << pc.n_past << ",\n";
        out << "  \"n_ctx\": " << pc.n_ctx << ",\n";
        out << "  \"n_predict\": " << pc.n_predict << ",\n";
        out << "  \"top_k\": " << pc.top_k << ",\n";
        out << "  \"top_p\": " << pc.top_p << ",\n";
        out << "  \"temp\": " << pc.temp << ",\n";
        out << "  \"n_batch\": " << pc.n_batch << ",\n";
        out << "  \"repeat_penalty\": " << pc.repeat_penalty << ",\n";
        out << "  \"repeat_last_n\": " << pc.repeat_last_n << ",\n";
        out << "  \"context_erase\": " << pc.context_erase << "\n";
        out << "}\n";

    }
};
