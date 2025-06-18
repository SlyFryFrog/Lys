// #include <jlcxx/jlcxx.hpp>
// #include <jlcxx/type_conversion.hpp>
// #include <julia.h>
// #include <vector>
#include <GL/glew.h>

import lys;
import lys.opengl;

import demo.player;
import vertices;

using namespace Lys;

class DemoApp final : public App
{
public:
	DemoApp() = default;

	void init() override
	{
		App::init();

		m_window.set_title("Lys Demo");

		m_window.set_windowed(1024, 768);
		// m_window.set_fullscreen();
		m_window.set_cursor_status(true);

		m_window.show();
	}

	void process() override
	{
		// JuliaEngine::load_script("/Users/marcus/dev/Lys/src/core/scripting/julia/bindings/lys.jl");
		// JuliaEngine::load_script("/Users/marcus/dev/Lys/demo/scripts/player.jl");

		// Node node;
		// auto boxed = jlcxx::box<Node>(node);
		// jl_value_t* n = boxed.value;

		// std::vector<jl_value_t*> args;
		// JuliaEngine::call_function("Player", "on_ready", &args);
		// args.push_back(jl_box_float64(3.9));
		// JuliaEngine::call_function("Player", "process", &args);
		// args.clear();
		// auto result = JuliaEngine::call_function("Player", "get_node_type", nullptr);
		PolygonMode mode = FILL;
		Timer deltaTimer;
		deltaTimer.start();
		init_mesh();
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		while (!m_window.is_done())
		{
			m_window.swap_buffers();
			Window::clear_buffer();
			Window::poll_events();

			double delta = deltaTimer.delta();

			draw_mesh(delta);

			if (InputManager::is_ordered_pressed({KEY_LEFT_SHIFT, KEY_ESCAPE}))
			{
				break;
			}
			if (InputManager::is_ordered_pressed({KEY_0}) && InputManager::is_just_pressed(KEY_0))
			{
				switch (mode)
				{
				case FILL:
					mode = LINE;
					Rendering::set_polygon_mode(mode);
					break;
				case LINE:
					mode = POINT;
					Rendering::set_polygon_mode(mode);
					break;
				default:
					mode = FILL;
					Rendering::set_polygon_mode(mode);
					break;
				}
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
	app.process();

	return 0;
}
