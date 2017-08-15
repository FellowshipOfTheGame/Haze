#ifndef HAZE_INPUT_HPP
#define HAZE_INPUT_HPP

#include <map>
#include <mutex>
#include <string>
#include <cstring>
#include "GLFW/glfw3.h"
#include "InputState.hpp"


class Input
{
	GLFWwindow* window;

	Input();
public:
	Input(GLFWwindow* window);
	~Input();

	InputState *state;
	InputState* getState();
	void poll();
	void clear();
};

#endif //HAZE_INPUT_HPP
