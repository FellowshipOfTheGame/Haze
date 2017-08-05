#include "Input.hpp"


//std::map<GLFWwindow*, std::mutex*> bufferMutex;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Input::Input(GLFWwindow* _window) : window(_window)
{
	//bufferMutex[window] = new std::mutex();
	state = (InputState*)std::calloc(1, sizeof(InputState));
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, keyCallback);
}

void Input::poll()
{
	glfwPollEvents();
/*
	std::lock_guard<std::mutex> guard(*bufferMutex[window]);

#ifdef _MSC_VER 
	memcpy_s(state, sizeof(InputState), buffer, sizeof(InputState));
	memset(buffer, 0, sizeof(buffer));
#else
	memcpy(state, buffer, sizeof(InputState));
	memset(buffer, 0, sizeof(buffer));
#endif // MSVC
*/
}
void Input::clear()
{
	std::memset(state, 0, sizeof(InputState));
}

Input::~Input()
{
	//delete bufferMutex[window];
}

InputState* Input::getState()
{
	return state;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int _action, int _mods)
{
	Input* input = (Input*)glfwGetWindowUserPointer(window);
	int mods = 0;
	int action = 0;
	switch (_action)
	{
	case GLFW_PRESS:
		action = HAZE_IN_PRESS;
		break;
	case GLFW_RELEASE:
		action = HAZE_IN_RELEASE;
		break;
	case GLFW_REPEAT:
		action = HAZE_IN_REPEAT;
		break;
	default:
		action = HAZE_IN_NONE;
		break;
	}
	if (_mods & GLFW_MOD_SHIFT)
		mods += HAZE_IN_SHIFT;
	//std::lock_guard<std::mutex> guard(*bufferMutex[window]);
	input->state->key[key].state = action;
	input->state->key[key].mods = mods;
}
