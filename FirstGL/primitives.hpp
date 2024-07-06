#pragma once

#include "buffers.hpp"

namespace Primitives
{
	class Cube
	{
	private:
		float vertices[36*8] = {
		//backface pos             normals			     TexCoords
			-0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // bottom-left
			 0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f, // top-right
			-0.5f, -0.5f, -0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f, // bottom-left
			-0.5f,  0.5f, -0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f, // top-left
		// front face									 
			-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // bottom-left
			 0.5f, -0.5f,  0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f,  0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f, // top-right
			 0.5f,  0.5f,  0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f, // top-right
			-0.5f,  0.5f,  0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f, // top-left
			-0.5f, -0.5f,  0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f, // bottom-left
		// left face									 
			-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // top-right
			-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // top-left
			-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // bottom-left
			-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // bottom-left
			-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // bottom-right
			-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // top-right
		// right face									 
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // top-left
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // bottom-right
			 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f, // bottom-right
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f, // top-left
			 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f, // bottom-left
		// bottom face									 
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // top-right
			 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f, // top-left
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // bottom-left
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f, // bottom-left
			-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f, // bottom-right
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f, // top-right
		// top face
			-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // top-left
			 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // bottom-right
			 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f, // top-right
			 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f, // bottom-right
			-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f, // top-left
			-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f, // bottom-left
		};
		const int verticesNr = 36;
		Buffers::VBO VBO;
		Buffers::VAO VAO;

		void init()
		{
			VAO.Bind();
			VBO.Bind();
			VBO.Data(vertices, sizeof(vertices));
			VAO.SetAttrib(0, 3, 8, 0);
			VAO.SetAttrib(1, 3, 8, 3);
			VAO.SetAttrib(2, 2, 8, 6);
			VAO.setVertexCount(verticesNr);
			VAO.UnBind();
			VBO.UnBind();
		}

	public:
		Cube()
		{
			init();
		};
		void Draw()
		{
			VAO.Draw();
		}
		~Cube()
		{
			VAO.Delete();
			VBO.Delete();
		}
	};

	class SkyBox
	{
	private:
		float vertices[3*36] = {
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};
		const int verticesNr = 36;
		Buffers::VBO VBO;
		Buffers::VAO VAO;

		void init()
		{
			VAO.Bind();
			VBO.Bind();
			VBO.Data(vertices, sizeof(vertices));
			VAO.SetAttrib(0, 3, 3, 0);
			VAO.setVertexCount(verticesNr);
			VAO.UnBind();
			VBO.UnBind();
		}
	public:
		SkyBox()
		{
			init();
		};
		void Draw()
		{
			VAO.Draw();
		}
		~SkyBox()
		{
			VAO.Delete();
			VBO.Delete();
		}
	};

	class Quad
	{
	private:
		float vertices[6*5] = {
		-0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.0f,  1.0f,  1.0f,

		-0.5f,  0.5f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.0f,  1.0f,  0.0f
		};
		const int verticesNr = 6;
		Buffers::VBO VBO;
		Buffers::VAO VAO;

		void init()
		{
			VAO.Bind();
			VBO.Bind();
			VBO.Data(vertices, sizeof(vertices));
			VAO.SetAttrib(0, 3, 5, 0);
			VAO.SetAttrib(2, 2, 5, 3);
			VAO.setVertexCount(verticesNr);
			VAO.UnBind();
			VBO.UnBind();
		}
	public:
		Quad()
		{
			init();
		};
		void Draw()
		{
			VAO.Draw();
		}
		~Quad()
		{
			VAO.Delete();
			VBO.Delete();
		}
	};

	class Triangle
	{

	};

	class FrameQuad
	{
	private:
		float vertices[5 * 6] =
		{
			-1.0,  1.0,  0.0,  0.0, 1.0,
			-1.0, -1.0,  0.0,  0.0, 0.0,
			 1.0, -1.0,  0.0,  1.0, 0.0,
							   
			 1.0, -1.0,  0.0,  1.0, 0.0,
			 1.0,  1.0,  0.0,  1.0, 1.0,
			-1.0,  1.0,  0.0,  0.0, 1.0,
		};

		const int verticesNr = 6;
		Buffers::VBO VBO;
		Buffers::VAO VAO;

		void init()
		{
			VAO.Bind();
			VBO.Bind();
			VBO.Data(vertices, sizeof(vertices));
			VAO.SetAttrib(0, 3, 5, 0);
			VAO.SetAttrib(1, 2, 5, 3);
			VAO.setVertexCount(verticesNr);
			VAO.UnBind();
			VBO.UnBind();
		}

	public:
		FrameQuad()
		{
			init();
		};
		void Draw()
		{
			VAO.Draw();
		}
		~FrameQuad()
		{
			VAO.Delete();
			VBO.Delete();
		}
	};

	class Plane
	{
	private:
		float vertices[8*6] = {
		//   positions			  normals				texCoords
			 5.0f, -0.5f, -5.0f,  0.0f,  1.0f,  0.0f,   2.0f, 2.0f,
			 5.0f, -0.5f,  5.0f,  0.0f,  1.0f,  0.0f,   2.0f, 0.0f,
			-5.0f, -0.5f, -5.0f,  0.0f,  1.0f,  0.0f,   0.0f, 2.0f,

			-5.0f, -0.5f, -5.0f,  0.0f,  1.0f,  0.0f,   0.0f, 2.0f,
			 5.0f, -0.5f,  5.0f,  0.0f,  1.0f,  0.0f,   2.0f, 0.0f,
			-5.0f, -0.5f,  5.0f,  0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
		};
		const int verticesNr = 6;
		Buffers::VBO VBO;
		Buffers::VAO VAO;

		void init()
		{
			VAO.Bind();
			VBO.Bind();
			VBO.Data(vertices, sizeof(vertices));
			VAO.SetAttrib(0, 3, 8, 0);
			VAO.SetAttrib(1, 3, 8, 3);
			VAO.SetAttrib(2, 2, 8, 6);
			VAO.setVertexCount(verticesNr);
			VAO.UnBind();
			VBO.UnBind();
		}

	public:
		Plane()
		{
			init();
		};
		void Draw()
		{
			VAO.Draw();
		}
		~Plane()
		{
			VAO.Delete();
			VBO.Delete();
		}
	};
}



