module;
#include <cstdlib>
#include <cxxabi.h>
#include <filesystem>
#include <memory>
#include <string>
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif
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

	std::filesystem::path get_executable_path()
	{
		char buffer[PATH_MAX];
		uint32_t size = sizeof(buffer);
#ifdef __APPLE__
		if (_NSGetExecutablePath(buffer, &size) == 0)
		{
			return std::filesystem::canonical(buffer);
		}
#endif
		return {}; // Handle failure
	}


	export const std::string WorkingDirectory = get_executable_path().parent_path();
} // namespace Lys
