module;
#include <GL/glew.h>
#include <print>
export module lys.opengl.gl_renderer;

export import lys.rendering.renderer;
import lys.opengl.gl_shader;

namespace Lys::GL
{
	export class Renderer final : public IRenderer
	{
	public:
		Renderer() = default;
		~Renderer() override = default;

		void init() override
		{
			glewExperimental = GL_TRUE;

			if (const GLenum err = glewInit(); err != GLEW_OK)
			{
				std::println("GLEW failed to initialize correctly: {0}",
							 reinterpret_cast<const char*>(glewGetErrorString(err)));
			}

			glEnable(GL_DEPTH_TEST);

			std::println("Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
			std::println("OpenGL version: {0}",
						 reinterpret_cast<const char*>(glGetString(GL_VERSION)));

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

		void update_viewport(const int width, const int height) override
		{
			glViewport(0, 0, width, height);
		}

		void shutdown() override
		{
		}

		void set_polygon_mode(const PolygonMode mode) override
		{
			if (mode == FILL)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else if (mode == POINT)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			}
			else if (mode == LINE)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
		}
	};
} // namespace Lys
