module;
#include <iostream>
#include <utils/macros.hpp>
export module rendering;

#ifdef USE_VULKAN
import vulkan;
using Renderer = Lys::VkRenderer;
#else
import opengl;
using Renderer = Lys::GLRenderer;
#endif

namespace Lys
{
	export class Rendering
	{
		static Renderer* m_renderer;

	public:
		Rendering() = default;

		static void init()
		{
			m_renderer = new Renderer();
			m_renderer->init();

			std::cout << CLASS_NAME(m_renderer)  << "\n";
		}

		static Renderer& get_renderer_singleton()
		{
			return *m_renderer;
		}

		static void update_viewport(int width, int height)
		{
		}
	};

	Renderer* Rendering::m_renderer = nullptr;
} // namespace Lys
