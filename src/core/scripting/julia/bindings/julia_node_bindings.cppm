module;
// #include <jlcxx/jlcxx.hpp>
// #include <jlcxx/type_conversion.hpp>
// #include <julia.h>
export module lys.core.scripting.julia.julia_node_bindings;

// import lys.scene.node;
// import lys.scene.node_2d;
// import lys.scene.node_3d;

// import lys.platform.input.input_event;
// import lys.platform.input.input_manager;
// import lys.platform.input.input_map;

// // Namespace for declaring upscaling
// export namespace jlcxx
// {
// 	template <>
// 	struct SuperType<Lys::Node3D>
// 	{
// 		typedef Lys::Node type;
// 	};

// 	template <>
// 	struct SuperType<Lys::Node2D>
// 	{
// 		typedef Lys::Node type;
// 	};
// } // namespace jlcxx


// Namespace for specifying Julia conversions of functions and classes
namespace Lys
{
// 	JLCXX_MODULE define_lys_module(::jlcxx::Module& mod)
// 	{
// 		mod.add_type<Node>("Node")
// 			.method("_init", &Lys::Node::_init)
// 			.method("_process", &Lys::Node::_process)
// 			.method("_destroy", &Lys::Node::_destroy)
// 			.method("get_name", &Node::get_name)
// 			.method("set_name", &Node::set_name)
// 			.constructor<>();

// 		mod.add_type<Node2D>("Node2D", jlcxx::julia_base_type<Node>()).constructor<>();

// 		mod.add_type<Node3D>("Node3D", jlcxx::julia_base_type<Node>()).constructor<>();

// 		// Input event bindings
// 		mod.add_bits<InputState>("InputState", jlcxx::julia_type("CppEnum"));
// 		mod.set_const("PRESSED", PRESSED);
// 		mod.set_const("JUST_PRESSED", JUST_PRESSED);
// 		mod.set_const("RELEASED", RELEASED);
// 		mod.set_const("JUST_RELEASED", JUST_RELEASED);

// 		mod.add_bits<Key>("Key", jlcxx::julia_type("CppEnum"));
// 		mod.set_const("KEY_0", KEY_0);
// 		mod.set_const("KEY_1", KEY_1);
// 		mod.set_const("KEY_2", KEY_2);
// 		mod.set_const("KEY_3", KEY_3);
// 		mod.set_const("KEY_4", KEY_4);
// 		mod.set_const("KEY_5", KEY_5);
// 		mod.set_const("KEY_6", KEY_6);
// 		mod.set_const("KEY_7", KEY_7);
// 		mod.set_const("KEY_8", KEY_8);
// 		mod.set_const("KEY_9", KEY_9);

// 		mod.set_const("KEY_A", KEY_A);
// 		mod.set_const("KEY_B", KEY_B);
// 		mod.set_const("KEY_C", KEY_C);
// 		mod.set_const("KEY_D", KEY_D);
// 		mod.set_const("KEY_E", KEY_E);
// 		mod.set_const("KEY_F", KEY_F);
// 		mod.set_const("KEY_G", KEY_G);
// 		mod.set_const("KEY_H", KEY_H);
// 		mod.set_const("KEY_I", KEY_I);
// 		mod.set_const("KEY_J", KEY_J);
// 		mod.set_const("KEY_K", KEY_K);
// 		mod.set_const("KEY_L", KEY_L);
// 		mod.set_const("KEY_M", KEY_M);
// 		mod.set_const("KEY_N", KEY_N);
// 		mod.set_const("KEY_O", KEY_O);
// 		mod.set_const("KEY_P", KEY_P);
// 		mod.set_const("KEY_Q", KEY_Q);
// 		mod.set_const("KEY_R", KEY_R);
// 		mod.set_const("KEY_S", KEY_S);
// 		mod.set_const("KEY_T", KEY_T);
// 		mod.set_const("KEY_U", KEY_U);
// 		mod.set_const("KEY_V", KEY_V);
// 		mod.set_const("KEY_W", KEY_W);
// 		mod.set_const("KEY_X", KEY_X);
// 		mod.set_const("KEY_Y", KEY_Y);
// 		mod.set_const("KEY_Z", KEY_Z);
// 		mod.set_const("KEY_ESCAPE", KEY_ESCAPE);
// 		mod.set_const("KEY_SPACE", KEY_SPACE);
// 		mod.set_const("KEY_SHIFT", KEY_SHIFT);
// 		mod.set_const("KEY_ALT", KEY_ALT);

// 		mod.add_type<InputEvent>("InputEvent")
// 			.method("is_pressed", &InputEvent::is_pressed)
// 			.method("is_just_pressed", &InputEvent::is_just_pressed)
// 			.method("is_just_released", &InputEvent::is_just_released)
// 			.method("get_state", &InputEvent::get_state)
// 			.method("set_state", &InputEvent::set_state)
// 			.method("get_key", &InputEvent::get_key)
// 			.method(&InputEvent::operator==)
// 			.constructor<>();
// 	}
} // namespace Lys
