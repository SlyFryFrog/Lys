module;
#include <cstdlib>
#include <cxxabi.h>
#include <filesystem>
#include <memory>
#include <string>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#elifdef __linux__
#include <limits.h>
#include <unistd.h>
#elifdef _WIN32
#include <windows.h>
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
#ifdef __APPLE__
		char buffer[PATH_MAX];
		uint32_t size = sizeof(buffer);
		if (_NSGetExecutablePath(buffer, &size) == 0)
		{
			return std::filesystem::canonical(buffer);
		}
#elif __linux__
		char buffer[PATH_MAX];
		ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer));
		if (count != -1)
		{
			return std::filesystem::canonical(std::string(buffer, count));
		}
#elif _WIN32
		wchar_t buffer[MAX_PATH];
		DWORD length = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
		if (length > 0 && length < MAX_PATH)
		{
			return std::filesystem::canonical(std::filesystem::path(buffer));
		}
#endif

		return {}; // Handle failure
	}


	export const std::string WorkingDirectory = get_executable_path().parent_path();
} // namespace Lys
