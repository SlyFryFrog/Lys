module;
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
export module app;

import rendering;
import window;

namespace Lys
{
	export class App
	{
		Window m_window;

	public:
		virtual void init()
		{
			// Init GLFW
			if (!glfwInit())
			{
				std::cerr << "Failed to initialize GLFW\n";
				return;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

			// Create window
			GLFWwindow* window = glfwCreateWindow(1280, 720, "Lys Engine", nullptr, nullptr);
			if (!window)
			{
				std::cerr << "Failed to create GLFW window\n";
				glfwTerminate();
				return;
			}

			glfwMakeContextCurrent(window);

			// Init GLEW
			glewExperimental = GL_TRUE;
			if (glewInit() != GLEW_OK)
			{
				std::cerr << "Failed to initialize GLEW\n";
				glfwDestroyWindow(window);
				glfwTerminate();
				return;
			}

			// Main loop
			while (!glfwWindowShouldClose(window))
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// TODO: Render stuff here

				glfwSwapBuffers(window);
				glfwPollEvents();
			}

			// Cleanup
			glfwDestroyWindow(window);
			glfwTerminate();
		}

		virtual void destroy()
		{
		}

		virtual void process()
		{
		}
	};
} // namespace Lys
