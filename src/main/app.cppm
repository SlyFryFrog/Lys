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
        virtual void _init()
        {
            // Initializes GLEW
			if (glewInit() != GLEW_OK)
			{
				std::cout << "GLEW failed to initialize correctly.", glGetError();
			}
            // Rendering::_init();
            // Window::init_glfw();
            // m_window.init();
        }

        virtual void _destroy()
        {

        }

        virtual void _process()
        {

        }
    };
}