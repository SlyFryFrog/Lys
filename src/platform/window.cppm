module;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
export module window;

import rendering;

namespace Lys
{
	export class Window
	{
		GLFWwindow* m_window{};
		int m_width{};
		int m_height{};
		std::string m_title{};

	public:
		Window() = default;

		Window(const int width, const int height) : m_width(width), m_height(height)
		{
		}

		Window(const int width, const int height, const std::string& title) :
			m_width(width), m_height(height), m_title(title)
		{
		}

		explicit Window(const std::string& title) : m_title(title)
		{
		}

		~Window()
		{
		}

		static void init_glfw()
		{
			glfwInit();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		}

		static void frame_buffer_callback(GLFWwindow* window, const int width, const int height)
		{
			Rendering::update_viewport(width, height);
		}

		void set_title(const std::string& title)
		{
			m_title = title;
		}

		void init()
		{
			init_glfw();

			m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

			if (!m_window)
			{
				glfwTerminate();
				std::cerr << "Failed to create Window instance! Terminating GLFW.";
				return;
			}

			// Makes the current window context
			glfwMakeContextCurrent(m_window);

			// // Associates window user pointer with current instance
			// glfwSetWindowUserPointer(m_window, this);
			// glfwSetFramebufferSizeCallback(m_window, frame_buffer_callback);
			// // glfwSetKeyCallback(_window, InputManager::_process_input_callback);
			// // glfwSetCursorPosCallback(_window, InputManager::_process_mouse_callback);
			// glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_FALSE);
			// glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			// frame_buffer_callback(m_window, m_width, m_height);
		}

		[[nodiscard]] GLFWwindow* get_native_window() const
		{
			return m_window;
		}

		[[nodiscard]] bool is_done() const
		{
			return glfwWindowShouldClose(m_window);
		}
	};
} // namespace Lys
