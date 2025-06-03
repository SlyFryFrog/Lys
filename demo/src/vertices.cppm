module;
#include <GL/glew.h>
#include <array>
export module vertices;

import lys.opengl;

using namespace Lys;


export std::array<float, 2> cube_vertices = {

};

export std::array<std::array<float, 3>, 6> square_vertices = {{{0.0f, 0.0f, 0.0f},
															   {0.0f, 1.0f, 0.0f},
															   {0.0f, 1.0f, 1.0f},
															   {1.0f, 0.0f, 0.0f},
															   {1.0f, 1.0f, 0.0f},
															   {1.0f, 1.0f, 1.0f}}};

export void draw_square()
{
	const Shaders shader("/Users/marcus/dev/Lys/demo/shaders/vert_test.vert",
				   "/Users/marcus/dev/Lys/demo/shaders/frag_test.frag");
	const GLShader glShader(shader);

	glShader.bind();
	{
		glShader.set_uniform_float("uDelta", 1.0f);

	}
	glShader.unbind();
}
