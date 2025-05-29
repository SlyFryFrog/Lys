module;
#include <julia.h>
#include <string>
#include <vector>
export module lys.core.scripting.julia.julia_engine;

JULIA_DEFINE_FAST_TLS

namespace Lys
{
	export class JuliaEngine
	{
	public:
		static void init()
		{
			jl_init();
		}

		static void shutdown()
		{
			jl_atexit_hook(0);
		}

		static void load_script(const std::string& path)
		{
			jl_eval_string(("include(\"" + path + "\")").c_str());
		}

		static jl_value_t* call_function(const std::string& mod, const std::string& func,
										 std::vector<jl_value_t*>* args)
		{
			jl_module_t* jl_mod = (jl_module_t*)jl_eval_string(mod.c_str());
			if (!jl_mod || !jl_is_module(jl_mod))
			{
				jl_printf(jl_stderr_stream(), "Failed to find module: %s\n", mod.c_str());
				return nullptr;
			}

			jl_function_t* jl_func = jl_get_function(jl_mod, func.c_str());
			if (!jl_func)
			{
				jl_printf(jl_stderr_stream(), "Failed to find function %s in module %s\n",
						  func.c_str(), mod.c_str());
				return nullptr;
			}

			jl_value_t* jl_return_val;
			if (args)
			{
				jl_call(jl_func, args->data(), args->size());
			}
			else
			{
				jl_call0(jl_func);
			}

			if (jl_exception_occurred())
			{
				jl_printf(jl_stderr_stream(),
						  "Exception was throw when calling function %s in module %s\nJulia "
						  "Exception: %s\n",
						  func.c_str(), mod.c_str(), jl_typeof_str(jl_exception_occurred()));
				return nullptr;
			}

			return jl_return_val;
		}
	};
} // namespace Lys
