#include "Haze.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

int main(int argc, char** argv)
{
    std::cout << "Hello world" << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);//GLFW_TRUE or GLFW_FALSE

    glfwWindowHint(GLFW_RED_BITS, 8);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_GREEN_BITS, 8);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_BLUE_BITS, 8);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_ALPHA_BITS, 8);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_DEPTH_BITS, 24);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_STENCIL_BITS, 8);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_ACCUM_RED_BITS, 0);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_ACCUM_GREEN_BITS, 0);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_ACCUM_BLUE_BITS, 0);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_ACCUM_ALPHA_BITS, 0);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_AUX_BUFFERS, 0);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_SAMPLES, 0);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);//0 to INT_MAX or GLFW_DONT_CARE
    glfwWindowHint(GLFW_STEREO, GLFW_FALSE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_FALSE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);//GLFW_TRUE or GLFW_FALSE

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);//GLFW_OPENGL_API, GLFW_OPENGL_ES_API or GLFW_NO_API
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);//GLFW_NATIVE_CONTEXT_API or GLFW_EGL_CONTEXT_API
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//Any valid major version number of the chosen client API
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//Any valid minor version number of the chosen client API
    glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);//GLFW_NO_ROBUSTNESS, GLFW_NO_RESET_NOTIFICATION or GLFW_LOSE_CONTEXT_ON_RESET
    glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_ANY_RELEASE_BEHAVIOR);//GLFW_ANY_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_FLUSH or GLFW_RELEASE_BEHAVIOR_NONE

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_FALSE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);//GLFW_TRUE or GLFW_FALSE
    glfwWindowHint(GLFW_OPENGL_PROFILE,	GLFW_OPENGL_CORE_PROFILE);//GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_COMPAT_PROFILE or GLFW_OPENGL_CORE_PROFILE


    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, u8"Haze Engine", NULL, NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL();

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

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }


    glfwDestroyWindow(window);
    glfwTerminate();


    return EXIT_SUCCESS;
}