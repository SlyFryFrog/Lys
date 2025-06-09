module;
#include <cxxabi.h>
#include <filesystem>
#include <memory>
#include <string>

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#elif defined(__linux__)
#include <unistd.h>
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
	std::shared_ptr<char> class_name(const T* ptr)
	{
		return cpp_demangle(typeid(*ptr).name());
	}

	std::filesystem::path get_executable_path()
	{
#if defined(__APPLE__)
		char buffer[PATH_MAX];
		uint32_t size = sizeof(buffer);
		if (_NSGetExecutablePath(buffer, &size) == 0)
		{
			return std::filesystem::canonical(buffer);
		}
#elif defined(__linux__)
		char buffer[PATH_MAX];
		ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer));
		if (count != -1)
		{
			return std::filesystem::canonical(std::string(buffer, count));
		}
#endif

		return {}; // Handle failure
	}


	export const std::string WorkingDirectory = get_executable_path().parent_path();
} // namespace Lys
