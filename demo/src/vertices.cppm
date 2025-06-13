module;
#include <GL/glew.h>
#include <array>
#include <memory>
export module vertices;

import lys.opengl;

using namespace Lys;

float vertices[] = {
	// Pos, rgb, text coord
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // top right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // bottom right
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f  // top left
};

float offSet = 0.0f;

unsigned int indices[] = {
	0, 1, 3, // first Triangle
	1, 2, 3	 // second Triangle
};

export void draw_square(double delta)
{
	offSet += delta;

	// Load shaders
	const auto vertex = std::make_shared<GL::Shader>(Vertex, "/shaders/vert_test.vert");
	const auto frag = std::make_shared<GL::Shader>(Fragment, "/shaders/frag_test.frag");
	GL::ShaderProgram shaderProgram({vertex, frag});
	shaderProgram.link();

	// Setup geometry
	const GL::VertexArray vao;
	const GL::VertexBuffer vbo;
	const GL::IndexBuffer ebo;

	vao.bind();
	vbo.bind(vertices, sizeof(vertices));
	GL::VertexLayout layout;
	layout.add_attributes({
		{0, 3, GL::FLOAT, false},
		{1, 3, GL::FLOAT, false},
	});
	layout.enable_attributes();
	vao.unbind();

	// Use shader and draw
	shaderProgram.bind();
	{
		shaderProgram.set_uniform("uOffset", offSet);
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 18);
		vao.unbind();
	}
	shaderProgram.unbind();
}
