// #include <jlcxx/jlcxx.hpp>
// #include <jlcxx/type_conversion.hpp>
// #include <julia.h>
// #include <vector>

import lys;
import demo.player;

import vertices;

using namespace Lys;

class DemoApp final : public App
{
public:
	DemoApp() = default;

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

		draw_square();

		while (!m_window.is_done())
		{
			m_window.swap_buffers();
			Window::poll_events();

			if (InputManager::is_ordered_combo_hold({Key::KEY_ESCAPE, Key::KEY_SHIFT}))
			{
				break;
			}

			if (InputManager::is_just_pressed(Key::KEY_ESCAPE))
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
	app.process();

	return 0;
}
