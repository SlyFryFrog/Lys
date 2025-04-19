module;
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
export module file;

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
