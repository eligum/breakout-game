#include "resource_manager.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include "stb_image.h"

// Instantiate static variables
std::map<std::string, Shader>	ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const char *vert_shader_path, const char *frag_shader_path, const char *geom_shader_path, std::string name)
{
	Shaders[name] = loadShaderFromFile(vert_shader_path, frag_shader_path, geom_shader_path);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name)
{
	/* Careful! This functions asumes that specified shader exists! */
	return Shaders[name];
}

Texture2D ResourceManager::LoadTexture(const char *file_path, bool alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file_path, alpha);
	return Textures[name];
}

Texture2D ResourceManager::GetTexture(std::string name)
{
	/* Careful! This function asumes that specified texture exists! */
	return Textures[name];
}

void ResourceManager::Clean()
{
	for (auto iter : Shaders)
		glDeleteProgram(iter.second._ID);
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second._ID);
}


Shader ResourceManager::loadShaderFromFile(const char *vert_shader_path, const char *frag_shader_path, const char *geom_shader_path)
{
	/* Read shaders source code and convert it into a C-like string */
	std::string vert_code;
	std::string frag_code;
	std::string geom_code;
	std::ifstream vert_shader_file;
	std::ifstream frag_shader_file;
	try
	{
		vert_shader_file.open(vert_shader_path);
		frag_shader_file.open(frag_shader_path);
		std::stringstream vert_stream;
		std::stringstream frag_stream;
		// read file contents
		vert_stream << vert_shader_file.rdbuf();
		frag_stream << frag_shader_file.rdbuf();
		// close file handlers
		vert_shader_file.close();
		frag_shader_file.close();
		// convert them into strings
		vert_code = vert_stream.str();
		frag_code = frag_stream.str();
		/* If geometry shader source is given */
		if (geom_shader_path != nullptr)
		{
			std::ifstream geom_shader_file;
			geom_shader_file.open(geom_shader_path);
			std::stringstream geom_stream;
			geom_stream << geom_shader_file.rdbuf();
			geom_shader_file.close();
			geom_code = geom_stream.str();
		}
	}
	catch(const std::exception& e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	/* Convert strings into C-like strings */
	const char *vert_source = vert_code.c_str();
	const char *frag_source = frag_code.c_str();
	const char *geom_source = geom_code.c_str();
	/* Create shader object from source code */
	Shader shader;
	shader.Compile(vert_source, frag_source, (geom_shader_path != nullptr) ? geom_source : nullptr);
	return shader;
}


Texture2D ResourceManager::loadTextureFromFile(const char *file_path, bool alpha)
{
	/* Create texture object */
	Texture2D texture;
	if (alpha)
	{
		texture._Internal_Format = GL_RGBA8;
		texture._Image_Format = GL_RGBA;
	}
	/* Load image and generate texture */
	stbi_set_flip_vertically_on_load(1);
	int width, height;
	byte *image = stbi_load(file_path, &width, &height, 0, (texture._Image_Format == GL_RGBA) ? 4 : 3);
	texture.Generate(width, height, image);
	/* Free image data */
	stbi_image_free(image);
	return texture;
}