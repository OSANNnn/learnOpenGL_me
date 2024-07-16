#include <iostream>
#include <map>
#include <glad/glad.h>
#include <glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "io.h"
#include "buffers.hpp"
#include "FBO.hpp"
#include "Shader.hpp"
#include "primitives.hpp"
#include "materials.hpp"
#include "lights.hpp"
#include "model.hpp"

using namespace std;
using namespace Buffers;
using namespace glm;

//canvas size
unsigned int width = 800;
unsigned int height = 600;

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

	vector<std::string> faces {
		"../assets/textures/skybox/right.jpg",
		"../assets/textures/skybox/left.jpg",
		"../assets/textures/skybox/top.jpg",
		"../assets/textures/skybox/bottom.jpg",
		"../assets/textures/skybox/front.jpg",
		"../assets/textures/skybox/back.jpg"
	};

	vector<vec3> vegetation;
	vegetation.push_back(vec3(-1.0f, 0.0f, -0.48f));
	vegetation.push_back(vec3(2.0f, 0.0f, 0.51f));
	vegetation.push_back(vec3(0.5f, 0.0f, 0.7f));
	vegetation.push_back(vec3(0.2f, 0.0f, -2.3f));
	vegetation.push_back(vec3(1.0f, 0.0f, -0.6f));

	Primitives::SkyBox skyboxCube;
	Primitives::Cube cube;
	Primitives::Plane plane;
	Primitives::Quad vegetationQuad;
	Primitives::FrameQuad frame;
	//Model backPack("../assets/backpack/backpack.obj");
	FBO framebuffer(800, 600);


	CubeMap skyboxTex(faces);
	Texture marble; //cube
	marble.TexData("../assets/textures/marble.jpg");
	Texture metal; //floor
	metal.TexData("../assets/textures/metal.png");
	Texture plant;
	plant.TexData("../assets/textures/grass.png");
	plant.setClamp();

	Shader skyboxShader("skybox.vert", "skybox.frag");
	skyboxShader.Use();
	skyboxShader.SetInt("skybox", 0);
	Shader plainTextures("texturePreview.vert", "texturePreview.frag");
	plainTextures.Use();
	plainTextures.SetInt("texture1", 0);
	Shader testShader("refraction.vert", "refraction.frag");
	testShader.Use();
	testShader.SetInt("skybox", 0);
	Shader frameBufferShader("frameBuffer.vert", "blur.frag");
	frameBufferShader.Use();
	frameBufferShader.SetInt("bufferTex", 0);
	frameBufferShader.SetFloat("blurStrenght", 16.0f);

	vec3 lightCol(1.0, 1.0, 0.99);
	DirectionalLight sunLight(vec3(1.0, -1.0f, -1.0), lightCol, vec3(0.9f));

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

		processInput(window, camera);
		

		framebuffer.Bind();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		projection = perspective(radians(camera.fov()), aspect, 0.1f, 100.0f);
		view = camera.getViewMatrix();

		testShader.Use();
		testShader.setMat4f("view", view);
		testShader.setMat4f("projection", projection);
		testShader.setVec3("viewPos", camera.position());
		skyboxTex.Activate(0);
		model = mat4(1.0);
		model = translate(model, vec3(0.0f, 1.0f, 0.0f));
		//model = rotate(model, radians((float)glfwGetTime() * 5.0f), vec3(0.0f, 1.0f, 0.0f));
		model = scale(model, vec3(0.2f));
		testShader.setMat4f("model", model);
		cube.Draw();

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

		glDepthFunc(GL_LEQUAL);
		skyboxShader.Use();
		view = mat4(mat3(camera.getViewMatrix()));
		skyboxShader.setMat4f("view", view);
		skyboxShader.setMat4f("projection", projection);
		skyboxTex.Activate(0);
		skyboxCube.Draw();
		glDepthFunc(GL_LESS);

		plainTextures.Use();
		plant.Activate(0);
		view = camera.getViewMatrix();
		map<float, vec3> sorted;
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
			vegetationQuad.Draw();
		}
		framebuffer.UnBind();

		framebuffer.Render(frameBufferShader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//main render loop --------------------------------------------------------------------------END

	//delete everything
	plainTextures.Delete();
	testShader.Delete();
	marble.Delete();
	metal.Delete();
	framebuffer.Delete();

	//clean memory and close the program
	glfwTerminate();
	return 0;
}