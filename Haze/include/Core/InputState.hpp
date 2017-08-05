#ifndef HAZE_INPUTDATA_HPP
#define HAZE_INPUTDATA_HPP

#include "GLFW\glfw3.h"

#define HAZE_KEY_SIZE GLFW_KEY_LAST + 1
#define HAZE_MOUSE_BUTTON_SIZE GLFW_MOUSE_BUTTON_LAST + 1
#define HAZE_JOYSTICK_SIZE GLFW_JOYSTICK_LAST + 1

#define HAZE_IN_NONE 0
#define HAZE_IN_PRESS 1
#define HAZE_IN_RELEASE 2
#define HAZE_IN_REPEAT 3

#define HAZE_IN_SHIFT GLFW_MOD_SHIFT
#define HAZE_IN_ALT GLFW_MOD_ALT
#define HAZE_IN_SUPER GLFW_MOD_SUPER
#define HAZE_IN_CONTROL GLFW_MOD_CONTROL


typedef struct
{
	int state;
	int mods;
} KeyboardInput;

typedef struct
{
	int action;
	int mods;
} MouseButtonInput;

typedef struct
{
	bool entered;
	bool left;
	bool moved;
} MouseInput;

typedef struct
{
	bool connected;
	const float* axes;
	const unsigned char* buttons;
} JoystickInput;

typedef struct
{
	double x, y;
	double scrollX, scrollY;
} MouseState;

typedef struct
{
	KeyboardInput key[HAZE_KEY_SIZE];

	JoystickInput joystick[HAZE_JOYSTICK_SIZE];

	MouseState mouse;
	MouseInput mouseEvents;
	MouseButtonInput mouseButton[HAZE_MOUSE_BUTTON_SIZE];
} InputState;

#endif //HAZE_INPUTDATA_HPP
