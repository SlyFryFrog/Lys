module;
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
export module lys.opengl.gl_shader;

import lys.core.io.file;
import lys.rendering.shader;

namespace Lys
{
	export struct Shaders
	{
		std::string vertex{};
		std::string fragment{};
	};

	export class OpenGLShader : IShader
	{
		unsigned int m_id;
		Shaders m_shaders;

	public:
		explicit OpenGLShader(const Shaders& shaders)
		{
			m_shaders = shaders;
			m_id = create();
		}

		void bind() const override
		{
			glUseProgram(m_id);
		}

		void unbind() const override
		{
			glUseProgram(0);
		}

		unsigned int create()
		{
			// Invalid shader, needs at minimum vertex and fragment shaders
			if (m_shaders.vertex.empty() || m_shaders.fragment.empty())
			{
				return 0;
			}
		}

		void set_uniform_mat2(const std::string& name, const glm::mat2& matrix) const override
		{
			glUniformMatrix2fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
		}

		void set_uniform_mat3(const std::string& name, const glm::mat3& matrix) const override
		{
			glUniformMatrix3fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
		}

		void set_uniform_mat4(const std::string& name, const glm::mat4& matrix) const override
		{
			glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, &matrix[0][0]);
		}


		void set_uniform_vec2(const std::string& name, const glm::vec2& vector) const override
		{
			glUniform2dv(get_uniform_location(name), 1, (double*)glm::value_ptr(vector));
		}

		void set_uniform_vec3(const std::string& name, const glm::vec3& vector) const override
		{
			glUniform3dv(get_uniform_location(name), 1, (double*)glm::value_ptr(vector));
		}

		void set_uniform_vec4(const std::string& name, const glm::vec4& vector) const override
		{
			glUniform4dv(get_uniform_location(name), 1, (double*)glm::value_ptr(vector));
		}


		void set_uniform_uint(const std::string& name, unsigned int value) const override
		{
			glUniform1ui(get_uniform_location(name), value);
		}

		void set_uniform_uint2(const std::string& name, const glm::uvec2& value) const override
		{
			glUniform2uiv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		void set_uniform_uint3(const std::string& name, const glm::uvec3& value) const override
		{
			glUniform3uiv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		void set_uniform_uint4(const std::string& name, const glm::uvec4& value) const override
		{
			glUniform4uiv(get_uniform_location(name), 1, glm::value_ptr(value));
		}


		void set_uniform_float(const std::string& name, float value) const override
		{
			glUniform1f(get_uniform_location(name), value);
		}

		void set_uniform_float2(const std::string& name, const glm::fvec2& value) const override
		{
			glUniform2fv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		void set_uniform_float3(const std::string& name, const glm::fvec3& value) const override
		{
			glUniform3fv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		void set_uniform_float4(const std::string& name, const glm::fvec4& value) const override
		{
			glUniform4fv(get_uniform_location(name), 1, glm::value_ptr(value));
		}

		void set_uniform_bool(const std::string& name, bool value) const override
		{
			glUniform1i(get_uniform_location(name), value);
		}

		[[nodiscard]] int get_uniform_location(const std::string& name) const override
		{
			int location = glGetUniformLocation(m_id, name.c_str());
			if (location == -1)
			{
				std::cout << "Warning: uniform " << name << " doesn't exist!";
			}
			return location;
		}
	};
} // namespace Lys
