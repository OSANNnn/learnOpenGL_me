#include "utils.hpp"

extern Fly_Camera camera;
extern float deltaTime;
extern float mixValue;
extern float mouseLastX;
extern float mouseLastY;
extern bool firstMouse;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		mouseLastX = (float)xpos;
		mouseLastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - mouseLastX;
	float yoffset = (float)mouseLastY - ypos;

	mouseLastX = (float)xpos;
	mouseLastY = (float)ypos;

	camera.processMouseMovement(xoffset, yoffset, false);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll((float)yoffset);
}

void processInput(GLFWwindow* window, Fly_Camera& camera)
{
	const float cameraSpeed = 2.5f * deltaTime;

	camera.setSpeed(2.5f);

	//window close
	if (Keyboard::keyDown(GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window, true);

	//camera controls
	if (Keyboard::key(GLFW_KEY_W))
	{
		camera.processKeyboard(FORWARD, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_S))
	{
		camera.processKeyboard(BACKWARD, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_A))
	{
		camera.processKeyboard(STRAFE_LEFT, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_D))
	{
		camera.processKeyboard(STRAFE_RIGHT, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_E))
	{
		camera.processKeyboard(STRAFE_UP, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_Q))
	{
		camera.processKeyboard(STRAFE_DOWN, deltaTime);
	}
}

