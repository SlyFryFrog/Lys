module;
export module lys.core.timer;

#warning Lys::Timer is unimplemented.

namespace Lys
{
	export class Timer
	{
	public:
		Timer();
		~Timer();

		void start();
		void stop();
		void update();
	};
} // namespace Lys
