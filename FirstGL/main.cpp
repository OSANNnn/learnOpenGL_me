#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.hpp"
#include "utils.hpp"
#include "Shader.hpp"
#include "buffers.hpp"
#include "materials.hpp"
#include "lights.hpp"
#include "keyboard.h"
#include "mouse.h"
#include "model.h"


using namespace std;
using namespace Buffers;
using namespace glm;

//canvas size
const unsigned int width = 800;
const unsigned int height = 600;

Fly_Camera camera(vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float mouseLastX = 400;
float mouseLastY = 300;
bool firstMouse = true;


int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Learn opengGL", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glViewport(0, 0, width, height);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
	glfwSetScrollCallback(window, Mouse::mouseWheelCallback);
	glfwSetKeyCallback(window, Keyboard::keycallback);
	
	stbi_set_flip_vertically_on_load(true);

	float cubeVertices[] = {
	//   positions            texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	float planeVertices[] = {
	//   positions            texture Coords
		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

		 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
		 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
	};

	VBO cubeVBO, planeVBO;
	VAO cubeVAO, planeVAO;

	cubeVAO.Bind();
	cubeVBO.Bind();
	cubeVBO.Data(cubeVertices, sizeof(cubeVertices));
	cubeVAO.SetAttrib(0, 3, 5 * sizeof(float), 0);
	cubeVAO.SetAttrib(1, 2, 5 * sizeof(float), 3 * sizeof(float));
	cubeVAO.setVertexCount(36);
	planeVAO.Bind();
	planeVBO.Bind();
	planeVBO.Data(planeVertices, sizeof(planeVertices));
	planeVAO.SetAttrib(0, 3, 5 * sizeof(float), 0);
	planeVAO.SetAttrib(1, 2, 5 * sizeof(float), 3 * sizeof(float));
	planeVAO.setVertexCount(6);
	planeVBO.UnBind();
	planeVAO.UnBind();

	Texture marble; //cube
	marble.TexData("../assets/textures/marble.jpg");
	Texture metal; //floor
	metal.TexData("../assets/textures/metal.png");

	Shader plainTextures("texturePreview.vert", "texturePreview.frag");
	plainTextures.Use();
	plainTextures.SetInt("texture1", 0);

	mat4 view = camera.getViewMatrix();
	mat4 projection(1.0f);
	mat4 model(1.0f);
	float aspect = (float)width / height;

	//uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_ALWAYS);

	//main render loop -----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(window, camera);
		
		projection = perspective(radians(camera.fov()), aspect, 0.1f, 100.0f);
		view = camera.getViewMatrix();

		plainTextures.Use();
		model = mat4(1.0f);
		plainTextures.setMat4f("view", view);
		plainTextures.setMat4f("projection", projection);

		cubeVAO.Bind();
		marble.Activate(0);
		model = translate(model, vec3(-1.0f, 0.0f, -1.0f));
		plainTextures.setMat4f("model", model);
		cubeVAO.Draw();

		model = mat4(1.0f);
		model = translate(model, vec3(2.0f, 0.0f, 0.0f));
		plainTextures.setMat4f("model", model);
		cubeVAO.Draw();

		planeVAO.Bind();
		metal.Activate(0);
		model = mat4(1.0f);
		plainTextures.setMat4f("model", model);
		planeVAO.Draw();
		planeVAO.UnBind();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//main render loop --------------------------------------------------------------------------END

	//delete everything
	cubeVAO.Delete();
	planeVAO.Delete();
	cubeVBO.Delete();
	planeVBO.Delete();
	plainTextures.Delete();
	marble.Delete();
	metal.Delete();

	//clean memory and close the program
	glfwTerminate();
	return 0;
}