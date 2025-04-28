#include <string>

import lys;


using namespace Lys;

class DemoApp : public App
{
public:
	DemoApp() = default;

	void process() override
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


int main()
{
	DemoApp app;
	
	app.init();
	app.destroy();

    return 0;
}
