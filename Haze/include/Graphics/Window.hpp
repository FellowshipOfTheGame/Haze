#ifndef HAZE_WINDOW_HPP
#define HAZE_WINDOW_HPP

#include "Haze.hpp"
#include "Graphics.hpp"
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* handler;
	Window()
	{
		handler = NULL;
	};
public:
	Window(int width, int height, Window* parent);
	~Window();
	void setContext();
};

#endif //!HAZE_WINDOW_HPP
