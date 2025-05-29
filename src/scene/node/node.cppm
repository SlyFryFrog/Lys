module;
#include <string>
export module lys.scene.node;

namespace Lys
{
	export class Node
	{
		std::string m_name;

	public:
		Node() = default;
		
		virtual void _init()
		{
		}

		virtual void _process(double delta)
		{
		}
		
        virtual void _destroy()
		{
		}
	
		void set_name(const std::string& name)
		{
			m_name = name;
		}

		std::string get_name() const
		{
			return m_name;
		}
	};
} // namespace Lys
