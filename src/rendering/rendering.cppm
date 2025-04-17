module;
export module rendering;

#if defined(USE_METAL)

#else
import opengl;
#endif

namespace Lys
{
	export class Rendering
	{
#if defined(USE_METAL)
using m_renderer = MetalRenderer;
#else
		using m_renderer = OpenGLRenderer;
#endif

	public:
	};
} // namespace Lys
