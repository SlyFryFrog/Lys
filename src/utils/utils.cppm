module;
#include <cstdlib>
#include <cxxabi.h>
#include <memory>
export module lys.utils;

namespace Lys
{
	export std::shared_ptr<char> cpp_demangle(const char* abiName)
	{
		int status;
		char* ret = abi::__cxa_demangle(abiName, nullptr, nullptr, &status);

		/* NOTE: must free() the returned char when done with it! */
		std::shared_ptr<char> retval;
		retval.reset(ret,
					 [](const char* mem)
					 {
						 if (mem)
						 {
							 free((void*)mem);
						 }
					 });
		return retval;
	}

	export template <typename T>
	std::shared_ptr<char> class_name([[maybe_unused]] const T* ptr)
	{
		return cpp_demangle(typeid(*ptr).name());
	}
} // namespace Lys
