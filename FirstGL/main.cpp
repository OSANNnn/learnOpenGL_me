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
#include "keyboard.h"
#include "mouse.h"

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

	float vertices[] = {
		//	vertexCoords          normals
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	
	Shader cubeShader("colorCube.vert", "colorCube.frag");
	Shader lightShader("light.vert", "light.frag");

	VBO cubeVBO;
	VAO cubeVAO, lightsourceVAO;
	GLuint CubeVerticesCount = 36;

	vec3 cubeColor(1.0f, 0.5f, 0.31f);
	vec3 lightColor(0.0f, 1.0f, 0.0f);
	vec3 lightPos(1.2f, 1.0f, 2.0f);

	Material cubeMaterial(cubeColor);
	Light lightCube{};

	cubeVAO.Bind();
	cubeVBO.Bind();
	cubeVBO.Data(vertices, sizeof(vertices));
	cubeVAO.setVertexCount(CubeVerticesCount);
	cubeVAO.SetAttrib(0, 3, sizeof(float) * 6, 0);
	cubeVAO.SetAttrib(1, 3, sizeof(float) * 6, 3 * sizeof(float));
	cubeVAO.UnBind();

	lightsourceVAO.Bind();
	lightsourceVAO.SetAttrib(0, 3, sizeof(float) * 6, 0);
	lightsourceVAO.setVertexCount(CubeVerticesCount);
	lightsourceVAO.UnBind();
	cubeVBO.UnBind();

	stbi_set_flip_vertically_on_load(true);


	//uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mat4 view = camera.getViewMatrix();
	mat4 projection(1.0f);
	mat4 model(1.0f);
	float aspect = (float)width / height;

	lightCube.position = lightPos;
	lightCube.ambient = vec3(0.5f);
	lightCube.diffuse = lightColor;
	lightCube.specular = lightColor;

	/*cubeMaterial.ambient = cubeColor;
	cubeMaterial.diffuse = cubeColor;
	cubeMaterial.specular = vec3(0.5f, 0.5f, 0.5f);
	cubeMaterial.shininess = 32.0f;*/

	glEnable(GL_DEPTH_TEST);

	//main render loop -----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		projection = perspective(radians(camera.fov()), aspect, 0.1f, 100.0f);

		processInput(window, camera);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//random moving light
		/*lightCube.position.x = 1.0f + (float) sin(glfwGetTime()) * 2.0f;
		lightCube.position.y = (float) sin(glfwGetTime() / 2.0f) * 1.0f;
		lightCube.position.z = (float) cos(glfwGetTime());	*/	

		lightShader.Use();
		lightShader.setVec3("lightColor", lightColor);
		lightsourceVAO.Bind();
		model = mat4(1.0f);
		model = translate(model, lightCube.position);
		model = scale(model, vec3(0.2f));
		lightShader.setMat4f("model", model);
		lightShader.setMat4f("view", view);
		lightShader.setMat4f("projection", projection);
		lightsourceVAO.Draw();

		cubeShader.Use();
		cubeShader.setMaterial("material", cubeMaterial);
		cubeShader.setLight("light", lightCube);
		cubeVAO.Bind();
		view = camera.getViewMatrix();
		model = mat4(1.0);
		//model = rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
		cubeShader.setMat4f("model", model);
		cubeShader.setMat4f("view", view);
		cubeShader.setMat4f("projection", projection);
		cubeShader.setVec3("viewPos", camera.position());
		cubeVAO.Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//main render loop --------------------------------------------------------------------------END

	//delete everything
	cubeVAO.Delete();
	cubeVBO.Delete();
	lightsourceVAO.Delete();
	cubeShader.Delete();
	lightShader.Delete();

	//clean memory and close the program
	glfwTerminate();
	return 0;
}