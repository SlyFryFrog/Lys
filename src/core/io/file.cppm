module;
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
export module lys.core.io.file;

import lys.utils;

namespace Lys
{
	export class File
	{
		std::string m_path;
		bool m_relative{true};

	public:
		File() = default;

		explicit File(const std::string& path) : m_path(WorkingDirectory + path)
		{
		}

		explicit File(const std::string& path, const bool relative) : m_relative(relative)
		{
			if (!relative)
			{
				m_path = WorkingDirectory;
			}

			m_path += path;
		}

		/**
		 * @brief Reads the contents of the path assigned to the File instance.
		 *
		 * @return std::string Contents stored in the file.
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
				std::println(std::cerr, "Failed to open file: {}", path);
			}

			std::ostringstream ss;
			ss << file.rdbuf();
			return ss.str();
		}

		/**
		 * @brief
		 *
		 * @param contents
		 * @param operation
		 * @return
		 */
		[[nodiscard]] bool write(const std::string& contents,
								 const std::ios::openmode operation) const
		{
			std::ofstream file(m_path, operation);

			if (!file)
			{
				std::println(std::cerr, "Failed to open file: {}", m_path);
				return false;
			}

			file << contents;

			return true;
		}

		[[nodiscard]] bool write(const std::vector<std::uint8_t>& contents,
								 const std::ios::openmode operation) const
		{
			std::ofstream file(m_path, operation);

			if (!file)
			{
				std::println(std::cerr, "Failed to open file: {}", m_path);
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

		[[nodiscard]] std::filesystem::path get_path() const
		{
			return m_path;
		}

		void set_path(const std::string& path)
		{
			if (!m_relative)
			{
				m_path = WorkingDirectory;
			}

			m_path += path;
		}
	};
} // namespace Lys
