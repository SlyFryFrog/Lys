module;
export module rendering;

#if defined(USE_METAL)
using Renderer = Lys::MetalRenderer;
#else
import opengl;
using Renderer = Lys::OpenGLRenderer;
#endif

namespace Lys
{
	export class Rendering
	{
		static Renderer m_renderer;

	public:
		Rendering() = default;

		static void _init()
		{
            m_renderer.init();
		}

		static Renderer get_renderer_singleton()
		{
			return m_renderer;
		}

		static void update_viewport(int width, int height)
		{
		}
	};

	Renderer Rendering::m_renderer = Renderer();
} // namespace Lys
