#include "Graphics.hpp"

bool Graphics::init = false;
bool Graphics::initGL = false;

void Graphics::initialize()
{
	if (init)
		return;

	if (!glfwInit())
		err(-1, "GLFW init error");

	glfwSetErrorCallback(err);

	glfwConfig();

	init = true;
}

void Graphics::loadGL()
{
	if (!init || initGL)
		return;

	if (!gladLoadGL())
		err(-1, "GLAD init error");

	std::cout << "OpenGL version major: " << GLVersion.major << " minor:" << GLVersion.minor;

	initGL = true;
}

void Graphics::terminate()
{
	if (!init)
		return;

	glfwTerminate();

	init = false;
}
