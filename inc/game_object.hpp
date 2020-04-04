#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>

#include "texture2D.hpp"
#include "sprite_renderer.hpp"

/* Container object for holding all state relevant for a single
game object entity. Each object in the game likely needs the
minimal of state as described within GameObject. */
class GameObject
{
public:
	glm::vec2	_Position, _Size, _Velocity;
	glm::vec3	_Color;
	float		_Rotation;
	bool 		_IsSolid;
	bool		_IsDestroyed;
	Texture2D	_Sprite;
public:
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec1 velocity = glm::vec2(0.0f, 0.0f));
	virtual void Draw(SpriteRenderer& renderer);
};

#endif