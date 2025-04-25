module;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <print>
export module opengl;

export import :shader;

import renderer;

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
				std::println("GLEW failed to initialize correctly: ",
							 (const char*)glewGetErrorString(err));
			}

			glEnable(GL_DEPTH_TEST);

			std::println("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
			std::println("OpenGL version: {0}", (const char*)glGetString(GL_VERSION));

			int numAttributes;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numAttributes);
			std::println("Maximum number of vertex attributes supported: {0}", numAttributes);
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
