module;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
export module lys.opengl.gl_renderer;

import renderer;
import lys.opengl.gl_shader;

namespace Lys
{
	export class GLRenderer : public IRenderer
	{
	public:
		GLRenderer() = default;
		~GLRenderer() = default;

		void init() override
		{
			glewExperimental = GL_TRUE;
			GLenum err = glewInit();

			if (err != GLEW_OK)
			{
				std::cout << "GLEW failed to initialize correctly: " << 
							 (const char*)glewGetErrorString(err) << "\n";
			}

			glEnable(GL_DEPTH_TEST);

			std::cout << "Renderer: " << (const char*)glGetString(GL_RENDERER) << "\n";
			std::cout << "OpenGL version: " << (const char*)glGetString(GL_VERSION) << "\n";

			int numAttributes;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);
			std::cout << "Maximum number of vertex attributes supported: " << numAttributes << "\n";
		}

		void begin_frame() override
		{
		}

		void draw() override
		{
		}

		void end_frame() override
		{
		}

		void update_viewport(int width, int height) override
		{
			glViewport(0, 0, width, height);
		}

		void shutdown() override
		{
		}
	};
} // namespace Lys
