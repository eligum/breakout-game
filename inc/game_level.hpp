#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "game_object.hpp"
#include "sprite_renderer.hpp"
#include "resource_manager.hpp"
#include <vector>

typedef std::vector<std::vector<unsigned int>> Matrixui;

class GameLevel
{
public:
	std::vector<GameObject> _Bricks;
public:
	GameLevel() {}
	/* Load level from file */
	void LoadLevel(const char *file_path, unsigned int lvlWidth, unsigned int  lvlHeight);
	/* Render level */
	void Draw(SpriteRenderer& renderer);
	/* Check if level is completed, all non-solid bricks are destroyed */
	bool IsCompleted() const;
private:
	/* Initialize level from tile data */
	void init(Matrixui tileData, unsigned int lvlWidth, unsigned int lvlHeight);
};

#endif