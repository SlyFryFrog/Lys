#include <iostream>

import app;
import file;

int main()
{
	Lys::App app;

	app._init();

	app._process();

	app._destroy();

	Lys::File file("README.md");
	std::cout << file.read();

	return 0;
}
