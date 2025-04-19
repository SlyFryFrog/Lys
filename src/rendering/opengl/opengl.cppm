module;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
export module opengl;

export import :shader;

import renderer;

namespace Lys
{
	export class OpenGLRenderer : public IRenderer
	{
	public:
		OpenGLRenderer() = default;
		~OpenGLRenderer() = default;
		
		void init() override
		{
			// Initializes GLEW
			if (glewInit() != GLEW_OK)
			{
				std::cout << "GLEW failed to initialize correctly.", glGetError();
			}
	
			glEnable(GL_DEPTH_TEST);

			std::cout << "Renderer: " << glGetString(GL_RENDERER);
			std::cout << "OpenGL version: ", glGetString(GL_VERSION);

			int numAttributes;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);
			std::cout << "Maximum number of vertex attributes supported: " << numAttributes;
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

		void resize(int width, int height) override
		{
		}

		void shutdown() override
		{
		}
	};
} // namespace Lys
