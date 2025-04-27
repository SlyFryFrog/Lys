module;
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
export module lys.core.io.file;

namespace Lys
{
	export class File
	{
		std::string m_path;

	public:
		File() = default;
		explicit File(const std::string& path) : m_path(path)
		{
		}

		[[nodiscard]] std::string read() const
		{
			return read(m_path);
		}

		/**
		 * @brief Returns a string of a file's contents. If it fails to read, it will simply print
		 * an error.
		 *
		 * @param path Path to the file, relative or absolute.
		 * @return std::string Contents of the file.
		 */
		static std::string read(const std::string& path)
		{
			std::ifstream file(path);
			if (!file)
			{
				std::cout << "Failed to open file: " + path;
			}

			std::ostringstream ss;
			ss << file.rdbuf();
			return ss.str();
		}
	};
} // namespace Lys
