#ifndef HAZE_GRAPHICS_HPP
#define HAZE_GRAPHICS_HPP

#include "GraphicsConfiguration.hpp"
#include "GLFW\glfw3.h"
#include "glad/glad.h"
#include "Haze.hpp"
#include <iostream>

class Graphics
{
	static bool init;
	static bool initGL;
	Graphics();
public:
	static void initialize();
	static void terminate();
	static void loadGL();
};


//glfwSetWindowCloseCallback(window, window_close_callback);
//glfwSetWindowSizeCallback(window, window_size_callback);
//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//glfwSetWindowPosCallback(window, window_pos_callback);
//glfwSetWindowIconifyCallback(window, window_iconify_callback);
//glfwSetWindowFocusCallback(window, window_focus_callback);
//glfwSetWindowRefreshCallback(m_handle, window_refresh_callback);
//void window_refresh_callback(GLFWwindow* window)
//{
//    draw_editor_ui(window);
//    glfwSwapBuffers(window);
//}

#endif // !HAZE_GRAPHICS_HPP
