#ifndef HAZE_INPUTDATA_HPP
#define HAZE_INPUTDATA_HPP

#include "GLFW\glfw3.h"

#define HAZE_KEY_SIZE GLFW_KEY_LAST + 1
#define HAZE_MOUSE_BUTTON_SIZE GLFW_MOUSE_BUTTON_LAST + 1
#define HAZE_JOYSTICK_SIZE GLFW_JOYSTICK_LAST + 1

#define KEY_NONE 0
#define KEY_PRESSED 1
#define KEY_RELEASED 2
#define KEY_REPEAT 3


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
	MouseButtonInput mouseButton[HAZE_MOUSE_BUTTON_SIZE];
	JoystickInput joystick[HAZE_JOYSTICK_SIZE];
	MouseState mouse;
} InputState;

#endif //HAZE_INPUTDATA_HPP
