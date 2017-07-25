#include "Window.hpp"

Window::Window(int width, int height, Window* parent)
{
	if(parent == NULL)
		handler = glfwCreateWindow(width, height, u8"Haze Engine", NULL, NULL);
	else
		handler = glfwCreateWindow(width, height, u8"Haze Engine", NULL, parent->handler);

	if (!handler)
		err(-1, "GLFW window creation error");
}

Window::~Window()
{
	if (handler != NULL)
		glfwDestroyWindow(handler);
}

void Window::setContext()
{
	if (handler != NULL)
		glfwMakeContextCurrent(handler);

	Graphics::loadGL();
}


void frambufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void refreshCallback(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}
