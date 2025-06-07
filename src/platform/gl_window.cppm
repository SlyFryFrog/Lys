module;
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
export module lys.platform.gl_window;

import lys.platform.platform_interfaces;
import lys.rendering;
import lys.platform.input.input_manager;

namespace Lys
{
	export class GLWindow final : public IWindow
	{
	public:
		explicit GLWindow(const std::string& title) : IWindow(title) {}

		explicit GLWindow(const bool fullscreen, const std::string& title) : IWindow(fullscreen, title) {}

		explicit GLWindow(const int width, const int height, const std::string& title) :
			IWindow(width, height, title)
		{
		}

		~GLWindow() override = default;

		void init() override
		{
			if (!glfwInit())
			{
				std::println(std::cerr, "Failed to initialize glfw.");
				return;
			}

			create_opengl_context(4, 1);
			set_glfw_hints();

			m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

			if (!m_window)
			{
				glfwTerminate();
				std::println(std::cerr , "Failed to create Window instance! Terminating GLFW.");
				return;
			}

			set_glfw_window_defaults(m_window);
		}

	private:
		/**
		 * @brief Sets the version of OpenGL to be used.
		 * 
		 * @code
		 * create_opengl_context(4, 1);
		 * @endcode
		 * 
		 * @param major Major version, all versions above 4 are supported.
		 * @param minor Minor version, all versions above 1 are supported.
		 */
		static void create_opengl_context(const int major, const int minor)
		{
			// Set OpenGL version (ie 4.6)
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		}

		/**
		 * @brief Set GLFW hints for OpenGL-specific functionality.
		 */
		static void set_glfw_hints()
		{
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

			// Required by macOS
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		}
	};
} // namespace Lys
