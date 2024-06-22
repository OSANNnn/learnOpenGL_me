#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>
#include "Shader.hpp"
#include "Mesh.hpp"
#include "buffers.hpp"


class Model
{
public:
	Model(char* path) { loadModel(path); }
	void Draw(Shader& shader);

private:
	std::vector<Mesh> Meshes;
	std::string Directory;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Buffers::Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

};

