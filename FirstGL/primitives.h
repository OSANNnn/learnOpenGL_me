#pragma once

#include "buffers.hpp"

namespace Primitives
{
	class Cube
	{
	private:
		float cubeVertices[36*5] = {
			// back face
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top-left
			// front face
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, // top-right
			 0.5f,  0.5f, 0.5f, 1.0f, 1.0f, // top-right
			-0.5f,  0.5f, 0.5f, 0.0f, 1.0f, // top-left
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
			// left face
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // top-right
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-left
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-right
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // top-right
			// right face
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // top-left
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
			 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-right
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // top-left
			 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-left
			 // bottom face
			 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
			  0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top-left
			  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom-left
			  0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom-left
			 -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // bottom-right
			 -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
			 // top face
			 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
			  0.5f, 0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
			  0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // top-right
			  0.5f, 0.5f,  0.5f, 1.0f, 0.0f, // bottom-right
			 -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
			 -0.5f, 0.5f,  0.5f, 0.0f, 0.0f, // bottom-left
		};
		const int verticesNr = 36;
		Buffers::VBO cubeVBO;
		Buffers::VAO cubeVAO;

		void init()
		{
			cubeVAO.Bind();
			cubeVBO.Bind();
			cubeVBO.Data(cubeVertices, sizeof(cubeVertices));
			cubeVAO.SetAttrib(0, 3, 5, 0);
			cubeVAO.SetAttrib(1, 2, 5, 3);
			cubeVAO.setVertexCount(verticesNr);
			cubeVAO.UnBind();
			cubeVBO.UnBind();
		}

	public:
		Cube()
		{
			init();
		};
		void Draw()
		{
			cubeVAO.Draw();
		}
		~Cube()
		{
			cubeVAO.Delete();
			cubeVBO.Delete();
		}
	};

	class Quad
	{
	};

	class Triangle
	{

	};

	class Plane
	{

	};
}



