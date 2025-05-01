module;
#include <print>
#include <utils/macros.hpp>
export module lys.rendering;

#ifdef USE_VULKAN
import lys.vulkan.vk_renderer;
using Renderer = Lys::VkRenderer;
#else
import lys.opengl.gl_renderer;
using Renderer = Lys::GLRenderer;
#endif

namespace Lys
{
	export class Rendering
	{
		static Renderer* m_renderer;

	public:
		Rendering() = default;

		/**
		 * @brief Initializes Rendering pipeline and underlying Renderer.
		 */
		static void init()
		{
			m_renderer = new Renderer();
			m_renderer->init();

			std::println("Render class: {0}", CLASS_NAME(m_renderer));
		}

		static Renderer& get_renderer_singleton()
		{
			return *m_renderer;
		}

		static void update_viewport(int width, int height)
		{
			if (m_renderer)
			{
				m_renderer->update_viewport(width, height);
			}
		}
	};

	Renderer* Rendering::m_renderer = nullptr;
} // namespace Lys
