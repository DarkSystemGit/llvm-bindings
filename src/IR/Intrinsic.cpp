#include "IR/index.h"
#include "Util/index.h"

Napi::Value getDeclaration(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    unsigned argsLen = info.Length();
    if (argsLen == 2 && Module::IsClassOf(info[0]) && info[1].IsNumber() ||
        argsLen == 3 && Module::IsClassOf(info[0]) && info[1].IsNumber() && info[2].IsArray()) {
        llvm::Module *module = Module::Extract(info[0]);
        llvm::Intrinsic::ID id = static_cast<llvm::Intrinsic::ID>(info[1].As<Napi::Number>().Uint32Value());
        llvm::Function *function;
        if (argsLen == 3) {
            auto types = info[2].As<Napi::Array>();
            unsigned numTypes = types.Length();
            std::vector<llvm::Type *> paramTypes(numTypes);
            for (unsigned i = 0; i < numTypes; ++i) {
                paramTypes[i] = Type::Extract(types.Get(i));
            }
            function = llvm::Intrinsic::getDeclaration(module, id, paramTypes);
        } else {
            function = llvm::Intrinsic::getDeclaration(module, id);
        }
        return Function::New(env, function);
    }
    throw Napi::TypeError::New(env, ErrMsg::Namespace::Intrinsic::getDeclaration);
}

