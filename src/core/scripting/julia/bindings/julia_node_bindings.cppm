module;
#include <jlcxx/jlcxx.hpp>
#include <julia.h>
export module lys.core.scripting.julia.julia_node_bindings;

import lys.scene.node;

namespace Lys
{
	JLCXX_MODULE define_lys_module(jlcxx::Module& mod)
	{
		mod.add_type<Node>("Node")
			.method("init", &Node::_init)
			.method("process", &Node::_process)
			.method("destroy", &Node::_destroy)
			.method("get_name", &Node::get_name)
			.method("set_name", &Node::set_name)
			.constructor<>();
	}
} // namespace Lys
