module;

#include <GL/glew.h>
#include <array>
#include <memory>
export module vertices;

import lys.opengl;

using namespace Lys;

float vertices[] = {
	// Pos, rgb
	0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // top right
	0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
	-0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f  // top left
};

unsigned int indices[] = {0, 1, 3, 1, 2, 3};

float offSet = 0.0f;

std::shared_ptr<GL::ShaderProgram> shaderProgram;
std::unique_ptr<GL::VertexArray> vao;
std::unique_ptr<GL::VertexBuffer> vbo;
std::unique_ptr<GL::IndexBuffer> ebo;

export void init_square_resources()
{
	const auto vertex = std::make_shared<GL::Shader>(Vertex, "/shaders/vert_test.vert");
	const auto frag = std::make_shared<GL::Shader>(Fragment, "/shaders/frag_test.frag");

	shaderProgram = std::make_shared<GL::ShaderProgram>(
		std::vector<std::shared_ptr<IShader>>{vertex, frag});
	shaderProgram->link();

	vao = std::make_unique<GL::VertexArray>();
	vbo = std::make_unique<GL::VertexBuffer>();
	ebo = std::make_unique<GL::IndexBuffer>();

	vao->bind();
	vbo->bind(vertices, sizeof(vertices));
	// ebo.bind(indices, sizeof(indices));

	GL::VertexLayout layout;
	layout.add_attributes({
		{0, 3, GL::FLOAT, false},
		{1, 3, GL::FLOAT, false},
	});
	layout.enable_attributes();
	vao->unbind();
}

export void draw_square(const double delta)
{
	offSet += static_cast<float>(delta);
	shaderProgram->bind();
	{
		shaderProgram->set_uniform("uOffset", offSet);
		vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 18);
		vao->unbind();
	}
	shaderProgram->unbind();
}
