module;
#include <GLFW/glfw3.h>
#include <print>
#include <string>
#include <utility>
export module lys.platform.platform_interfaces;

import lys.rendering;
import lys.platform.input.input_manager;

namespace Lys
{
	export class IWindow
	{
	protected:
		GLFWwindow* m_window{};
		std::string m_title;
		int m_width{};
		int m_height{};
		bool m_fullscreen{};

	public:
		IWindow() = default;

		explicit IWindow(std::string title) : m_title(std::move(title))
		{
		}
		IWindow(const bool fullscreen, std::string  title) :
			m_title(std::move(title)), m_fullscreen(fullscreen)
		{
		}
		IWindow(const int width, const int height, std::string  title) :
			m_title(std::move(title)), m_width(width), m_height(height)
		{
		}

		virtual ~IWindow()
		{
			destroy();
		}

		virtual void init() = 0;

		void destroy()
		{
			if (m_window)
			{
				glfwDestroyWindow(m_window);
				m_window = nullptr;
			}
		}

		void swap_buffers() const
		{
			glfwSwapBuffers(m_window);
		}

		static void clear_buffer()
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		static void terminate()
		{
			glfwTerminate();
		}

		static void frame_buffer_callback(GLFWwindow* window, int width, int height)
		{
			Rendering::update_viewport(width, height);
		}

		static void poll_events()
		{
			glfwPollEvents();
		}

		void set_cursor_status(bool status) const
		{
			glfwSetInputMode(m_window, GLFW_CURSOR,
							 status ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
		}

		[[nodiscard]] GLFWwindow* get_native_window() const
		{
			return m_window;
		}

		[[nodiscard]] bool is_done() const
		{
			return glfwWindowShouldClose(m_window);
		}

		void set_done(const bool status) const
		{
			if (status)
			{
				glfwSetWindowShouldClose(m_window, GLFW_TRUE);
			}
			else
			{
				glfwSetWindowShouldClose(m_window, GLFW_FALSE);
			}
		}

		void set_title(const std::string& title)
		{
			m_title = title;
			glfwSetWindowTitle(m_window, title.c_str());
		}

		void resize(const int width, const int height)
		{
			if (width <= 0 || height <= 0 || !m_window)
			{
				return;
			}

			m_width = width;
			m_height = height;

			glfwSetWindowSize(m_window, width, height);
			glViewport(0, 0, width, height);
		}

		void set_fullscreen()
		{
			if (!m_fullscreen)
			{

				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				m_height = mode->height;
				m_width = mode->width;
				m_fullscreen = true;

				glfwDestroyWindow(m_window);

				glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
				m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), monitor, nullptr);

				set_glfw_window_defaults(m_window);
				glViewport(0, 0, m_width, m_height);
			}
		}

		void set_windowed(const int width, const int height)
		{
			m_fullscreen = false;
			m_width = width;
			m_height = height;

			glfwDestroyWindow(m_window);

			m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
			set_glfw_window_defaults(m_window);
		}

		void show() const
		{
			glfwShowWindow(m_window);
		}

		void hide() const
		{
			glfwHideWindow(m_window);
		}

		void set_glfw_window_defaults(GLFWwindow* window)
		{
			glfwMakeContextCurrent(window);
			glfwSetWindowUserPointer(window, this);
			glfwSetFramebufferSizeCallback(window, frame_buffer_callback);
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			glfwSetKeyCallback(window, InputManager::_process_input_callback);
			glfwSetCursorPosCallback(window, InputManager::_process_mouse_callback);

			glfwGetFramebufferSize(window, &m_width, &m_height);
			frame_buffer_callback(window, m_width, m_height);
		}
	};
} // namespace Lys
