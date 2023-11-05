#ifndef BINDING_TOOLS_H 
#define BINDING_TOOLS_H 

#include <llmodel_c.h>
#include <napi.h>

namespace Tools {
    llmodel_prompt_context JSObjectToContext(Napi::Object const &);
    Napi::Object ContextToJsObject(llmodel_prompt_context const &, Napi::Env);
};

#endif
