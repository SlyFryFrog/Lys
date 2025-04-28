module;
#include <cstdint>
#include <vector>
#include <filesystem>
#include <fstream>
#include <ios>
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

		/**
		 * @brief
		 *
		 * @return std::string
		 */
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

		bool write(const std::string& contents, std::ios::openmode operation)
		{
			std::ofstream file(m_path, operation);

			if (!file)
			{
				std::cout << "Failed to open file: " + m_path;
				return false;
			}

			file << contents;

			return true;
		}

		bool write(const std::vector<std::uint8_t>& contents, std::ios::openmode operation)
		{
			std::ofstream file(m_path, operation);

			if (!file)
			{
				std::cout << "Failed to open file: " + m_path;
				return false;
			}

			file << contents.data();

			return true;
		}

		[[nodiscard]] bool exists() const
		{
			return std::filesystem::exists(m_path);
		}

		[[nodiscard]] size_t file_size() const
		{
			return std::filesystem::file_size(m_path);
		}

		[[nodiscard]] std::filesystem::path path() const
		{
			return m_path;
		}
	};
} // namespace Lys
