#include "Graphics.hpp"

GLFWwindow* graphicsInit()
{
	if (!glfwInit())
		err(-1, "GLFW init error");

	glfwSetErrorCallback(err);

	glfwConfig();

	GLFWwindow* window = NULL;
	window = glfwCreateWindow(WIDTH, HEIGHT, u8"Haze Engine", NULL, NULL);

	if(!window)
		err(-1, "GLFW window creation error");

	glfwMakeContextCurrent(window);

	if (!gladLoadGL())
		err(-1, "GLAD init error");

	return window;
}

void graphicsDestroy(GLFWwindow* window)
{

	glfwDestroyWindow(window);
	glfwTerminate();
}
