module;
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <print>
#include <string>
export module lys.opengl.gl_shader;

export import lys.rendering.shader;
import lys.core.io.file;

namespace Lys
{
	export class GLShader final : public IShader
	{
	public:
		explicit GLShader(const ShaderType type, const std::string& file) : IShader()
		{
			m_type = type;
			m_source = File(file);
		}

		~GLShader() override = default;

		void compile() override
		{
			// Give OpenGL the appropriate shader type during creation
			if (m_type == Vertex)
			{
				m_id = glCreateShader(GL_VERTEX_SHADER);
			}
			else if (m_type == Fragment)
			{
				m_id = glCreateShader(GL_FRAGMENT_SHADER);
			}
			else if (m_type == Geometry)
			{
				m_id = glCreateShader(GL_GEOMETRY_SHADER);
			}
			else if (m_type == Compute)
			{
				m_id = glCreateShader(GL_COMPUTE_SHADER);
			}

			// Shader code, .glsl
			const std::string strSrc = m_source.read();
			const char* src = strSrc.c_str();

			glShaderSource(m_id, 1, &src, nullptr);
			glCompileShader(m_id);

			check_compile_status();
		}

		void check_compile_status() const
		{
			GLint success;
			glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

			if (success == GL_FALSE)
			{
				char log[512];
				glGetShaderInfoLog(m_id, 512, nullptr, log);
				std::println(std::cerr, "Shader compile error:\n{}", std::string(log));
			}
		}
	};


	export class GLShaderProgram final : public IShaderProgram
	{
	public:
		GLShaderProgram() = default;

		explicit GLShaderProgram(const std::vector<std::shared_ptr<IShader>>& shaders) : IShaderProgram()
		{
			m_shaders = shaders;
		}

		~GLShaderProgram() override = default;

		void link() override
		{
			// Reset program id if it already exists
			if (m_id)
			{
				glDeleteProgram(m_id);
			}
			m_id = glCreateProgram();

			for (const auto& shader : m_shaders)
			{
				shader->compile();
				glAttachShader(m_id, shader->get_id());
			}

			glLinkProgram(m_id);

			GLint success;
			glGetProgramiv(m_id, GL_LINK_STATUS, &success);

			if (!success)
			{
				char infoLog[512];
				glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
				std::println("Shader program linking failed: {0}", std::string(infoLog));
			}

			for (const auto& shader : m_shaders)
			{
				glDetachShader(m_id, shader->get_id());
			}

			m_shaders.clear();
		}

		/**
		 * @brief Binds the shader program for use in subsequent OpenGL rendering calls.
		 */
		void bind() const override
		{
			glUseProgram(m_id);
		}

		/**
		 * @brief Unbinds the current shader program by setting the active program to 0.
		 */
		void unbind() const override
		{
			glUseProgram(0);
		}

		void set_uniform(const std::string& name, const glm::mat2& matrix) const override
		{
			glUniformMatrix2fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
		}

		void set_uniform(const std::string& name, const glm::mat3& matrix) const override
		{
			glUniformMatrix3fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
		}

		void set_uniform(const std::string& name, const glm::mat4& matrix) const override
		{
			glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
		}

		void set_uniform(const std::string& name, const int value) const override
		{
			glUniform1i(get_uniform_location(name), value);
		}

		void set_uniform(const std::string& name, const glm::ivec2& value) const override
		{
			glUniform2iv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		void set_uniform(const std::string& name, const glm::ivec3& value) const override
		{
			glUniform3iv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		void set_uniform(const std::string& name, const glm::ivec4& value) const override
		{
			glUniform4iv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		/**
		 * @brief Sets a uint (unsigned int) uniform variable in the shader program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The uint value to set.
		 */
		void set_uniform(const std::string& name, unsigned int value) const override
		{
			glUniform1ui(get_uniform_location(name), value);
		}

		/**
		 * @brief Sets a vec2 (consisting of 2 unsigned ints) uniform variable in the shader
		 * program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The uvec2 value to set.
		 */
		void set_uniform(const std::string& name, const glm::uvec2& value) const override
		{
			glUniform2uiv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		/**
		 * @brief Sets a vec3 (consisting of 3 unsigned ints) uniform variable in the shader
		 * program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The uvec3 value to set.
		 */
		void set_uniform(const std::string& name, const glm::uvec3& value) const override
		{
			glUniform3uiv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		/**
		 * @brief Sets a vec4 (consisting of 4 unsigned ints) uniform variable in the shader
		 * program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The uvec4 value to set.
		 */
		void set_uniform(const std::string& name, const glm::uvec4& value) const override
		{
			glUniform4uiv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		/**
		 * @brief Sets a float uniform variable in the shader program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The float value to set.
		 */
		void set_uniform(const std::string& name, const float value) const override
		{
			glUniform1f(get_uniform_location(name), value);
		}

		/**
		 * @brief Sets a vec2 (consisting of 2 floats) uniform variable in the shader program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The fvec2 value to set.
		 */
		void set_uniform(const std::string& name, const glm::vec2& value) const override
		{
			glUniform2fv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		/**
		 * @brief Sets a vec3 (consisting of 3 floats) uniform variable in the shader program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The fvec3 value to set.
		 */
		void set_uniform(const std::string& name, const glm::vec3& value) const override
		{
			glUniform3fv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		/**
		 * @brief Sets a vec4 (consisting of 4 floats) uniform variable in the shader program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The fvec4 value to set.
		 */
		void set_uniform(const std::string& name, const glm::vec4& value) const override
		{
			glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		void set_uniform(const std::string& name, const double value) const override
		{
			glUniform1d(get_uniform_location(name), value);
		}

		/**
		 * @brief Sets a boolean uniform variable in the shader program.
		 *
		 * @param name The name of the uniform variable.
		 * @param value The boolean value to set.
		 */
		void set_uniform(const std::string& name, const bool value) const override
		{
			glUniform1i(get_uniform_location(name), value);
		}

		/**
		 * @brief Retrieves the location of a uniform variable in the shader program.
		 *
		 * @param name The name of the uniform variable.
		 * @return The location of the uniform variable, or -1 if not found.
		 */
		[[nodiscard]] int get_uniform_location(const std::string& name) const override
		{
			const int location = glGetUniformLocation(m_id, name.c_str());

			if (location == -1)
			{
				std::println(std::cerr, "Warning: uniform \"{0}\" doesn't exist!\n", name);
			}

			return location;
		}
	};
} // namespace Lys
