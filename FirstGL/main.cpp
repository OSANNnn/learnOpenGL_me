#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>
#include <cstdlib>
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
//texture mix
float mixValue = 0.3f;

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

	/*vec3 pointLightPositions[] = {
		vec3(0.7f, 0.2f, 2.0f),
		vec3(2.3f, -3.3f, -4.0f),
		vec3(-4.0f, 2.0f, -12.0f),
		vec3(0.0f, 0.0f, -3.0f)
	};*/

	//Shader cubeShader("phongModel.vert", "phongModel.frag");
	//Shader lightShader("light.vert", "light.frag");
	Shader defaultShader("default.vert", "default.frag");
		
	DirectionalLight directionalLight;
	directionalLight.direction = vec3(-0.2f, -1.0f, -0.3f);
	directionalLight.ambient = vec3(0.1f);
	directionalLight.diffuse = vec3(0.0f);
	//directionalLight.diffuse = vec3(1.0f, 1.0f, 0.8f);
	//directionalLight.specular = vec3(0.2f);
	directionalLight.specular = vec3(1.0f, 1.0f, 0.8f);

	/*PointLight lightCube[4];
	for (int i = 0; i < 4; i++) {
		vec3 lightColor;
		switch (i) {
		case 0:
			lightColor = vec3(1.0f, 1.0f, 0.0f);
			break;
		case 1:
			lightColor = vec3(0.0f, 1.0f, 1.0f);
			break;
		case 2:
			lightColor = vec3(1.0f, 0.0f, 1.0f);
			break;
		case 3:
			lightColor = vec3(0.0f, 1.0f, 0.0f);
			break;
		}

		lightCube[i].position = pointLightPositions[i];
		lightCube[i].ambient = vec3(0.0f);
		lightCube[i].diffuse = lightColor;
		lightCube[i].specular = lightColor;
		lightCube[i].constant = 1.0f;
		lightCube[i].linear = 0.0009f;
		lightCube[i].quadratic = 0.032f;
	}*/

	SpotLight torch;
	torch.position = camera.position();
	torch.position = camera.front();
	torch.ambient = vec3(0.1f);
	torch.diffuse = vec3(0.8f);
	torch.specular = vec3(0.8);
	torch.cutOff = cos(radians(12.5f));
	torch.outerCutOff = cos(radians(15.0f));
	
	stbi_set_flip_vertically_on_load(true);

	Model backpack("../assets/backpack/backpack.obj");


	mat4 view = camera.getViewMatrix();
	mat4 projection(1.0f);
	mat4 model(1.0f);
	float aspect = (float)width / height;
	vec3 clearColor(0.2f, 0.7f, 1.0f);

	//uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	//main render loop -----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window, camera);
		
		projection = perspective(radians(camera.fov()), aspect, 0.1f, 100.0f);
		view = camera.getViewMatrix();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//defaultShader.setDirectionalLight("uDirectionalLigth", directionalLight);
		model = mat4(1.0f);
		model = scale(model, vec3(0.2f, 0.2f, 0.2f));
		defaultShader.Use();
		defaultShader.setDirectionalLight("directionalLight", directionalLight);
		defaultShader.setMat4f("uModel", model);
		defaultShader.setMat4f("uView", view);
		defaultShader.setMat4f("uProjection", projection);
		defaultShader.setVec3("viewPos", camera.position());
		defaultShader.SetFloat("material.shininess", 64.f);
		backpack.Draw(defaultShader);
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//main render loop --------------------------------------------------------------------------END

	//delete everything


	//clean memory and close the program
	glfwTerminate();
	return 0;
}