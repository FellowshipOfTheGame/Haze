#ifndef HAZE_GRAPHICS_HPP
#define HAZE_GRAPHICS_HPP

#include "glad/glad.h"

#include "Window.hpp"
#include "Haze.hpp"

class Graphics
{
	static bool init;
	Graphics();
public:
	static void initialize(Window* window);
	static void terminate();
};

#endif // !HAZE_GRAPHICS_HPP
