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

	glm::vec3 cubePositions[] = {
		vec3(0.0f, 0.0f, 0.0f),
		vec3(2.0f, 5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f, -0.4f, -3.5f),
		vec3(-1.7f, 3.0f, -7.5f),
		vec3(1.3f, -2.0f, -2.5f),
		vec3(1.5f, 2.0f, -2.5f),
		vec3(1.5f, 0.2f, -1.5f),
		vec3(-1.3f, 1.0f, -1.5f)
	};

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	
	Shader cubeShader("colorCube.vert", "colorCube.frag");
	Shader lightShader("light.vert", "light.frag");

	cubeShader.Use();
	cubeShader.SetInt("material.diffuse", 0);
	cubeShader.SetInt("material.specular", 1);
	cubeShader.SetInt("material.emission", 2);

	VBO cubeVBO;
	VAO cubeVAO, lightsourceVAO;
	GLuint CubeVerticesCount = 36;

	vec3 cubeColor(1.0f, 0.5f, 0.31f);
	vec3 lightColor(1.0f);
	vec3 lightPos(1.2f, 1.0f, 2.0f);

	Light lightCube;

	lightCube.position = lightPos;
	lightCube.ambient = vec3(0.1f);
	lightCube.diffuse = lightColor;
	lightCube.specular = lightColor;

	Texture reinforcedBox;
	Texture reinforcedBoxSpecularMap;
	Texture emissionMatrix;

	reinforcedBox.TexData("container2.png");
	reinforcedBoxSpecularMap.TexData("container2_specular.png");
	emissionMatrix.TexData("matrix.jpg", false);

	cubeVAO.Bind();
	cubeVBO.Bind();
	cubeVBO.Data(vertices, sizeof(vertices));
	cubeVAO.setVertexCount(CubeVerticesCount);
	cubeVAO.SetAttrib(0, 3, sizeof(float) * 8, 0);
	cubeVAO.SetAttrib(1, 3, sizeof(float) * 8, 3 * sizeof(float));
	cubeVAO.SetAttrib(2, 2, sizeof(float) * 8, 6 * sizeof(float));
	cubeVAO.UnBind();

	lightsourceVAO.Bind();
	lightsourceVAO.SetAttrib(0, 3, sizeof(float) * 8, 0);
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

		//random moving light
		/*lightCube.position.x = 1.0f + (float) sin(glfwGetTime()) * 2.0f;
		lightCube.position.y = (float) sin(glfwGetTime() / 2.0f) * 1.0f;
		lightCube.position.z = (float) cos(glfwGetTime());	*/	

		/*lightShader.Use();
		lightShader.setVec3("lightColor", lightColor);
		lightsourceVAO.Bind();
		model = mat4(1.0f);
		model = translate(model, lightCube.position);
		model = scale(model, vec3(0.2f));
		lightShader.setMat4f("model", model);
		lightShader.setMat4f("view", view);
		lightShader.setMat4f("projection", projection);
		lightsourceVAO.Draw();*/

		for (int i = 0; i < 10; i++)
		{
			cubeVAO.Bind();
			cubeShader.Use();
			cubeShader.SetFloat("material.shininess", 64.0f);
			cubeShader.setLight("light", lightCube);
			cubeShader.setVec3("light.direction", vec3(-0.2f, -1.0f, -0.3f));
			model = mat4(1.0f);
			model = translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = rotate(model, radians(angle), vec3(0.1f, 0.3f, 0.5f));
			cubeShader.setMat4f("model", model);
			cubeShader.setMat4f("view", view);
			cubeShader.setMat4f("projection", projection);
			cubeShader.setVec3("viewPos", camera.position());
			reinforcedBox.Activate(0);
			reinforcedBoxSpecularMap.Activate(1);
			emissionMatrix.Activate(2);
			cubeVAO.Draw();
		}

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
	reinforcedBox.Delete();
	reinforcedBoxSpecularMap.Delete();
	emissionMatrix.Delete();

	//clean memory and close the program
	glfwTerminate();
	return 0;
}