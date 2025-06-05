module;
#include <glm/glm.hpp>
#include <string>
export module lys.rendering.shader;

import lys.core.io.file;

namespace Lys
{
	export enum ShaderType { Vertex, Fragment, Geometry, Compute };

	export class IShader
	{
	protected:
		unsigned int m_id{};
		int m_type{};

		File m_source{};

	public:
		IShader() = default;

		virtual ~IShader() = default;

		virtual void compile() = 0;

		[[nodiscard]] unsigned int get_id() const
		{
			return m_id;
		}
	};

	export class IShaderProgram
	{
	protected:
		unsigned int m_id{};
		std::vector<std::shared_ptr<IShader>> m_shaders{};

	public:
		virtual ~IShaderProgram() = default;

		virtual void link() = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		// Uniform setters
		virtual void set_uniform(const std::string& name, const glm::mat2& value) const = 0;
		virtual void set_uniform(const std::string& name, const glm::mat3& value) const = 0;
		virtual void set_uniform(const std::string& name, const glm::mat4& value) const = 0;

		virtual void set_uniform(const std::string& name, const glm::vec2& value) const = 0;
		virtual void set_uniform(const std::string& name, const glm::vec3& value) const = 0;
		virtual void set_uniform(const std::string& name, const glm::vec4& value) const = 0;

		virtual void set_uniform(const std::string& name, const glm::ivec2& value) const = 0;
		virtual void set_uniform(const std::string& name, const glm::ivec3& value) const = 0;
		virtual void set_uniform(const std::string& name, const glm::ivec4& value) const = 0;

		virtual void set_uniform(const std::string& name, const glm::uvec2& value) const = 0;
		virtual void set_uniform(const std::string& name, const glm::uvec3& value) const = 0;
		virtual void set_uniform(const std::string& name, const glm::uvec4& value) const = 0;

		virtual void set_uniform(const std::string& name, int value) const = 0;
		virtual void set_uniform(const std::string& name, uint32_t value) const = 0;
		virtual void set_uniform(const std::string& name, float value) const = 0;
		virtual void set_uniform(const std::string& name, double value) const = 0;
		virtual void set_uniform(const std::string& name, bool value) const = 0;

		[[nodiscard]] virtual int get_uniform_location(const std::string& name) const = 0;

		[[nodiscard]] unsigned int get_id() const
		{
			return m_id;
		}
	};
}; // namespace Lys
