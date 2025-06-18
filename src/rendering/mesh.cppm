module;
#include <GL/glew.h>
#include <filesystem>
#include <fstream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <print>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
export module lys.rendering.mesh;

import lys.rendering.shader;
import lys.opengl.gl_vertex_array;
import lys.utils;

namespace Lys
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;

		bool operator==(const Vertex& other) const
		{
			return Position == other.Position && Normal == other.Normal &&
				TexCoords == other.TexCoords;
		}
	};

	/**
	 * Special hash to enable use of hash-defined data structures with the Vertex struct.
	 * Calculates a special hash for each characteristic defined in the Vertex.
	 * Combines the hashes into a single hash that then gets returned.
	 */
	struct VertexHasher
	{
		size_t operator()(const Lys::Vertex& v) const noexcept
		{
			using namespace std;

			size_t h1 = hash<float>()(v.Position.x) ^ (hash<float>()(v.Position.y) << 1) ^
				(hash<float>()(v.Position.z) << 2);
			size_t h2 = hash<float>()(v.Normal.x) ^ (hash<float>()(v.Normal.y) << 1) ^
				(hash<float>()(v.Normal.z) << 2);
			size_t h3 = hash<float>()(v.TexCoords.x) ^ (hash<float>()(v.TexCoords.y) << 1);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
	};

	export class Mesh
	{
		std::vector<Vertex> m_vertices;
		std::vector<uint32_t> m_indices;
		std::vector<Texture> m_textures;
		std::unique_ptr<GL::VertexArray> m_vao;
		std::unique_ptr<GL::VertexBuffer> m_vbo;
		std::unique_ptr<GL::IndexBuffer> m_ebo;
		GL::VertexLayout m_layout;

	public:
		Mesh()
		{
			init_buffers();
		}

		~Mesh() = default;

		/**
		 *
		 * @param path Relative path to mesh file. Prefixes the working directory of the executable
		 * to the path internally.
		 */
		explicit Mesh(const std::string& path)
		{
			init_buffers();
			load(path);
		}

		/**
		 *
		 * @param path Relative path to mesh file. Prefixes the working directory of the executable
		 * to the path internally.
		 */
		void load(const std::string& path)
		{
			const std::string absPath = WorkingDirectory + path;
			std::ifstream file(absPath);
			if (!file.is_open())
			{
				return;
			}

			std::vector<glm::vec3> positions;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec2> texcoords;
			std::unordered_map<Vertex, uint32_t, VertexHasher> uniqueVertices;

			std::string line;
			while (std::getline(file, line))
			{
				// Extract prefix from current line
				std::istringstream iss(line);
				std::string prefix;
				iss >> prefix;

				if (prefix == "v")
				{
					glm::vec3 pos;
					iss >> pos.x >> pos.y >> pos.z;
					positions.push_back(pos);
				}
				else if (prefix == "vn")
				{
					glm::vec3 norm;
					iss >> norm.x >> norm.y >> norm.z;
					normals.push_back(norm);
				}
				else if (prefix == "vt")
				{
					glm::vec2 uv;
					iss >> uv.x >> uv.y;
					texcoords.push_back(uv);
				}
				else if (prefix == "mtllib")
				{
					std::string resourcePath;
					iss >> resourcePath;

					std::string mtlPath = std::filesystem::path(absPath).parent_path().string() + "/" +
						resourcePath;

					load_mtl(mtlPath); // TODO Add implementation that creates texture ids for
									   // renderer.
				}
				else if (prefix == "f")
				{
					std::vector<std::string> faceVertices;
					std::string vertexStr;

					// Iterate for each vertex defined in line
					while (iss >> vertexStr)
					{
						faceVertices.push_back(vertexStr);
					}

					// Fan triangulate (v0, v1, v2), (v0, v2, v3), etc
					for (size_t i = 1; i + 1 < faceVertices.size(); ++i)
					{
						const std::string& v0 = faceVertices[0];
						const std::string& v1 = faceVertices[i];
						const std::string& v2 = faceVertices[i + 1];

						for (const std::string& v : {v0, v1, v2})
						{
							std::istringstream vss(v);
							std::string posIdxStr, texIdxStr, normIdxStr;

							// Extract segments between the delimiters
							std::getline(vss, posIdxStr, '/');
							std::getline(vss, texIdxStr, '/');
							std::getline(vss, normIdxStr, '/');

							// Convert index to 0-based starting rather than 1-based
							int posIdx = std::stoi(posIdxStr) - 1;

							// Tries to get tex and norm indices if available - default to 0 to
							// avoid crashing
							int texIdx = !texIdxStr.empty() ? std::stoi(texIdxStr) - 1 : 0;
							int normIdx = !normIdxStr.empty() ? std::stoi(normIdxStr) - 1 : 0;

							Vertex vertex{};
							vertex.Position = positions[posIdx];
							vertex.TexCoords = texcoords.size() > texIdx ? texcoords[texIdx]
																		 : glm::vec2(0.0f);
							vertex.Normal = normals.size() > normIdx ? normals[normIdx]
																	 : glm::vec3(0.0f);

							// Only add unique vertices to the arraylist
							if (!uniqueVertices.contains(vertex))
							{
								uniqueVertices[vertex] = static_cast<uint32_t>(m_vertices.size());
								m_vertices.push_back(vertex);
							}

							m_indices.push_back(uniqueVertices[vertex]);
						}
					}
				}
			}


			m_layout.add_attributes(
				{{0, 3, GL::FLOAT, false}, {1, 3, GL::FLOAT, false}, {2, 2, GL::FLOAT, false}});

			// Perform binding operations to add mesh instance to gpu for rendering
			m_vao->bind();
			m_vbo->set_data(m_vertices.data(), sizeof(Vertex) * m_vertices.size());
			m_layout.enable_attributes();
			m_ebo->set_data(m_indices.data(), sizeof(uint32_t) * m_indices.size());
			m_ebo->unbind();
			m_vao->unbind();
		}

		void draw(const IShaderProgram& program)
		{
			program.bind();
			m_vao->bind();
			m_ebo->bind();
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
			m_vao->unbind();
			program.unbind();
		}

		[[nodiscard]] std::vector<Vertex> get_vertices() const
		{
			return m_vertices;
		}

		[[nodiscard]] std::vector<uint32_t> get_indices() const
		{
			return m_indices;
		}

	private:
		void init_buffers()
		{
			m_vao = std::make_unique<GL::VertexArray>();
			m_vbo = std::make_unique<GL::VertexBuffer>();
			m_ebo = std::make_unique<GL::IndexBuffer>();
		}

		/**
		 *
		 * @param path Absolute path to the mtl file.
		 */
		void load_mtl(const std::string& path)
		{
		}
	};
} // namespace Lys
