module;
//#include <jlcxx/jlcxx.hpp>
#include <julia.h>
export module lys.core.scripting.julia.julia_node_bindings;

// import lys.scene.node;

// namespace Lys
// {
// 	class JuliaNode : public Node
// 	{
// 	public:
// 		jl_function_t* jl_init = nullptr;
// 		jl_function_t* jl_process = nullptr;
// 		jl_function_t* jl_destroy = nullptr;

// 		void _init() override
// 		{
// 			if (jl_init)
// 			{
// 				jl_call0(jl_init);
// 			}
// 		}

// 		void _process(double delta) override
// 		{
// 			if (jl_process)
// 			{
// 				jl_call1(jl_process, jl_box_float64(delta));
// 			}
// 		}

// 		void _destroy() override
// 		{
// 			if (jl_destroy)
// 			{
// 				jl_call0(jl_destroy);
// 			}
// 		}

// 		void set_callbacks(jl_function_t* init, jl_function_t* process, jl_function_t* destroy)
// 		{
// 			jl_init = init;
// 			jl_process = process;
// 			jl_destroy = destroy;
// 		}
// 	};

// 	JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
// 	{

// 		mod.add_type<Node>("Node")
// 			.method("_init", &Node::_init)
// 			.method("_process", &Node::_process)
// 			.method("_destroy", &Node::_destroy);

// 		mod.add_type<JuliaNode>("JuliaNode")
// 			.constructor<>()
// 			.method("set_callbacks", &JuliaNode::set_callbacks);
// 	}
// } // namespace Lys
