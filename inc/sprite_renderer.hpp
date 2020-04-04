#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"
#include "texture2D.hpp"

class SpriteRenderer
{
public:
	/* Constructor, inits shaders and shapes */
	SpriteRenderer(const Shader& shader);
	~SpriteRenderer();
	void DrawSprite(const Texture2D& texture,
					glm::vec2 position,
					glm::vec2 size = glm::vec2(10.0f, 10.0f),
					float rotate = 0.0f,
					glm::vec3 color = glm::vec3(1.0f));
private:
	Shader _shader;
	unsigned int _quadVAO;
private:
	void initRenderData();
};

#endif