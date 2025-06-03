module;
#include <glm/glm.hpp>
#include <string>
export module lys.rendering.shader;

import lys.core.io.file;

namespace Lys
{
	export class IShader
	{
	public:
		virtual ~IShader() = default;

		virtual void bind() const = 0;
        virtual void unbind() const = 0;
        
		// Matrices
		virtual void set_uniform_mat2(const std::string& name, const glm::mat2& matrix) const = 0;
		virtual void set_uniform_mat3(const std::string& name, const glm::mat3& matrix) const = 0;
		virtual void set_uniform_mat4(const std::string& name, const glm::mat4& matrix) const = 0;

		// Vectors
		virtual void set_uniform_vec2(const std::string& name, const glm::vec2& vector) const = 0;
		virtual void set_uniform_vec3(const std::string& name, const glm::vec3& vector) const = 0;
		virtual void set_uniform_vec4(const std::string& name, const glm::vec4& vector) const = 0;

		// Scalars
		virtual void set_uniform_int(const std::string& name, int value) const = 0;
		virtual void set_uniform_int2(const std::string& name, const glm::ivec2& value) const = 0;
		virtual void set_uniform_int3(const std::string& name, const glm::ivec3& value) const = 0;
		virtual void set_uniform_int4(const std::string& name, const glm::ivec4& value) const = 0;

		virtual void set_uniform_uint(const std::string& name, uint32_t value) const = 0;
		virtual void set_uniform_uint2(const std::string& name, const glm::uvec2& value) const = 0;
		virtual void set_uniform_uint3(const std::string& name, const glm::uvec3& value) const = 0;
		virtual void set_uniform_uint4(const std::string& name, const glm::uvec4& value) const = 0;

		virtual void set_uniform_float(const std::string& name, float value) const = 0;
		virtual void set_uniform_float2(const std::string& name, const glm::vec2& value) const = 0;
		virtual void set_uniform_float3(const std::string& name, const glm::vec3& value) const = 0;
		virtual void set_uniform_float4(const std::string& name, const glm::vec4& value) const = 0;

		virtual void set_uniform_bool(const std::string& name, bool value) const = 0;

		[[nodiscard]] virtual int get_uniform_location(const std::string& name) const = 0;
	};

	export class IShaderProgram
	{
	public:
	};
}; // namespace Lys
