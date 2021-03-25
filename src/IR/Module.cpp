#include <llvm/Support/raw_ostream.h>

#include "IR/LLVMContext.h"
#include "IR/Module.h"
#include "IR/Function.h"
#include "IR/GlobalVariable.h"
#include "IR/StructType.h"
#include "IR/DataLayout.h"

void Module::Init(Napi::Env env, Napi::Object &exports) {
    Napi::HandleScope scope(env);
    Napi::Function func = DefineClass(env, "Module", {
            InstanceMethod("empty", &Module::empty),
            InstanceMethod("getFunction", &Module::getFunction),
            InstanceMethod("getGlobalVariable", &Module::getGlobalVariable),
            InstanceMethod("getTypeByName", &Module::getTypeByName),
            InstanceMethod("getName", &Module::getName),
            InstanceMethod("getDataLayout", &Module::getDataLayout),
            InstanceMethod("setDataLayout", &Module::setDataLayout),
            InstanceMethod("getModuleIdentifier", &Module::getModuleIdentifier),
            InstanceMethod("setModuleIdentifier", &Module::setModuleIdentifier),
            InstanceMethod("getSourceFileName", &Module::getSourceFileName),
            InstanceMethod("setSourceFileName", &Module::setSourceFileName),
            InstanceMethod("getTargetTriple", &Module::getTargetTriple),
            InstanceMethod("setTargetTriple", &Module::setTargetTriple),
            InstanceMethod("print", &Module::print)
    });
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("Module", func);
}

bool Module::IsClassOf(const Napi::Value &value) {
    return value.As<Napi::Object>().InstanceOf(constructor.Value());
}

llvm::Module *Module::Extract(const Napi::Value &value) {
    return Unwrap(value.As<Napi::Object>())->getLLVMPrimitive();
}

Module::Module(const Napi::CallbackInfo &info) : ObjectWrap(info) {
    Napi::Env env = info.Env();
    if (!info.IsConstructCall()) {
        throw Napi::TypeError::New(env, "Module constructor needs to be called with new");
    }
    if (info.Length() < 2 || !info[0].IsString() || !LLVMContext::IsClassOf(info[1])) {
        throw Napi::TypeError::New(env, "The Module constructor needs to be called with: new (moduleID: string, context: LLVMContext)");
    }
    const std::string &moduleID = info[0].As<Napi::String>();
    llvm::LLVMContext &context = LLVMContext::Extract(info[1]);
    module = new llvm::Module(moduleID, context);
}

Napi::Value Module::empty(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::Boolean::New(env, module->empty());
}

Napi::Value Module::getFunction(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, "getFunction needs to be called with: (name: string)");
    }
    std::string functionName = info[0].As<Napi::String>();
    llvm::Function *function = module->getFunction(functionName);
    if (function) {
        return Function::New(env, function);
    }
    return env.Null();
}

Napi::Value Module::getGlobalVariable(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString() || info.Length() == 2 && !info[1].IsBoolean()) {
        throw Napi::TypeError::New(env, "Module.getGlobalVariable needs to be called with: (name: string, allowInternal?: boolean)");
    }
    const std::string &name = info[0].As<Napi::String>();
    bool allowInternal = false;
    if (info.Length() == 2) {
        allowInternal = info[1].As<Napi::Boolean>();
    }
    llvm::GlobalVariable *global = module->getGlobalVariable(name, allowInternal);
    if (global) {
        return GlobalVariable::New(env, global);
    }
    return env.Null();
}

Napi::Value Module::getTypeByName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() < 1 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, "getTypeByName needs to be called with: (name: string)");
    }
    const std::string name = info[0].As<Napi::String>();
    llvm::StructType *type = module->getTypeByName(name);
    if (type) {
        return StructType::New(env, type);
    }
    return env.Null();
}

Napi::Value Module::getName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, module->getName().str());
}

Napi::Value Module::getDataLayout(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    const llvm::DataLayout &dataLayout = module->getDataLayout();
    return DataLayout::New(env, const_cast<llvm::DataLayout *>(&dataLayout));
}

void Module::setDataLayout(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() == 0 || !(info[0].IsString() || DataLayout::IsClassOf(info[0]))) {
        throw Napi::TypeError::New(env, "setDataLayout needs to be called with: (StringRef Desc) or (const DataLayout &Other)");
    }
    if (info[0].IsString()) {
        const std::string &desc = info[0].As<Napi::String>();
        module->setDataLayout(desc);
    } else if (DataLayout::IsClassOf(info[0])) {
        llvm::DataLayout &dl = DataLayout::Extract(info[0]);
        module->setDataLayout(dl);
    }
}

Napi::Value Module::getModuleIdentifier(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, module->getModuleIdentifier());
}

void Module::setModuleIdentifier(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, "moduleIdentifier needs to be a string");
    }
    const std::string &moduleID = info[0].As<Napi::String>();
    module->setModuleIdentifier(moduleID);
}

Napi::Value Module::getSourceFileName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, module->getSourceFileName());
}

void Module::setSourceFileName(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, "sourceFileName needs to be a string");
    }
    const std::string &sourceFileName = info[0].As<Napi::String>();
    module->setSourceFileName(sourceFileName);
}

Napi::Value Module::getTargetTriple(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    return Napi::String::New(env, module->getTargetTriple());
}

void Module::setTargetTriple(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    if (info.Length() != 1 || !info[0].IsString()) {
        throw Napi::TypeError::New(env, "targetTriple needs to be a string");
    }
    const std::string &triple = info[0].As<Napi::String>();
    module->setTargetTriple(triple);
}

void Module::print(const Napi::CallbackInfo &info) {
    module->print(llvm::outs(), nullptr);
}

llvm::Module *Module::getLLVMPrimitive() {
    return module;
}