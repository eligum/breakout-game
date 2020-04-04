#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include "game_level.hpp"

enum GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	GameState		_State;
	bool			_Keys[1024];
	unsigned int	_Width, _Height;
	unsigned int	_CurrentLevel;
	GameLevel		_Levels[10];
public:
	Game(int width, int height);
	~Game();
	void Init();
	void ProcessInput(float dt);
	void UpdateModel(float dt);
	void RenderFrame();
};

#endif