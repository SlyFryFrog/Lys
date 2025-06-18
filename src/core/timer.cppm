module;
#include <chrono>
export module lys.core.timer;

namespace Lys
{
	export class Timer
	{
		std::chrono::high_resolution_clock::time_point m_start;
		std::chrono::high_resolution_clock::time_point m_prev;
		double m_elapsed{};
		bool m_isRunning{};

	public:
		Timer()
		{
			reset();
		}

		~Timer() = default;

		void start()
		{
			m_start = std::chrono::high_resolution_clock::now();
			m_prev = m_start;
			m_isRunning = true;
		}

		void reset()
		{
			m_start = std::chrono::high_resolution_clock::now();
			m_prev = m_start;
			m_elapsed = 0.0;
			m_isRunning = false;
		}

		void stop()
		{
			if (m_isRunning)
			{
				m_prev = std::chrono::high_resolution_clock::now();
				m_elapsed = std::chrono::duration<double>(m_prev - m_start).count();
				m_isRunning = false;
			}
		}

		void update()
		{
			if (m_isRunning)
			{
				m_prev = std::chrono::high_resolution_clock::now();
				m_elapsed = std::chrono::duration<double>(m_prev - m_start).count();
			}
		}

		[[nodiscard]] double delta()
		{
			if (!m_isRunning)
			{
				return 0.0;
			}

			const auto now = std::chrono::high_resolution_clock::now();
			const double delta = std::chrono::duration<double>(now - m_prev).count();

			m_prev = now;

			return delta;
		}

		[[nodiscard]] double peek_delta() const
		{
			if (!m_isRunning)
			{
				return 0.0;
			}

			const auto now = std::chrono::high_resolution_clock::now();
			const double delta = std::chrono::duration<double>(now - m_prev).count();

			return delta;
		}

		[[nodiscard]] double elapsed()
		{
			if (!m_isRunning)
			{
				return 0.0;
			}

			const auto now = std::chrono::high_resolution_clock::now();
			const double elapsed = std::chrono::duration<double>(now - m_start).count();
			m_start = now;

			return elapsed;
		}

		[[nodiscard]] double peek_elapsed() const
		{
			if (!m_isRunning)
			{
				return 0.0;
			}

			const auto now = std::chrono::high_resolution_clock::now();
			const double elapsed = std::chrono::duration<double>(now - m_prev).count();

			return elapsed;
		}
	};
} // namespace Lys
