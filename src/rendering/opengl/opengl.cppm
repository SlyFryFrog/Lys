module;
export module opengl;

export import :shader;

import renderer;

namespace Lys
{
	export class OpenGLRenderer : public IRenderer
	{
	public:
		void init() override
		{
		}

		void begin_frame() override
		{
		}

		void draw() override
		{
		}

		void end_frame() override
		{
		}

		void resize(int width, int height) override
		{
		}

		void shutdown() override
		{
		}
	};
} // namespace Lys
