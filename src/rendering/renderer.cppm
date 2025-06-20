module;
export module lys.rendering.renderer;

namespace Lys
{
	export enum PolygonMode { FILL, LINE, POINT };

	export class IRenderer
	{
	public:
		virtual ~IRenderer() = default;

		virtual void init() = 0;
		virtual void begin_frame() = 0;
		virtual void draw() = 0;
		virtual void end_frame() = 0;
		virtual void update_viewport(int width, int height) = 0;
		virtual void shutdown() = 0;

		virtual void set_polygon_mode(PolygonMode mode) = 0;
	};
} // namespace Lys
