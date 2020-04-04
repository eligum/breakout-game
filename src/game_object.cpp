#include "game_object.hpp"

GameObject::GameObject()
	:
	_Position(0, 0),
	_Size(1, 1),
	_Velocity(0.0f),
	_Color(1.0f),
	_Rotation(0.0f),
	_IsSolid(false),
	_IsDestroyed(false)
{}

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec1 velocity)
	:
	_Position(pos),
	_Size(size),
	_Velocity(velocity),
	_Color(color),
	_Rotation(0.0f),
	_IsSolid(false),
	_IsDestroyed(false)
{}

void GameObject::Draw(SpriteRenderer& renderer)
{
	renderer.DrawSprite(_Sprite, _Position, _Size, _Rotation, _Color);
}