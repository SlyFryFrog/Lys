module;
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <vector>
export module lys.opengl.gl_vertex_array;

namespace Lys::GL
{
	export enum DataType : unsigned int {
		FLOAT = GL_FLOAT,
		INT = GL_INT,
		UINT = GL_UNSIGNED_INT,
		BOOL = GL_BOOL,
		DOUBLE = GL_DOUBLE
	};

	export int sizeof_data_type(const DataType type)
	{
		switch (type)
		{
		case DataType::FLOAT:
			return sizeof(float);
		case DataType::INT:
			return sizeof(int);
		case DataType::UINT:
			return sizeof(unsigned int);
		case DataType::BOOL:
			return sizeof(bool);
		case DataType::DOUBLE:
			return sizeof(double);
		}

		return 0;
	}

	export struct VertexAttribute
	{
		int index;
		int size;
		DataType type;
		bool normalized;
		int offset;
	};

	export class VertexLayout
	{
		std::vector<VertexAttribute> m_data;
		int m_stride{};

	public:
		VertexLayout() = default;

		explicit VertexLayout(const std::vector<VertexAttribute>& data) : m_data(data)
		{
		}

		void add_attribute(const int index, const int size, const DataType type,
						   const bool normalized)
		{
			VertexAttribute attrib(index, size, type, normalized);
			attrib.offset = m_stride;

			m_data.emplace_back(attrib);
			m_stride += attrib.size * sizeof_data_type(type);
		}

		void add_attribute(VertexAttribute attrib)
		{
			attrib.offset = m_stride;

			m_data.emplace_back(attrib);
			m_stride += attrib.size * sizeof_data_type(attrib.type);
		}

		void add_attributes(const std::vector<VertexAttribute>& data)
		{
			for (const VertexAttribute attrib : data)
			{
				add_attribute(attrib.index, attrib.size, attrib.type, attrib.normalized);
			}
		}

		template <std::size_t T>
		void add_attributes(const std::array<VertexAttribute, T>& data)
		{
			for (const VertexAttribute attrib : data)
			{
				add_attribute(attrib.index, attrib.size, attrib.type, attrib.normalized);
			}
		}

		void enable_attributes() const
		{
			for (const auto& attrib : m_data)
			{
				glVertexAttribPointer(attrib.index, attrib.size, attrib.type, attrib.normalized,
									  m_stride, reinterpret_cast<const void*>(attrib.offset));

				glEnableVertexAttribArray(attrib.index);
			}
		}
	};

	export class VertexArray
	{
		unsigned int m_id{};

	public:
		VertexArray()
		{
			glGenVertexArrays(1, &m_id);
		}

		VertexArray(const VertexArray&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;

		VertexArray(VertexArray&& other) noexcept
		{
			m_id = other.m_id;
			other.m_id = 0;
		}

		~VertexArray()
		{
			if (m_id)
			{
				glDeleteVertexArrays(1, &m_id);
			}
		}

		[[nodiscard]] unsigned int get_id() const
		{
			return m_id;
		}

		void bind() const
		{
			glBindVertexArray(m_id);
		}

		void unbind() const
		{
			glBindVertexArray(0);
		}

		void set_vertex_attrib_pointer(const int index, const int size, const DataType type,
									   const bool normalized, const int stride,
									   const void* pointer) const
		{
			glBindVertexArray(m_id);
			glVertexAttribPointer(index, size, type, normalized, stride, pointer);
			glEnableVertexAttribArray(index);
		}
	};

	export class VertexBuffer
	{
		unsigned int m_id{};
		unsigned int m_size{};

	public:
		VertexBuffer()
		{
			glGenBuffers(1, &m_id);
		}

		VertexBuffer(const void* data, const unsigned int size) : m_size(size)
		{
			glGenBuffers(1, &m_id);
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		~VertexBuffer()
		{
			glDeleteBuffers(1, &m_id);
		}

		void set_data(const void* data, const unsigned int size) const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		[[nodiscard]] unsigned int get_id() const
		{
			return m_id;
		}

		void bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_id);
		}

		void unbind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	};

	export class IndexBuffer
	{
		unsigned int m_id{};
		GLsizeiptr m_size{};

	public:
		IndexBuffer() = default;

		IndexBuffer(const IndexBuffer&) = delete;
		IndexBuffer& operator=(const IndexBuffer&) = delete;

		~IndexBuffer()
		{
			if (m_id != 0)
			{
				glDeleteBuffers(1, &m_id);
			}
		}

		[[nodiscard]] unsigned int get_id() const
		{
			return m_id;
		}

		void set_data(const void* data, const GLsizeiptr size)
		{
			if (m_id == 0)
			{
				glGenBuffers(1, &m_id);
			}

			m_size = size;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
		}

		void bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
		}

		void unbind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	};
	;
} // namespace Lys::GL
