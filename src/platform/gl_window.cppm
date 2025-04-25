module;
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
export module window:gl_window;

import window_interface;
import rendering;

namespace Lys
{
	export class GLWindow : public IWindow
	{
	public:
		GLWindow() = default;

		explicit GLWindow(const int width, const int height, const std::string& title) :
			IWindow(width, height, title)
		{
		}

		~GLWindow()
		{
		}

		void init() override
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize glfw." << "\n";
				return;
			}

			create_opengl_context(4, 1);
			set_glfw_hints();

			m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

			if (!m_window)
			{
				glfwTerminate();
				std::cout << "Failed to create Window instance! Terminating GLFW." << "\n";
				return;
			}

			// Makes the current window context
			glfwMakeContextCurrent(m_window);

			// Associates window user pointer with current instance
			glfwSetWindowUserPointer(m_window, this);
			glfwSetFramebufferSizeCallback(m_window, frame_buffer_callback);
			// glfwSetKeyCallback(_window, InputManager::_process_input_callback);
			// glfwSetCursorPosCallback(_window, InputManager::_process_mouse_callback);
			glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_FALSE);
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			frame_buffer_callback(m_window, m_width, m_height);
		}

	private:
		static void create_opengl_context(int major, int minor)
		{
			// Set OpenGL version (ie 4.6)
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		}

		/**
		 * @brief Set GLFW hints for OpenGL-specific functionality.
		 *
		 * @param coreProfile Either enable or disable the use of GLFW_OPENGL_CORE_PROFILE.
		 */
		static void set_glfw_hints(bool coreProfile = true)
		{
			if (coreProfile)
			{
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			}
			else
			{
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
			}

			// Required by macOS
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		}
	};
} // namespace Lys
