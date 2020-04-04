#include "game.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"

SpriteRenderer *Renderer;

Game::Game(int width, int height)
	:
	_State(GAME_ACTIVE),
	_Keys(),
	_Width(width),
	_Height(height),
	_CurrentLevel(1),
	_Levels()
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

	// Load textures
	ResourceManager::LoadTexture("data/img/background.jpg", true, "background");
	ResourceManager::LoadTexture("data/img/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("data/img/block.png", true, "block");
	ResourceManager::LoadTexture("data/img/block_solid.png", true, "block_solid");
	// Load levels
	GameLevel level_1; level_1.Load("data/levels/L01.txt", _Width, _Height * 0.5);
}

void Game::ProcessInput(float dt)
{

}

void Game::UpdateModel(float dt)
{

}

void Game::RenderFrame()
{
	if (_State == GAME_ACTIVE)
	{
		Renderer->DrawSprite(ResourceManager::GetTexture("background"),
							 glm::vec2(0, 0),
							 glm::vec2(_Width, _Height));
		_Levels[_CurrentLevel - 1].Draw(*Renderer);
	}
}