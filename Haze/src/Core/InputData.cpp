#include "Input.hpp"

enum InputType
{

};

typedef struct
{

} WindowInputData;

typedef struct
{

} KeyboardInputData;


typedef struct
{

} MouseInputData;


typedef struct
{

} JoystickInputData;


typedef union
{
	WindowInputData window;
	KeyboardInputData keyboard;
	MouseInputData mouse;
	JoystickInputData joystick;
} InputData;

typedef struct
{
	InputType type;
	InputData data;
};