void Intrinsic::Init(Napi::Env env, Napi::Object &exports) {
    Napi::Object intrinsicNS = Napi::Object::New(env);
    intrinsicNS.Set("abs", Napi::Number::New(env, llvm::Intrinsic::abs));
    intrinsicNS.Set("addressofreturnaddress",
                    Napi::Number::New(env, llvm::Intrinsic::addressofreturnaddress));
    intrinsicNS.Set("adjust_trampoline",
                    Napi::Number::New(env, llvm::Intrinsic::adjust_trampoline));
    intrinsicNS.Set("annotation", Napi::Number::New(env, llvm::Intrinsic::annotation));
    intrinsicNS.Set("arithmetic_fence", Napi::Number::New(env, llvm::Intrinsic::arithmetic_fence));
    intrinsicNS.Set("asan_check_memaccess",
                    Napi::Number::New(env, llvm::Intrinsic::asan_check_memaccess));
    intrinsicNS.Set("assume", Napi::Number::New(env, llvm::Intrinsic::assume));
    intrinsicNS.Set("bitreverse", Napi::Number::New(env, llvm::Intrinsic::bitreverse));
    intrinsicNS.Set("bswap", Napi::Number::New(env, llvm::Intrinsic::bswap));
    intrinsicNS.Set("call_preallocated_arg",
                    Napi::Number::New(env, llvm::Intrinsic::call_preallocated_arg));
    intrinsicNS.Set("call_preallocated_setup",
                    Napi::Number::New(env, llvm::Intrinsic::call_preallocated_setup));
    intrinsicNS.Set("call_preallocated_teardown",
                    Napi::Number::New(env, llvm::Intrinsic::call_preallocated_teardown));
    intrinsicNS.Set("canonicalize", Napi::Number::New(env, llvm::Intrinsic::canonicalize));
    intrinsicNS.Set("ceil", Napi::Number::New(env, llvm::Intrinsic::ceil));
    intrinsicNS.Set("clear_cache", Napi::Number::New(env, llvm::Intrinsic::clear_cache));
    intrinsicNS.Set("codeview_annotation",
                    Napi::Number::New(env, llvm::Intrinsic::codeview_annotation));
    intrinsicNS.Set("convert_from_fp16",
                    Napi::Number::New(env, llvm::Intrinsic::convert_from_fp16));
    intrinsicNS.Set("convert_to_fp16", Napi::Number::New(env, llvm::Intrinsic::convert_to_fp16));
    intrinsicNS.Set("copysign", Napi::Number::New(env, llvm::Intrinsic::copysign));
    intrinsicNS.Set("coro_align", Napi::Number::New(env, llvm::Intrinsic::coro_align));
    intrinsicNS.Set("coro_alloc", Napi::Number::New(env, llvm::Intrinsic::coro_alloc));
    intrinsicNS.Set("coro_alloca_alloc",
                    Napi::Number::New(env, llvm::Intrinsic::coro_alloca_alloc));
    intrinsicNS.Set("coro_alloca_free", Napi::Number::New(env, llvm::Intrinsic::coro_alloca_free));
    intrinsicNS.Set("coro_alloca_get", Napi::Number::New(env, llvm::Intrinsic::coro_alloca_get));
    intrinsicNS.Set("coro_async_context_alloc",
                    Napi::Number::New(env, llvm::Intrinsic::coro_async_context_alloc));
    intrinsicNS.Set("coro_async_context_dealloc",
                    Napi::Number::New(env, llvm::Intrinsic::coro_async_context_dealloc));
    intrinsicNS.Set("coro_async_resume",
                    Napi::Number::New(env, llvm::Intrinsic::coro_async_resume));
    intrinsicNS.Set("coro_async_size_replace",
                    Napi::Number::New(env, llvm::Intrinsic::coro_async_size_replace));
    intrinsicNS.Set("coro_begin", Napi::Number::New(env, llvm::Intrinsic::coro_begin));
    intrinsicNS.Set("coro_destroy", Napi::Number::New(env, llvm::Intrinsic::coro_destroy));
    intrinsicNS.Set("coro_done", Napi::Number::New(env, llvm::Intrinsic::coro_done));
    intrinsicNS.Set("coro_end", Napi::Number::New(env, llvm::Intrinsic::coro_end));
    intrinsicNS.Set("coro_end_async", Napi::Number::New(env, llvm::Intrinsic::coro_end_async));
    intrinsicNS.Set("coro_frame", Napi::Number::New(env, llvm::Intrinsic::coro_frame));
    intrinsicNS.Set("coro_free", Napi::Number::New(env, llvm::Intrinsic::coro_free));
    intrinsicNS.Set("coro_id", Napi::Number::New(env, llvm::Intrinsic::coro_id));
    intrinsicNS.Set("coro_id_async", Napi::Number::New(env, llvm::Intrinsic::coro_id_async));
    intrinsicNS.Set("coro_id_retcon", Napi::Number::New(env, llvm::Intrinsic::coro_id_retcon));
    intrinsicNS.Set("coro_id_retcon_once",
                    Napi::Number::New(env, llvm::Intrinsic::coro_id_retcon_once));
    intrinsicNS.Set("coro_noop", Napi::Number::New(env, llvm::Intrinsic::coro_noop));
    intrinsicNS.Set("coro_prepare_async",
                    Napi::Number::New(env, llvm::Intrinsic::coro_prepare_async));
    intrinsicNS.Set("coro_prepare_retcon",
                    Napi::Number::New(env, llvm::Intrinsic::coro_prepare_retcon));
    intrinsicNS.Set("coro_promise", Napi::Number::New(env, llvm::Intrinsic::coro_promise));
    intrinsicNS.Set("coro_resume", Napi::Number::New(env, llvm::Intrinsic::coro_resume));
    intrinsicNS.Set("coro_save", Napi::Number::New(env, llvm::Intrinsic::coro_save));
    intrinsicNS.Set("coro_size", Napi::Number::New(env, llvm::Intrinsic::coro_size));
    intrinsicNS.Set("coro_subfn_addr", Napi::Number::New(env, llvm::Intrinsic::coro_subfn_addr));
    intrinsicNS.Set("coro_suspend", Napi::Number::New(env, llvm::Intrinsic::coro_suspend));
    intrinsicNS.Set("coro_suspend_async",
                    Napi::Number::New(env, llvm::Intrinsic::coro_suspend_async));
    intrinsicNS.Set("coro_suspend_retcon",
                    Napi::Number::New(env, llvm::Intrinsic::coro_suspend_retcon));
    intrinsicNS.Set("cos", Napi::Number::New(env, llvm::Intrinsic::cos));
    intrinsicNS.Set("ctlz", Napi::Number::New(env, llvm::Intrinsic::ctlz));
    intrinsicNS.Set("ctpop", Napi::Number::New(env, llvm::Intrinsic::ctpop));
    intrinsicNS.Set("cttz", Napi::Number::New(env, llvm::Intrinsic::cttz));
    intrinsicNS.Set("dbg_addr", Napi::Number::New(env, llvm::Intrinsic::dbg_addr));
    intrinsicNS.Set("dbg_declare", Napi::Number::New(env, llvm::Intrinsic::dbg_declare));
    intrinsicNS.Set("dbg_label", Napi::Number::New(env, llvm::Intrinsic::dbg_label));
    intrinsicNS.Set("dbg_value", Napi::Number::New(env, llvm::Intrinsic::dbg_value));
    intrinsicNS.Set("debugtrap", Napi::Number::New(env, llvm::Intrinsic::debugtrap));
    intrinsicNS.Set("donothing", Napi::Number::New(env, llvm::Intrinsic::donothing));
    intrinsicNS.Set("eh_dwarf_cfa", Napi::Number::New(env, llvm::Intrinsic::eh_dwarf_cfa));
    intrinsicNS.Set("eh_exceptioncode", Napi::Number::New(env, llvm::Intrinsic::eh_exceptioncode));
    intrinsicNS.Set("eh_exceptionpointer",
                    Napi::Number::New(env, llvm::Intrinsic::eh_exceptionpointer));
    intrinsicNS.Set("eh_recoverfp", Napi::Number::New(env, llvm::Intrinsic::eh_recoverfp));
    intrinsicNS.Set("eh_return_i32", Napi::Number::New(env, llvm::Intrinsic::eh_return_i32));
    intrinsicNS.Set("eh_return_i64", Napi::Number::New(env, llvm::Intrinsic::eh_return_i64));
    intrinsicNS.Set("eh_sjlj_callsite", Napi::Number::New(env, llvm::Intrinsic::eh_sjlj_callsite));
    intrinsicNS.Set("eh_sjlj_functioncontext",
                    Napi::Number::New(env, llvm::Intrinsic::eh_sjlj_functioncontext));
    intrinsicNS.Set("eh_sjlj_longjmp", Napi::Number::New(env, llvm::Intrinsic::eh_sjlj_longjmp));
    intrinsicNS.Set("eh_sjlj_lsda", Napi::Number::New(env, llvm::Intrinsic::eh_sjlj_lsda));
    intrinsicNS.Set("eh_sjlj_setjmp", Napi::Number::New(env, llvm::Intrinsic::eh_sjlj_setjmp));
    intrinsicNS.Set("eh_sjlj_setup_dispatch",
                    Napi::Number::New(env, llvm::Intrinsic::eh_sjlj_setup_dispatch));
    intrinsicNS.Set("eh_typeid_for", Napi::Number::New(env, llvm::Intrinsic::eh_typeid_for));
    intrinsicNS.Set("eh_unwind_init", Napi::Number::New(env, llvm::Intrinsic::eh_unwind_init));
    intrinsicNS.Set("exp", Napi::Number::New(env, llvm::Intrinsic::exp));
    intrinsicNS.Set("exp2", Napi::Number::New(env, llvm::Intrinsic::exp2));
    intrinsicNS.Set("expect", Napi::Number::New(env, llvm::Intrinsic::expect));
    intrinsicNS.Set("expect_with_probability",
                    Napi::Number::New(env, llvm::Intrinsic::expect_with_probability));
    intrinsicNS.Set("fabs", Napi::Number::New(env, llvm::Intrinsic::fabs));
    intrinsicNS.Set("floor", Napi::Number::New(env, llvm::Intrinsic::floor));
    intrinsicNS.Set("flt_rounds", Napi::Number::New(env, llvm::Intrinsic::flt_rounds));
    intrinsicNS.Set("fma", Napi::Number::New(env, llvm::Intrinsic::fma));
    intrinsicNS.Set("fmuladd", Napi::Number::New(env, llvm::Intrinsic::fmuladd));
    intrinsicNS.Set("fptosi_sat", Napi::Number::New(env, llvm::Intrinsic::fptosi_sat));
    intrinsicNS.Set("fptoui_sat", Napi::Number::New(env, llvm::Intrinsic::fptoui_sat));
    intrinsicNS.Set("frameaddress", Napi::Number::New(env, llvm::Intrinsic::frameaddress));
    intrinsicNS.Set("fshl", Napi::Number::New(env, llvm::Intrinsic::fshl));
    intrinsicNS.Set("fshr", Napi::Number::New(env, llvm::Intrinsic::fshr));
    intrinsicNS.Set("gcread", Napi::Number::New(env, llvm::Intrinsic::gcread));
    intrinsicNS.Set("gcroot", Napi::Number::New(env, llvm::Intrinsic::gcroot));
    intrinsicNS.Set("gcwrite", Napi::Number::New(env, llvm::Intrinsic::gcwrite));
    intrinsicNS.Set("get_active_lane_mask",
                    Napi::Number::New(env, llvm::Intrinsic::get_active_lane_mask));
    intrinsicNS.Set("get_dynamic_area_offset",
                    Napi::Number::New(env, llvm::Intrinsic::get_dynamic_area_offset));
    intrinsicNS.Set("hwasan_check_memaccess",
                    Napi::Number::New(env, llvm::Intrinsic::hwasan_check_memaccess));
    intrinsicNS.Set("hwasan_check_memaccess_shortgranules",
                    Napi::Number::New(env, llvm::Intrinsic::hwasan_check_memaccess_shortgranules));
    intrinsicNS.Set("icall_branch_funnel",
                    Napi::Number::New(env, llvm::Intrinsic::icall_branch_funnel));
    intrinsicNS.Set("init_trampoline", Napi::Number::New(env, llvm::Intrinsic::init_trampoline));
    intrinsicNS.Set("instrprof_cover", Napi::Number::New(env, llvm::Intrinsic::instrprof_cover));
    intrinsicNS.Set("instrprof_increment",
                    Napi::Number::New(env, llvm::Intrinsic::instrprof_increment));
    intrinsicNS.Set("instrprof_increment_step",
                    Napi::Number::New(env, llvm::Intrinsic::instrprof_increment_step));
    intrinsicNS.Set("instrprof_value_profile",
                    Napi::Number::New(env, llvm::Intrinsic::instrprof_value_profile));
    intrinsicNS.Set("invariant_end", Napi::Number::New(env, llvm::Intrinsic::invariant_end));
    intrinsicNS.Set("invariant_start", Napi::Number::New(env, llvm::Intrinsic::invariant_start));
    intrinsicNS.Set("is_constant", Napi::Number::New(env, llvm::Intrinsic::is_constant));
    intrinsicNS.Set("launder_invariant_group",
                    Napi::Number::New(env, llvm::Intrinsic::launder_invariant_group));
    intrinsicNS.Set("lifetime_end", Napi::Number::New(env, llvm::Intrinsic::lifetime_end));
    intrinsicNS.Set("lifetime_start", Napi::Number::New(env, llvm::Intrinsic::lifetime_start));
    intrinsicNS.Set("llrint", Napi::Number::New(env, llvm::Intrinsic::llrint));
    intrinsicNS.Set("llround", Napi::Number::New(env, llvm::Intrinsic::llround));
    intrinsicNS.Set("load_relative", Napi::Number::New(env, llvm::Intrinsic::load_relative));
    intrinsicNS.Set("localaddress", Napi::Number::New(env, llvm::Intrinsic::localaddress));
    intrinsicNS.Set("localescape", Napi::Number::New(env, llvm::Intrinsic::localescape));
    intrinsicNS.Set("localrecover", Napi::Number::New(env, llvm::Intrinsic::localrecover));
    intrinsicNS.Set("log", Napi::Number::New(env, llvm::Intrinsic::log));
    intrinsicNS.Set("log10", Napi::Number::New(env, llvm::Intrinsic::log10));
    intrinsicNS.Set("log2", Napi::Number::New(env, llvm::Intrinsic::log2));
    intrinsicNS.Set("loop_decrement", Napi::Number::New(env, llvm::Intrinsic::loop_decrement));
    intrinsicNS.Set("loop_decrement_reg",
                    Napi::Number::New(env, llvm::Intrinsic::loop_decrement_reg));
    intrinsicNS.Set("lrint", Napi::Number::New(env, llvm::Intrinsic::lrint));
    intrinsicNS.Set("lround", Napi::Number::New(env, llvm::Intrinsic::lround));
    intrinsicNS.Set("masked_compressstore",
                    Napi::Number::New(env, llvm::Intrinsic::masked_compressstore));
    intrinsicNS.Set("masked_expandload",
                    Napi::Number::New(env, llvm::Intrinsic::masked_expandload));
    intrinsicNS.Set("masked_gather", Napi::Number::New(env, llvm::Intrinsic::masked_gather));
    intrinsicNS.Set("masked_load", Napi::Number::New(env, llvm::Intrinsic::masked_load));
    intrinsicNS.Set("masked_scatter", Napi::Number::New(env, llvm::Intrinsic::masked_scatter));
    intrinsicNS.Set("masked_store", Napi::Number::New(env, llvm::Intrinsic::masked_store));
    intrinsicNS.Set("matrix_column_major_load",
                    Napi::Number::New(env, llvm::Intrinsic::matrix_column_major_load));
    intrinsicNS.Set("matrix_column_major_store",
                    Napi::Number::New(env, llvm::Intrinsic::matrix_column_major_store));
    intrinsicNS.Set("matrix_multiply", Napi::Number::New(env, llvm::Intrinsic::matrix_multiply));
    intrinsicNS.Set("matrix_transpose", Napi::Number::New(env, llvm::Intrinsic::matrix_transpose));
    intrinsicNS.Set("maximum", Napi::Number::New(env, llvm::Intrinsic::maximum));
    intrinsicNS.Set("maxnum", Napi::Number::New(env, llvm::Intrinsic::maxnum));
    intrinsicNS.Set("memcpy", Napi::Number::New(env, llvm::Intrinsic::memcpy));
    intrinsicNS.Set("memcpy_element_unordered_atomic",
                    Napi::Number::New(env, llvm::Intrinsic::memcpy_element_unordered_atomic));
    intrinsicNS.Set("memcpy_inline", Napi::Number::New(env, llvm::Intrinsic::memcpy_inline));
    intrinsicNS.Set("memmove", Napi::Number::New(env, llvm::Intrinsic::memmove));
    intrinsicNS.Set("memmove_element_unordered_atomic",
                    Napi::Number::New(env, llvm::Intrinsic::memmove_element_unordered_atomic));
    intrinsicNS.Set("memset", Napi::Number::New(env, llvm::Intrinsic::memset));
    intrinsicNS.Set("memset_element_unordered_atomic",
                    Napi::Number::New(env, llvm::Intrinsic::memset_element_unordered_atomic));
    intrinsicNS.Set("minimum", Napi::Number::New(env, llvm::Intrinsic::minimum));
    intrinsicNS.Set("minnum", Napi::Number::New(env, llvm::Intrinsic::minnum));
    intrinsicNS.Set("nearbyint", Napi::Number::New(env, llvm::Intrinsic::nearbyint));
    intrinsicNS.Set("objc_arc_annotation_bottomup_bbend",
                    Napi::Number::New(env, llvm::Intrinsic::objc_arc_annotation_bottomup_bbend));
    intrinsicNS.Set("objc_arc_annotation_bottomup_bbstart",
                    Napi::Number::New(env, llvm::Intrinsic::objc_arc_annotation_bottomup_bbstart));
    intrinsicNS.Set("objc_arc_annotation_topdown_bbend",
                    Napi::Number::New(env, llvm::Intrinsic::objc_arc_annotation_topdown_bbend));
    intrinsicNS.Set("objc_arc_annotation_topdown_bbstart",
                    Napi::Number::New(env, llvm::Intrinsic::objc_arc_annotation_topdown_bbstart));
    intrinsicNS.Set("objc_autorelease", Napi::Number::New(env, llvm::Intrinsic::objc_autorelease));
    intrinsicNS.Set("objc_autoreleasePoolPop",
                    Napi::Number::New(env, llvm::Intrinsic::objc_autoreleasePoolPop));
    intrinsicNS.Set("objc_autoreleasePoolPush",
                    Napi::Number::New(env, llvm::Intrinsic::objc_autoreleasePoolPush));
    intrinsicNS.Set("objc_autoreleaseReturnValue",
                    Napi::Number::New(env, llvm::Intrinsic::objc_autoreleaseReturnValue));
    intrinsicNS.Set("objc_clang_arc_noop_use",
                    Napi::Number::New(env, llvm::Intrinsic::objc_clang_arc_noop_use));
    intrinsicNS.Set("objc_clang_arc_use",
                    Napi::Number::New(env, llvm::Intrinsic::objc_clang_arc_use));
    intrinsicNS.Set("objc_copyWeak", Napi::Number::New(env, llvm::Intrinsic::objc_copyWeak));
    intrinsicNS.Set("objc_destroyWeak", Napi::Number::New(env, llvm::Intrinsic::objc_destroyWeak));
    intrinsicNS.Set("objc_initWeak", Napi::Number::New(env, llvm::Intrinsic::objc_initWeak));
    intrinsicNS.Set("objc_loadWeak", Napi::Number::New(env, llvm::Intrinsic::objc_loadWeak));
    intrinsicNS.Set("objc_loadWeakRetained",
                    Napi::Number::New(env, llvm::Intrinsic::objc_loadWeakRetained));
    intrinsicNS.Set("objc_moveWeak", Napi::Number::New(env, llvm::Intrinsic::objc_moveWeak));
    intrinsicNS.Set("objc_release", Napi::Number::New(env, llvm::Intrinsic::objc_release));
    intrinsicNS.Set("objc_retain", Napi::Number::New(env, llvm::Intrinsic::objc_retain));
    intrinsicNS.Set("objc_retain_autorelease",
                    Napi::Number::New(env, llvm::Intrinsic::objc_retain_autorelease));
    intrinsicNS.Set("objc_retainAutorelease",
                    Napi::Number::New(env, llvm::Intrinsic::objc_retainAutorelease));
    intrinsicNS.Set("objc_retainAutoreleaseReturnValue",
                    Napi::Number::New(env, llvm::Intrinsic::objc_retainAutoreleaseReturnValue));
    intrinsicNS.Set("objc_retainAutoreleasedReturnValue",
                    Napi::Number::New(env, llvm::Intrinsic::objc_retainAutoreleasedReturnValue));
    intrinsicNS.Set("objc_retainBlock", Napi::Number::New(env, llvm::Intrinsic::objc_retainBlock));
    intrinsicNS.Set("objc_retainedObject",
                    Napi::Number::New(env, llvm::Intrinsic::objc_retainedObject));
    intrinsicNS.Set("objc_storeStrong", Napi::Number::New(env, llvm::Intrinsic::objc_storeStrong));
    intrinsicNS.Set("objc_storeWeak", Napi::Number::New(env, llvm::Intrinsic::objc_storeWeak));
    intrinsicNS.Set("objc_sync_enter", Napi::Number::New(env, llvm::Intrinsic::objc_sync_enter));
    intrinsicNS.Set("objc_sync_exit", Napi::Number::New(env, llvm::Intrinsic::objc_sync_exit));
    intrinsicNS.Set("objc_unretainedObject",
                    Napi::Number::New(env, llvm::Intrinsic::objc_unretainedObject));
    intrinsicNS.Set("objc_unretainedPointer",
                    Napi::Number::New(env, llvm::Intrinsic::objc_unretainedPointer));
    intrinsicNS.Set("objc_unsafeClaimAutoreleasedReturnValue", Napi::Number::New(env,
                                                                                 llvm::Intrinsic::objc_unsafeClaimAutoreleasedReturnValue));
    intrinsicNS.Set("objectsize", Napi::Number::New(env, llvm::Intrinsic::objectsize));
    intrinsicNS.Set("pcmarker", Napi::Number::New(env, llvm::Intrinsic::pcmarker));
    intrinsicNS.Set("pow", Napi::Number::New(env, llvm::Intrinsic::pow));
    intrinsicNS.Set("powi", Napi::Number::New(env, llvm::Intrinsic::powi));
    intrinsicNS.Set("prefetch", Napi::Number::New(env, llvm::Intrinsic::prefetch));
    intrinsicNS.Set("preserve_array_access_index",
                    Napi::Number::New(env, llvm::Intrinsic::preserve_array_access_index));
    intrinsicNS.Set("preserve_struct_access_index",
                    Napi::Number::New(env, llvm::Intrinsic::preserve_struct_access_index));
    intrinsicNS.Set("preserve_union_access_index",
                    Napi::Number::New(env, llvm::Intrinsic::preserve_union_access_index));
    intrinsicNS.Set("pseudoprobe", Napi::Number::New(env, llvm::Intrinsic::pseudoprobe));
    intrinsicNS.Set("ptr_annotation", Napi::Number::New(env, llvm::Intrinsic::ptr_annotation));
    intrinsicNS.Set("ptrauth_auth", Napi::Number::New(env, llvm::Intrinsic::ptrauth_auth));
    intrinsicNS.Set("ptrauth_blend", Napi::Number::New(env, llvm::Intrinsic::ptrauth_blend));
    intrinsicNS.Set("ptrauth_resign", Napi::Number::New(env, llvm::Intrinsic::ptrauth_resign));
    intrinsicNS.Set("ptrauth_sign", Napi::Number::New(env, llvm::Intrinsic::ptrauth_sign));
    intrinsicNS.Set("ptrauth_sign_generic",
                    Napi::Number::New(env, llvm::Intrinsic::ptrauth_sign_generic));
    intrinsicNS.Set("ptrauth_strip", Napi::Number::New(env, llvm::Intrinsic::ptrauth_strip));
    intrinsicNS.Set("ptrmask", Napi::Number::New(env, llvm::Intrinsic::ptrmask));
    intrinsicNS.Set("read_register", Napi::Number::New(env, llvm::Intrinsic::read_register));
    intrinsicNS.Set("read_volatile_register",
                    Napi::Number::New(env, llvm::Intrinsic::read_volatile_register));
    intrinsicNS.Set("readcyclecounter", Napi::Number::New(env, llvm::Intrinsic::readcyclecounter));
    intrinsicNS.Set("returnaddress", Napi::Number::New(env, llvm::Intrinsic::returnaddress));
    intrinsicNS.Set("rint", Napi::Number::New(env, llvm::Intrinsic::rint));
    intrinsicNS.Set("round", Napi::Number::New(env, llvm::Intrinsic::round));
    intrinsicNS.Set("roundeven", Napi::Number::New(env, llvm::Intrinsic::roundeven));
    intrinsicNS.Set("sadd_sat", Napi::Number::New(env, llvm::Intrinsic::sadd_sat));
    intrinsicNS.Set("sadd_with_overflow",
                    Napi::Number::New(env, llvm::Intrinsic::sadd_with_overflow));
    intrinsicNS.Set("sdiv_fix", Napi::Number::New(env, llvm::Intrinsic::sdiv_fix));
    intrinsicNS.Set("sdiv_fix_sat", Napi::Number::New(env, llvm::Intrinsic::sdiv_fix_sat));
    intrinsicNS.Set("seh_scope_begin", Napi::Number::New(env, llvm::Intrinsic::seh_scope_begin));
    intrinsicNS.Set("seh_scope_end", Napi::Number::New(env, llvm::Intrinsic::seh_scope_end));
    intrinsicNS.Set("seh_try_begin", Napi::Number::New(env, llvm::Intrinsic::seh_try_begin));
    intrinsicNS.Set("seh_try_end", Napi::Number::New(env, llvm::Intrinsic::seh_try_end));
    intrinsicNS.Set("set_loop_iterations",
                    Napi::Number::New(env, llvm::Intrinsic::set_loop_iterations));
    intrinsicNS.Set("set_rounding", Napi::Number::New(env, llvm::Intrinsic::set_rounding));
    intrinsicNS.Set("sideeffect", Napi::Number::New(env, llvm::Intrinsic::sideeffect));
    intrinsicNS.Set("sin", Napi::Number::New(env, llvm::Intrinsic::sin));
    intrinsicNS.Set("smax", Napi::Number::New(env, llvm::Intrinsic::smax));
    intrinsicNS.Set("smin", Napi::Number::New(env, llvm::Intrinsic::smin));
    intrinsicNS.Set("smul_fix", Napi::Number::New(env, llvm::Intrinsic::smul_fix));
    intrinsicNS.Set("smul_fix_sat", Napi::Number::New(env, llvm::Intrinsic::smul_fix_sat));
    intrinsicNS.Set("smul_with_overflow",
                    Napi::Number::New(env, llvm::Intrinsic::smul_with_overflow));
    intrinsicNS.Set("sponentry", Napi::Number::New(env, llvm::Intrinsic::sponentry));
    intrinsicNS.Set("sqrt", Napi::Number::New(env, llvm::Intrinsic::sqrt));
    intrinsicNS.Set("ssa_copy", Napi::Number::New(env, llvm::Intrinsic::ssa_copy));
    intrinsicNS.Set("sshl_sat", Napi::Number::New(env, llvm::Intrinsic::sshl_sat));
    intrinsicNS.Set("ssub_sat", Napi::Number::New(env, llvm::Intrinsic::ssub_sat));
    intrinsicNS.Set("ssub_with_overflow",
                    Napi::Number::New(env, llvm::Intrinsic::ssub_with_overflow));
    intrinsicNS.Set("stackguard", Napi::Number::New(env, llvm::Intrinsic::stackguard));
    intrinsicNS.Set("stackprotector", Napi::Number::New(env, llvm::Intrinsic::stackprotector));
    intrinsicNS.Set("stackrestore", Napi::Number::New(env, llvm::Intrinsic::stackrestore));
    intrinsicNS.Set("stacksave", Napi::Number::New(env, llvm::Intrinsic::stacksave));
    intrinsicNS.Set("start_loop_iterations",
                    Napi::Number::New(env, llvm::Intrinsic::start_loop_iterations));
    intrinsicNS.Set("strip_invariant_group",
                    Napi::Number::New(env, llvm::Intrinsic::strip_invariant_group));
    intrinsicNS.Set("swift_async_context_addr",
                    Napi::Number::New(env, llvm::Intrinsic::swift_async_context_addr));
    intrinsicNS.Set("test_set_loop_iterations",
                    Napi::Number::New(env, llvm::Intrinsic::test_set_loop_iterations));
    intrinsicNS.Set("test_start_loop_iterations",
                    Napi::Number::New(env, llvm::Intrinsic::test_start_loop_iterations));
    intrinsicNS.Set("thread_pointer", Napi::Number::New(env, llvm::Intrinsic::thread_pointer));
    intrinsicNS.Set("trap", Napi::Number::New(env, llvm::Intrinsic::trap));
    intrinsicNS.Set("trunc", Napi::Number::New(env, llvm::Intrinsic::trunc));
    intrinsicNS.Set("type_checked_load",
                    Napi::Number::New(env, llvm::Intrinsic::type_checked_load));
    intrinsicNS.Set("type_test", Napi::Number::New(env, llvm::Intrinsic::type_test));
    intrinsicNS.Set("uadd_sat", Napi::Number::New(env, llvm::Intrinsic::uadd_sat));
    intrinsicNS.Set("uadd_with_overflow",
                    Napi::Number::New(env, llvm::Intrinsic::uadd_with_overflow));
    intrinsicNS.Set("ubsantrap", Napi::Number::New(env, llvm::Intrinsic::ubsantrap));
    intrinsicNS.Set("udiv_fix", Napi::Number::New(env, llvm::Intrinsic::udiv_fix));
    intrinsicNS.Set("udiv_fix_sat", Napi::Number::New(env, llvm::Intrinsic::udiv_fix_sat));
    intrinsicNS.Set("umax", Napi::Number::New(env, llvm::Intrinsic::umax));
    intrinsicNS.Set("umin", Napi::Number::New(env, llvm::Intrinsic::umin));
    intrinsicNS.Set("umul_fix", Napi::Number::New(env, llvm::Intrinsic::umul_fix));
    intrinsicNS.Set("umul_fix_sat", Napi::Number::New(env, llvm::Intrinsic::umul_fix_sat));
    intrinsicNS.Set("umul_with_overflow",
                    Napi::Number::New(env, llvm::Intrinsic::umul_with_overflow));
    intrinsicNS.Set("ushl_sat", Napi::Number::New(env, llvm::Intrinsic::ushl_sat));
    intrinsicNS.Set("usub_sat", Napi::Number::New(env, llvm::Intrinsic::usub_sat));
    intrinsicNS.Set("usub_with_overflow",
                    Napi::Number::New(env, llvm::Intrinsic::usub_with_overflow));
    intrinsicNS.Set("vacopy", Napi::Number::New(env, llvm::Intrinsic::vacopy));
    intrinsicNS.Set("vaend", Napi::Number::New(env, llvm::Intrinsic::vaend));
    intrinsicNS.Set("vastart", Napi::Number::New(env, llvm::Intrinsic::vastart));
    intrinsicNS.Set("var_annotation", Napi::Number::New(env, llvm::Intrinsic::var_annotation));
    intrinsicNS.Set("vector_reduce_add",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_add));
    intrinsicNS.Set("vector_reduce_and",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_and));
    intrinsicNS.Set("vector_reduce_fadd",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_fadd));
    intrinsicNS.Set("vector_reduce_fmax",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_fmax));
    intrinsicNS.Set("vector_reduce_fmin",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_fmin));
    intrinsicNS.Set("vector_reduce_fmul",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_fmul));
    intrinsicNS.Set("vector_reduce_mul",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_mul));
    intrinsicNS.Set("vector_reduce_or", Napi::Number::New(env, llvm::Intrinsic::vector_reduce_or));
    intrinsicNS.Set("vector_reduce_smax",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_smax));
    intrinsicNS.Set("vector_reduce_smin",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_smin));
    intrinsicNS.Set("vector_reduce_umax",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_umax));
    intrinsicNS.Set("vector_reduce_umin",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_umin));
    intrinsicNS.Set("vector_reduce_xor",
                    Napi::Number::New(env, llvm::Intrinsic::vector_reduce_xor));
    intrinsicNS.Set("vp_add", Napi::Number::New(env, llvm::Intrinsic::vp_add));
    intrinsicNS.Set("vp_and", Napi::Number::New(env, llvm::Intrinsic::vp_and));
    intrinsicNS.Set("vp_ashr", Napi::Number::New(env, llvm::Intrinsic::vp_ashr));
    intrinsicNS.Set("vp_fadd", Napi::Number::New(env, llvm::Intrinsic::vp_fadd));
    intrinsicNS.Set("vp_fdiv", Napi::Number::New(env, llvm::Intrinsic::vp_fdiv));
    intrinsicNS.Set("vp_fmul", Napi::Number::New(env, llvm::Intrinsic::vp_fmul));
    intrinsicNS.Set("vp_frem", Napi::Number::New(env, llvm::Intrinsic::vp_frem));
    intrinsicNS.Set("vp_fsub", Napi::Number::New(env, llvm::Intrinsic::vp_fsub));
    intrinsicNS.Set("vp_gather", Napi::Number::New(env, llvm::Intrinsic::vp_gather));
    intrinsicNS.Set("vp_load", Napi::Number::New(env, llvm::Intrinsic::vp_load));
    intrinsicNS.Set("vp_lshr", Napi::Number::New(env, llvm::Intrinsic::vp_lshr));
    intrinsicNS.Set("vp_merge", Napi::Number::New(env, llvm::Intrinsic::vp_merge));
    intrinsicNS.Set("vp_mul", Napi::Number::New(env, llvm::Intrinsic::vp_mul));
    intrinsicNS.Set("vp_or", Napi::Number::New(env, llvm::Intrinsic::vp_or));
    intrinsicNS.Set("vp_reduce_add", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_add));
    intrinsicNS.Set("vp_reduce_and", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_and));
    intrinsicNS.Set("vp_reduce_fadd", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_fadd));
    intrinsicNS.Set("vp_reduce_fmax", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_fmax));
    intrinsicNS.Set("vp_reduce_fmin", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_fmin));
    intrinsicNS.Set("vp_reduce_fmul", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_fmul));
    intrinsicNS.Set("vp_reduce_mul", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_mul));
    intrinsicNS.Set("vp_reduce_or", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_or));
    intrinsicNS.Set("vp_reduce_smax", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_smax));
    intrinsicNS.Set("vp_reduce_smin", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_smin));
    intrinsicNS.Set("vp_reduce_umax", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_umax));
    intrinsicNS.Set("vp_reduce_umin", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_umin));
    intrinsicNS.Set("vp_reduce_xor", Napi::Number::New(env, llvm::Intrinsic::vp_reduce_xor));
    intrinsicNS.Set("vp_scatter", Napi::Number::New(env, llvm::Intrinsic::vp_scatter));
    intrinsicNS.Set("vp_sdiv", Napi::Number::New(env, llvm::Intrinsic::vp_sdiv));
    intrinsicNS.Set("vp_select", Napi::Number::New(env, llvm::Intrinsic::vp_select));
    intrinsicNS.Set("vp_shl", Napi::Number::New(env, llvm::Intrinsic::vp_shl));
    intrinsicNS.Set("vp_srem", Napi::Number::New(env, llvm::Intrinsic::vp_srem));
    intrinsicNS.Set("vp_store", Napi::Number::New(env, llvm::Intrinsic::vp_store));
    intrinsicNS.Set("vp_sub", Napi::Number::New(env, llvm::Intrinsic::vp_sub));
    intrinsicNS.Set("vp_udiv", Napi::Number::New(env, llvm::Intrinsic::vp_udiv));
    intrinsicNS.Set("vp_urem", Napi::Number::New(env, llvm::Intrinsic::vp_urem));
    intrinsicNS.Set("vp_xor", Napi::Number::New(env, llvm::Intrinsic::vp_xor));
    intrinsicNS.Set("vscale", Napi::Number::New(env, llvm::Intrinsic::vscale));
    intrinsicNS.Set("write_register", Napi::Number::New(env, llvm::Intrinsic::write_register));
    intrinsicNS.Set("xray_customevent", Napi::Number::New(env, llvm::Intrinsic::xray_customevent));
    intrinsicNS.Set("xray_typedevent", Napi::Number::New(env, llvm::Intrinsic::xray_typedevent));
    intrinsicNS.Set("getDeclaration", Napi::Function::New(env, getDeclaration));
    exports.Set("Intrinsic", intrinsicNS);
}
