module;
#include <cxxabi.h>
#include <filesystem>
#include <memory>
#include <string>

#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif
export module lys.utils;

namespace Lys
{
	std::shared_ptr<char> cpp_demangle(const char* abiName)
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

	/**
	 * @brief Returns the absolute path to the running executable.
	 *
	 * @return Absolute path to the executable.
	 *
	 * @note Works on macOS and Linux. Returns an empty path on failure.
	 */
	std::filesystem::path get_working_directory()
	{
		// MacOS doesn't use the pwd of the executable when launching from clicking on the
		// executable directly.
#if defined(__APPLE__)
		char buffer[PATH_MAX];
		uint32_t size = sizeof(buffer);
		if (_NSGetExecutablePath(buffer, &size) == 0)
		{
			return std::filesystem::canonical(buffer).parent_path();
		}
#endif
		// Default implementation
		return std::filesystem::current_path().string();
	}

	/**
	 * @brief Current working directory where the executable is located.
	 */
	export const std::string WorkingDirectory = get_working_directory();

	export float ClearColor[4] = {0.3f, 0.3f, 0.3f, 1.0};
} // namespace Lys
