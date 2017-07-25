#ifndef HAZE_INPUT_HPP
#define HAZE_INPUT_HPP


#include <GLFW/glfw3.h>
#include "InputData.hpp"
#include "Window.hpp"


class Input
{
    static Input* input;
	InputState state, buffer;
    Input();

public:
    static void create(Window* window);
    void setCurrentWindow(Window* window);
    static Input* get();

};


#endif //HAZE_INPUT_HPP
