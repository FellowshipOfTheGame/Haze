#ifndef HAZE_WINDOW_HPP
#define HAZE_WINDOW_HPP

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Haze.hpp"
#include "Input.hpp"
#include "GraphicsConfiguration.hpp"

class Window
{
private:
	static bool init;

	Input* input;
	GLFWwindow* handler;

	Window();
public:
	Window(int width, int height, Window* parent);
	~Window();

	static bool loaded();
	static void initialize();
	static void terminate();

	void close();
	bool running();
	void setContext();

	void flush();
	void update();
	InputState* getInput();
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


#endif //!HAZE_WINDOW_HPP
