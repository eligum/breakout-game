#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"

SpriteRenderer *Renderer;

Game::Game(int width, int height)
	:
	_State(GAME_ACTIVE),
	_Keys(),
	_Width(width),
	_Height(height)
{}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	ResourceManager::LoadShader("data/shaders/sprite.vert", "data/shaders/sprite.frag", nullptr, "sprite");
	glm::mat4 projection = glm::ortho(0.0f, (float)_Width, (float)_Height, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	ResourceManager::LoadTexture("data/img/awesomeface.png", true, "face");
}

void Game::ProcessInput(float dt)
{

}

void Game::UpdateModel(float dt)
{

}

void Game::RenderFrame()
{
	Renderer->DrawSprite(ResourceManager::GetTexture("face"),
						 glm::vec2(200, 150),
						 glm::vec2(400, 300),
						 0.0f,
						 glm::vec3(0.0f, 0.0f, 1.0f));
}