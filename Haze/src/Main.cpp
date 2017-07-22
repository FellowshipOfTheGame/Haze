#include <iostream>
#include <cstdlib>

#include "Graphics.hpp"
#include "Haze.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "al.h"
#include "alc.h"


inline void err(int errn, const char* str)
{
	std::cout << str << std::endl;
	exit(errn);
}

int main(int argc, char** argv)
{
	ALCdevice *dev = NULL;
	ALCcontext *ctx = NULL;


	dev = alcOpenDevice(NULL);
	if (!dev)
		err(-1, "Could not open device");
	ctx = alcCreateContext(dev, NULL);
	if (!ctx)
		err(-1, "Could not create context");

	std::cout << "Opened device: " << alcGetString(dev, ALC_DEVICE_SPECIFIER) << std::endl;

	alcMakeContextCurrent(ctx);

	GLFWwindow* window = graphicsInit();
	std::cout << "OpenGL version major: " << GLVersion.major << " minor:" << GLVersion.minor;

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

	graphicsDestroy(window);

	alcMakeContextCurrent(NULL);
	alcDestroyContext(ctx);
	alcCloseDevice(dev);


    return EXIT_SUCCESS;
}
