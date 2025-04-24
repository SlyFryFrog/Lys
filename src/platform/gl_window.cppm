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

		explicit GLWindow(const int width, const int height, const std::string& title) : IWindow(width, height, title) {}

		~GLWindow()
		{
			cleanup();
		}

		void cleanup() override
		{
			glfwDestroyWindow(IWindow::m_window);
			glfwTerminate();
		}

		void init() override
		{
			if (!glfwInit())
			{
				std::cerr << "Failed to initialize glfw." << "\n";
			}

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

			if (!glfwVulkanSupported())
			{
				throw std::runtime_error("GLFW: Vulkan not supported on this system!");
			}

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

    private:
        static void create_opengl_context(int major, int minor, bool coreProfile=true)
        {
            // Set OpenGL version (ie 4.6)
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

            if (coreProfile)
            {
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            }
        }
    };
}