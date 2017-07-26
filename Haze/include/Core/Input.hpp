#ifndef HAZE_INPUT_HPP
#define HAZE_INPUT_HPP

#include <string>
#include "GLFW/glfw3.h"
#include "InputState.hpp"


class Input
{
	InputState *state, *buffer;

	Input();
public:
	Input(GLFWwindow* window);

	void poll();
	InputState* getState();
};

#endif //HAZE_INPUT_HPP
