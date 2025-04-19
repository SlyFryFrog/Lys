#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

// import app;
// import file;

int main()
{
	// Lys::App app;

	// app._init();

	// app._process();

	// app._destroy();
	// Initializes GLEW
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW failed to initialize correctly.", glGetError();
	}
	return 0;
}
