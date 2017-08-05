#include "Window.hpp"

bool Window::init = false;

bool Window::loaded()
{
	return Window::init;
}

void Window::initialize()
{
	if (init)
		return;

	if (!glfwInit())
		err(-1, "GLFW init error");

	glfwConfig();

	glfwSetErrorCallback(err);

	init = true;
}

void Window::terminate()
{
	if (!init)
		return;
	
	glfwTerminate();

	init = false;
}

Window::Window(int width, int height, Window* parent)
{
	if (!Window::init)
		Window::initialize();

	if(parent == NULL)
		handler = glfwCreateWindow(width, height, u8"Haze Engine", NULL, NULL);
	else
		handler = glfwCreateWindow(width, height, u8"Haze Engine", NULL, parent->handler);

	if (!handler)
		err(-1, "GLFW window creation error");
	
	input = new Input(handler);
}

Window::~Window()
{
	if (handler != NULL)
		glfwDestroyWindow(handler);
}

void Window::update()
{
	input->poll();
}

void Window::flush()
{
	input->clear();
}

InputState* Window::getInput()
{
	return input->getState();
}

void Window::setContext()
{
	if (handler != NULL)
		glfwMakeContextCurrent(handler);
}

bool Window::running()
{
	return glfwWindowShouldClose(handler) == 0;
}

void Window::close()
{
	glfwSetWindowShouldClose(handler, 1);
}


void frambufferCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void refreshCallback(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}
