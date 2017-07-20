#ifndef HAZE_INPUTDATA_HPP
#define HAZE_INPUTDATA_HPP

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


typedef struct
{

	WindowInputData window;
	KeyboardInputData keyboard;
	MouseInputData mouse;
	JoystickInputData joystick;
} InputData;

#endif //HAZE_INPUTDATA_HPP
