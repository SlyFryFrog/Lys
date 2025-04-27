module;
#include <string>
export module app;

import lys.platform.window;
import lys.rendering;

namespace Lys
{
	export class App
	{
		Window m_window;

	public:
		virtual void init()
		{
			m_window = Window(100, 100, "Lys Engine");
			m_window.init();
			Rendering::init();

			process();
		}

		virtual void destroy()
		{
		}

		virtual void process()
		{
			while (!m_window.is_done())
			{
			}
		}
	};
} // namespace Lys
