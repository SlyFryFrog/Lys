module;
export module lys.scene.node;

namespace Lys
{
	export class Node
	{
	public:
		virtual void _init()
		{
		}

		virtual void _process(double delta)
		{
		}
		
        virtual void _destroy()
		{
		}
	};
} // namespace Lys
