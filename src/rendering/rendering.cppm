module;
#include <iostream>
#include <print>
export module lys.rendering;

import lys.utils;
import lys.opengl.gl_renderer;
import lys.vulkan.vk_renderer;


namespace Lys
{
	export class Rendering
	{
		static IRenderer* m_renderer;

	public:
		Rendering() = default;

		/**
		 * @brief Initializes Rendering pipeline and underlying Renderer.
		 */
		static void init()
		{
#ifdef USE_VULKAN
			m_renderer = new VkRenderer();
#else
			m_renderer = new GLRenderer();
#endif

			if (m_renderer == nullptr)
			{
				std::println(
					std::cerr,
					"Failed to initiate Renderer: Cannot initiate nullptr for render class: {}\n",
					class_name(m_renderer).get());
				return;
			}

			m_renderer->init();

			std::println("Render class: {}\n", class_name(m_renderer).get());
		}

		static IRenderer& get_renderer_singleton()
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

	IRenderer* Rendering::m_renderer = nullptr;
} // namespace Lys
