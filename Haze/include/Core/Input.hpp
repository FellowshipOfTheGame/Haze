#ifndef HAZE_INPUT_HPP
#define HAZE_INPUT_HPP


#include <GLFW/glfw3.h>
#include "InputData.hpp"

enum ListenerType
{

};

typedef int (*ListenerCallback)(InputData*);

class Input
{
    static Input* input;
    GLFWwindow* currentWindow;
    Input();

public:
    void createInput(GLFWwindow* window);
    void setCurrentWindow(GLFWwindow* window);
    Input* getInput();
    void addInputCallback(ListenerType, ListenerCallback);

};


#endif //HAZE_INPUT_HPP
