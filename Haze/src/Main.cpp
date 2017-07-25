#include "Haze.hpp"

#include "InputData.hpp"
#include "Audio.hpp"
#include "Physics.hpp"
#include "Graphics.hpp"



int main(int argc, char** argv)
{
	
	Audio::initialize();
	Physics::initialize();
	Graphics::initialize();

    //while(!glfwWindowShouldClose(window))
    //{
    //    glfwPollEvents();
    //    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);
    //    glfwSwapBuffers(window);
    //}

	Graphics::terminate();
	Physics::terminate();
	Audio::terminate();

    return EXIT_SUCCESS;
}
