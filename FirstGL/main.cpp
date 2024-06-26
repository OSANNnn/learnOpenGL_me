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

	float quadVertices[]{
		-0.6f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
		-0.6f,  0.6f, 0.0f, 1.0f, 0.0f, // bottom right
		-1.0f,  0.6f, 0.0f, 0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f // top left
	};

	unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	VAO textureQuadVAO;
	VBO quad;
	EBO quadIndices;

	textureQuadVAO.Bind();
	quad.Bind();
	quad.Data(quadVertices, sizeof(quadVertices));
	quadIndices.Bind();
	quadIndices.Data(indices, sizeof(quadIndices));

	textureQuadVAO.SetAttrib(0, 3, 5 * sizeof(float), 0);
	textureQuadVAO.SetAttrib(1, 2, 5 * sizeof(float), 3 * sizeof(float));

	textureQuadVAO.UnBind();
	quad.UnBind();
	quadIndices.UnBind();

	Texture diffuse;
	diffuse.TexData("../assets/backpack/diffuse.jpg");

	Shader texturePreview("texturePreview.vert", "texturePreview.frag");
	Shader defaultShader("default.vert", "default.frag");
		
	DirectionalLight directionalLight;
	directionalLight.direction = vec3(-0.2f, -1.0f, -0.3f);
	directionalLight.ambient = vec3(0.1f);
	directionalLight.diffuse = vec3(1.0f);
	//directionalLight.diffuse = vec3(1.0f, 1.0f, 0.8f);
	//directionalLight.specular = vec3(0.2f);
	directionalLight.specular = vec3(1.0f, 1.0f, 0.8f);

	PointLight pointLight;

	pointLight.position = vec3(0.0f, 0.0f, 10.0f);
	pointLight.ambient = vec3(0.0001f);
	pointLight.diffuse = vec3(1.0f, 1.0f, 0.9f);
	pointLight.specular = vec3(1.0f, 1.0f, 0.9f);
	pointLight.constant = 1.0f;
	pointLight.quadratic = 0.00009f;
	pointLight.linear = 0.032f;


	SpotLight torch;
	torch.position = camera.position();
	torch.position = camera.front();
	torch.ambient = vec3(0.1f);
	torch.diffuse = vec3(0.8f);
	torch.specular = vec3(0.8f);
	torch.cutOff = cos(radians(12.5f));
	torch.outerCutOff = cos(radians(15.0f));

	Model backpack("../assets/backpack/backpack.obj");

	mat4 view = camera.getViewMatrix();
	mat4 projection(1.0f);
	mat4 model(1.0f);
	float aspect = (float)width / height;

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


		glEnable(GL_DEPTH_TEST);
		defaultShader.setDirectionalLight("uDirectionalLigth", directionalLight);
		model = mat4(1.0f);
		model = scale(model, vec3(0.05f, 0.05f, 0.05f));
		model = translate(model, vec3(10.0f, 0.0f, 0.0f));
		defaultShader.Use();
		defaultShader.setDirectionalLight("directionalLight", directionalLight);
		defaultShader.setPointLight("pointLight", pointLight);
		defaultShader.setMat4f("uModel", model);
		defaultShader.setMat4f("uView", view);
		defaultShader.setMat4f("uProjection", projection);
		defaultShader.setVec3("viewPos", camera.position());
		defaultShader.SetFloat("material.shininess", 128.f);
		backpack.Draw(defaultShader);
		
		glDisable(GL_DEPTH_TEST);
		textureQuadVAO.Bind();
		texturePreview.Use();
		diffuse.Activate(0);
		texturePreview.SetInt("uTexture", 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//main render loop --------------------------------------------------------------------------END

	//delete everything
	texturePreview.Delete();
	defaultShader.Delete();

	textureQuadVAO.Delete();
	diffuse.Delete();
	texturePreview.Delete();
	quadIndices.Delete();

	//clean memory and close the program
	glfwTerminate();
	return 0;
}