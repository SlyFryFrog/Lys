module;
#include <array>
#include <memory>
#include <GL/glew.h>
export module vertices;

import lys.opengl;

using namespace Lys;


export std::array<std::array<float, 3>, 18> cube_vertices = {

};

export std::array<std::array<float, 3>, 6> square_vertices = {{{0.0f, 0.0f, 0.0f},
															   {0.0f, 1.0f, 0.0f},
															   {0.0f, 1.0f, 1.0f},
															   {1.0f, 0.0f, 0.0f},
															   {1.0f, 1.0f, 0.0f},
															   {1.0f, 1.0f, 1.0f}}};

float vertices[] = {
	0.5f,  0.5f, 0.0f,  // top right
	0.5f, -0.5f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f,  // bottom left
   -0.5f,  0.5f, 0.0f   // top left
};

unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
};


export void draw_square()
{
	// Load shaders
	auto vertex = std::make_shared<GLShader>(Vertex, "shaders/vert_test.vert");
	auto frag = std::make_shared<GLShader>(Fragment, "shaders/frag_test.frag");
	GLShaderProgram shaderProgram({vertex, frag});
	shaderProgram.link();

	// Setup geometry
	GLuint VAO{}, VBO{};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Use shader and draw
	shaderProgram.bind();
	{
		shaderProgram.set_uniform("uDelta", 1.0f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	shaderProgram.unbind();
}
