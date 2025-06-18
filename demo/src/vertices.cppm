module;
#include <GL/glew.h>
#include <__ostream/print.h>
#include <array>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <memory>
export module vertices;

import lys.rendering.mesh;
import lys.opengl;


using namespace Lys;

float offSet = 0.0f;
static std::unique_ptr<Mesh> mesh;

std::shared_ptr<GL::ShaderProgram> shaderProgram;
std::unique_ptr<GL::VertexArray> vao;
std::unique_ptr<GL::VertexBuffer> vbo;
std::unique_ptr<GL::IndexBuffer> ebo;

export void init_mesh()
{
	const auto vertex = std::make_shared<GL::Shader>(VERTEX, "/shaders/vert_test.vert");
	const auto frag = std::make_shared<GL::Shader>(FRAGMENT, "/shaders/frag_test.frag");

	shaderProgram = std::make_shared<GL::ShaderProgram>(
		std::vector<std::shared_ptr<IShader>>{vertex, frag});
	shaderProgram->link();

	vao = std::make_unique<GL::VertexArray>();
	vbo = std::make_unique<GL::VertexBuffer>();
	ebo = std::make_unique<GL::IndexBuffer>();

	mesh = std::make_unique<Mesh>("/rsc/banjo_frog.obj");
}

export void draw_mesh(const double delta)
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -5.0f);	  // Back 5 units
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Looking at center
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);			  // "Up" is +Y

	glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, up);
	float aspectRatio = (float)1024 / (float)768;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

	offSet += static_cast<float>(delta) / 10.0f;
	shaderProgram->bind();
	{
		shaderProgram->set_uniform("uOffset", offSet);
		shaderProgram->set_uniform("uProjection", projection);
		shaderProgram->set_uniform("uView", view);
		shaderProgram->set_uniform("uModel", model);

		vao->bind();
		mesh->draw(*shaderProgram);
	}
	shaderProgram->unbind();
}
