module;
#include <GLFW/glfw3.h>
#include <string>
export module window_interface;

import rendering;

namespace Lys
{
	export class IWindow
	{
	protected:
		GLFWwindow* m_window{};
		std::string m_title;
		int m_width{};
		int m_height{};

	public:
		IWindow() = default;

		explicit IWindow(const int width, const int height, const std::string& title) :
			m_width(width), m_height(height), m_title(title)
		{
		}

		~IWindow()
		{
			cleanup();
		}

		virtual void init() = 0;

		/**
		 * @brief Destroys the Window instance.
		 *
		 */
		void cleanup()
		{
			glfwDestroyWindow(m_window);
		}

		static void terminate()
		{
			glfwTerminate();
		}

		static void frame_buffer_callback(GLFWwindow* window, const int width, const int height)
		{
			Rendering::update_viewport(width, height);
		}

		static void poll_events()
		{
			glfwPollEvents();
		}

		void set_cursor_status(bool status)
		{
			if (status)
			{
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else
			{
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
		}

		[[nodiscard]] GLFWwindow* get_native_window() const
		{
			return m_window;
		}

		[[nodiscard]] bool is_done() const
		{
			return glfwWindowShouldClose(m_window);
		}

		void set_title(const std::string& title)
		{
			m_title = title;
		}
	};
} // namespace Lys
