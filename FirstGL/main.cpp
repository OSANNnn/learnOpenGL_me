#include <iostream>
#include <map>
#include <glad/glad.h>
#include <glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "io.h"
#include "Shader.hpp"
#include "buffers.hpp"
#include "materials.hpp"
#include "lights.hpp"
#include "model.h"
#include "primitives.h"


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
	
	stbi_set_flip_vertically_on_load(false);

	float quadVertices[] = {
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};


	vec2 translations[100];

	int index = 0;
	float offset = 0.1f;
	for (int y = -10; y < 10; y += 2)
	{
		for (int x = -10; x < 10; x += 2)
		{
			translations[index].x = (float)x / 10.0f + offset;
			translations[index].y = (float)y / 10.0f + offset;
			index++;
		}
	}

	VBO quad;
	VAO vegetationVao;

	vegetationVao.Bind();
	quad.Bind();
	quad.Data(quadVertices, sizeof(quadVertices));
	vegetationVao.SetAttrib(0, 3, 5, 0);
	vegetationVao.SetAttrib(2, 2, 5, 3);
	vegetationVao.setVertexCount(6);
	vegetationVao.UnBind();
	quad.UnBind();

	Texture plant;
	plant.TexData("../assets/textures/grass.png");
	plant.setClamp();

	vector<vec3> vegetation;
	vegetation.push_back(vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(vec3(0.5f, 0.0f, -0.6f));

	Primitives::Cube cube;
	Primitives::Plane plane;

	Model backpack("../assets/backpack/backpack.obj");

	Texture marble; //cube
	marble.TexData("../assets/textures/marble.jpg");
	Texture metal; //floor
	metal.TexData("../assets/textures/metal.png");

	Shader plainTextures("texturePreview.vert", "texturePreview.frag");
	plainTextures.Use();
	plainTextures.SetInt("texture1", 0);

	DirectionalLight sunLight;
	sunLight.direction = vec3(-1.0, -1.0f, 1.0);
	sunLight.ambient = vec3(0.1f);
	sunLight.diffuse = vec3(0.8, 1.0, 1.0);
	sunLight.specular = vec3(0.8, 1.0, 1.0);

	mat4 view = camera.getViewMatrix();
	mat4 projection(1.0f);
	mat4 model(1.0f);
	float aspect = (float)width / height;

	//uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//main render loop -----------------------------------------------------------------------------
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		processInput(window, camera);
		
		projection = perspective(radians(camera.fov()), aspect, 0.1f, 100.0f);
		view = camera.getViewMatrix();

		plainTextures.Use();
		plainTextures.setMat4f("view", view);
		plainTextures.setMat4f("projection", projection);
		plainTextures.SetInt("material.texture_diffuse1", 0);
		plainTextures.setDirectionalLight("directionalLight", sunLight);
		plainTextures.setVec3("viewPos", camera.position());

		metal.Activate(0);
		model = mat4(1.0f);
		plainTextures.setMat4f("model", model);
		plane.Draw();

		marble.Activate(0);
		model = mat4(1.0f);
		model = translate(model, vec3(-1.0f, 0.001f, -1.0f));
		plainTextures.setMat4f("model", model);
		cube.Draw();
		model = mat4(1.0f);
		model = translate(model, vec3(2.0f, 0.001f, 0.0f));
		plainTextures.setMat4f("model", model);
		cube.Draw();

		plant.Activate(0);
		map<float, glm::vec3> sorted;
		for (unsigned int i = 0; i < vegetation.size(); i++)
		{
			float distance = glm::length(camera.position() - vegetation[i]);
			sorted[distance] = vegetation[i];
		}
		for (map<float, vec3>::reverse_iterator it = sorted.rbegin(); it !=
			sorted.rend(); ++it)
		{
			model = mat4(1.0f);
			model = translate(model, it->second);
			plainTextures.setMat4f("model", model);
			vegetationVao.Draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//main render loop --------------------------------------------------------------------------END

	//delete everything
	quad.Delete();
	plainTextures.Delete();
	marble.Delete();
	metal.Delete();

	//clean memory and close the program
	glfwTerminate();
	return 0;
}