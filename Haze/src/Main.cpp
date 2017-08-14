#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "LearnOpenGL/filesystem.h"
#include "LearnOpenGL/shader.h"
#include "LearnOpenGL/camera.h"
#include "LearnOpenGL/model.h"

#include <iostream>

// Callbacks
void frambufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void errorHandler(int num, const char* message);

// Settings
unsigned int screenWidth = 800;
unsigned int screenHeight = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = screenWidth / 2.0f;
float lastY = screenHeight / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Render Buffer Object
unsigned int rbo;
unsigned int framebuffer;
unsigned int textureColorbuffer;

// Shader programs
Shader* nanosuitShader;
Shader* screenShader;
// Nanosuit model
Model* nanosuit;

// Using geometry shader?
bool geometry = false;

// Using post processing?
bool postProcessing = false;

// Model scale and rotation
glm::vec3 scale(1.0f, 1.0f, 1.0f);
glm::vec3 up(0.0f, 0.0f, 1.0f);
glm::vec3 fwd(1.0f, 0.0f, 0.0f);
float yaw = 0.0f, row = 0.0f;

int main()
{
	// Initialize glfw and check for errors
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Error initializing GLFW" << std::endl;
		return -1;
	}
	// Set error handler (just print)
	glfwSetErrorCallback(errorHandler);

	// OpenGL version is 3.3 Core Profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window and check if there is no error
	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Introduction to GLSL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set OpenGL context to current
	glfwMakeContextCurrent(window);

	// Attach callbacks to window input
	glfwSetFramebufferSizeCallback(window, frambufferSizeCallback);
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	// Hide mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Load opengl functions and check for errors
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Create shaders (vertex and fragment) and load model (nanosuit)
	nanosuitShader = new Shader("../Haze/shader/vertex.glsl", "../Haze/shader/fragment.glsl");
	screenShader = new Shader("../Haze/shader/screen_vertex.glsl", "../Haze/shader/screen_fragment.glsl");
	nanosuit = new Model("../Haze/resources/objects/nanosuit/nanosuit.obj");

	// Generate framebuffer
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Generate texture for framebuffer
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	// Generate render bufffer
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// Check if framebuffer status is ready, unbind
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Quad for framebuffer output (full screen)
	float quadVertices[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		1.0f, -1.0f,  1.0f, 0.0f,
		1.0f,  1.0f,  1.0f, 1.0f
	};

	// Create quad objects
	unsigned int quadVAO, quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// Loop
	while (!glfwWindowShouldClose(window))
	{
		// Elapsed time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process input (keyboard)
		processInput(window);

		// Bind framebuffer texture if using post processing
		if(postProcessing)
			glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		else
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glEnable(GL_DEPTH_TEST);

		// Clear framebuffer buffer
		glClearColor(0.00f, 0.2f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		nanosuitShader->use();

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model;

		model = glm::rotate(model, yaw, up);
		model = glm::rotate(model, row, fwd);
		model = glm::translate(model, glm::vec3(0.0f, -8.75f, 0.0f) * scale);
		model = glm::scale(model, scale);

		// Set MVP matrixes and normal matrix
		nanosuitShader->setMat4("Projection", projection);
		nanosuitShader->setMat4("View", view);
		nanosuitShader->setMat4("Model", model);
		nanosuitShader->setMat4("Normal", glm::transpose(glm::inverse(model)));

		// Mouse position
		double mousex, mousey;
		glfwGetCursorPos(window, &mousex, &mousey);

		// Set auxiliar variables for cool stuff
		nanosuitShader->setFloat("Time", (float)glfwGetTime());
		nanosuitShader->setVec2("Mouse", glm::vec2((float)mousex, (float)mousey));
		nanosuitShader->setVec2("Resolution", glm::vec2(screenWidth, screenHeight));
		
		nanosuit->Draw(nanosuitShader);

		if (postProcessing)
		{
			// Bind to scene and disable depth
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glDisable(GL_DEPTH_TEST);

			// Clear scene (useless clear)
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Bind texture to shader and use program
			screenShader->setInt("Framebuffer", 0);
			screenShader->use();

			//Bind quad and draw texture
			glBindVertexArray(quadVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all things and terminate
	glDeleteTextures(1, &textureColorbuffer);
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteRenderbuffers(1, &rbo);
	glDeleteBuffers(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);

	delete nanosuitShader;
	delete screenShader;
	delete nanosuit;

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		yaw += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		yaw -= 0.001f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		row += 0.001f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		row -= 0.001f;
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_F2:
			delete nanosuitShader;
			if (geometry)
				nanosuitShader = new Shader("../Haze/shader/vertex.glsl", "../Haze/shader/fragment.glsl");
			else
				nanosuitShader = new Shader("../Haze/shader/vertex.glsl", "../Haze/shader/fragment.glsl", "../Haze/shader/geometry.glsl");
			geometry = !geometry;
			break;
		case GLFW_KEY_F3:
			postProcessing = !postProcessing;
			break;
		case GLFW_KEY_F5:
			delete nanosuitShader;
			if (!geometry)
				nanosuitShader = new Shader("../Haze/shader/vertex.glsl", "../Haze/shader/fragment.glsl");
			else
				nanosuitShader = new Shader("../Haze/shader/vertex.glsl", "../Haze/shader/fragment.glsl", "../Haze/shader/geometry.glsl");

			delete screenShader;
			screenShader = new Shader("../Haze/shader/screen_vertex.glsl", "../Haze/shader/screen_fragment.glsl");
			break;
		}
	}
}

void frambufferSizeCallback(GLFWwindow* window, int width, int height)
{
	screenWidth = width;
	screenHeight = height;
	glViewport(0, 0, width, height);

	glDeleteTextures(1, &textureColorbuffer);
	glDeleteFramebuffers(1, &framebuffer);
	glDeleteRenderbuffers(1, &rbo);

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (yoffset > 0.0)
		scale *= 1.1f;
	else
		scale *= 0.9f;
}


void errorHandler(int num, const char* message)
{
	std::cout << "Error " << num << ": " << message << std::endl;
}
