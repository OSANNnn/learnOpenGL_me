#include "model.hpp"

std::vector<Buffers::Texture> textures_loaded;

void Model::Draw(Shader& shader)
{
	for (auto& mesh : Meshes)
		mesh.Draw(shader);
}

void Model::Delete()
{
	for (auto& texture : textures_loaded)
	{
		texture.Delete();
	}

	for (Mesh& mesh : Meshes)
	{
		mesh.Delete();
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	std::cout << "Loading model: \"" << path << "\"" << std::endl;
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}

	Directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	std::cout << "MeshesNr: " << node->mNumMeshes << std::endl;
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{	
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		Meshes.push_back(processMesh(mesh, scene));
	}

	std::cout << "ChildNr: " << node->mNumChildren << std::endl;
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		std::cout << "Processing meshes:" << i << std::endl;
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Buffers::Texture> textures;
	std::cout << "Loading vertex data..." << std::endl;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 temp(0.0f);

		temp.x = mesh->mVertices[i].x;
		temp.y = mesh->mVertices[i].y;
		temp.z = mesh->mVertices[i].z;
		vertex.Position = temp;

		temp.x = mesh->mNormals[i].x;
		temp.y = mesh->mNormals[i].y;
		temp.z = mesh->mNormals[i].z;
		vertex.Normal = temp;

		if (mesh->mTextureCoords[0])
		{	
			temp.x = mesh->mTextureCoords[0][i].x;
			temp.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = glm::vec2(temp.x, temp.y);
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f);
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Buffers::Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<Buffers::Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		std::vector<Buffers::Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normals");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	}

	return Mesh(vertices, indices, textures);
}

std::vector<Buffers::Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Buffers::Texture> temp;
	
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path().data(), str.C_Str()) == 0)
			{
				temp.push_back(textures_loaded[j]);
				skip = true;
			}
		}
		
		if (!skip)
		{
			std::cout << "Texture found for model: " << typeName << " \"" << Directory << "/" << str.C_Str() << "\"" << std::endl;
			Buffers::Texture texture(typeName);
			texture.TexData(str.C_Str(), Directory);
			texture.setPath(str.C_Str());
			temp.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}

	return temp;
}
