#include "Input.hpp"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Input::Input(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, keyCallback);
}

void Input::poll()
{
	glfwPollEvents();

#ifdef _MSC_VER 
	memcpy_s(state, sizeof(InputState), buffer, sizeof(InputState));
	memset(buffer, 0, sizeof(buffer));
#else
	memcpy(state, buffer, sizeof(InputState));
	memset(buffer, 0, sizeof(buffer));
#endif // MSVC
}

InputState* Input::getState()
{
	return state;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}
