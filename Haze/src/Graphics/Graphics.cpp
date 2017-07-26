#include "Graphics.hpp"

bool Graphics::init = false;

void Graphics::initialize(Window* window)
{
	if (init || !Window::loaded() || window == nullptr)
		return;

	window->setContext();

	if (!gladLoadGL())
		err(-1, "GLAD init error");

	std::cout << "OpenGL version major: " << GLVersion.major << " minor:" << GLVersion.minor;

	init = true;
}

void Graphics::terminate()
{
	if (!init)
		return;

	if (Window::loaded())
		Window::terminate();

	init = false;
}
