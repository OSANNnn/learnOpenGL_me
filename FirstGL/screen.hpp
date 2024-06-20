#pragma once

#include <glfw3.h>


class Screen {

	GLFWwindow *window;
public:
	static unsigned int Screen_width;
	static unsigned int Screen_height;

	Screen();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	bool init();
	void setParameters();

	void update();
	void newFrame();

	bool shouldClose();
	void setShouldClose(bool shouldClose);

};