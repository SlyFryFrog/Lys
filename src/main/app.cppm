module;
#include <string>
export module lys.main.app;

import lys.platform.input.input_manager;
import lys.platform.window;
import lys.rendering;

namespace Lys
{
	export class App
	{
	protected:
		Window m_window;

	public:
		virtual void init()
		{
			m_window = Window(100, 100, "Lys Engine");
			m_window.init();
			Rendering::init();
		}

		virtual void destroy()
		{
			m_window.terminate();			
		}

		virtual void process()
		{
			while (!m_window.is_done())
			{
				m_window.swap_buffers();
				Window::poll_events();

				if (InputManager::is_ordered_combo_hold({Key::KEY_ESCAPE, Key::KEY_SHIFT}))
				{
					break;
				}

				InputManager::_process();
			}

			m_window.destroy();
			Window::terminate();
		}
	};
} // namespace Lys
