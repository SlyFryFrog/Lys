module;
#include <string>
export module lys.main.app;

import lys.platform.input.input_manager;
import lys.platform.window;
import lys.rendering;
// import lys.core.scripting.julia.julia_engine;

namespace Lys
{
	export class App
	{
	protected:
		Window m_window;

	public:
		explicit App() : m_window(400, 400, "Project")
		{}

		virtual ~App()
		{
			m_window.terminate();
			// JuliaEngine::shutdown();
		}

		virtual void init()
		{
			m_window.init();
			Rendering::init();

			// JuliaEngine::init();
		}

		virtual void process()
		{
			while (!m_window.is_done())
			{
				m_window.swap_buffers();
				Window::clear_buffer();
				Window::poll_events();
				
				InputManager::_process();
			}
		}
	};
} // namespace Lys
