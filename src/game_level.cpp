#include "game_level.hpp"
#include <fstream>
#include <sstream>

void GameLevel::Load(const char *file_path, unsigned int levelWidth, unsigned int levelHeight)
{
	// Clear old data
	_Bricks.clear();
	// Load from file
	unsigned int tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file_path);
	Matrixui tileData;
	if (fstream)
	{
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode)
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0)
			init(tileData, levelWidth, levelHeight);
	}
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
	for (GameObject& brick : _Bricks)
		if (!brick._IsDestroyed)
			brick.Draw(renderer);
}

bool GameLevel::IsCompleted() const
{
	for (const GameObject& tile : _Bricks)
		if (!tile._IsSolid and !tile._IsDestroyed)
			return false;
	return true;
}

void GameLevel::init(Matrixui tileData, unsigned int levelWidth, unsigned int levelHeight)
{
	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();
	float unit_width = levelWidth / (float)width;
	float unit_height = levelHeight / (float)height;
	// Initialize level tiles based on tileData
	for (unsigned int y = 0; y < height; ++y)
	{
		for (unsigned int x = 0; x < width; ++x)
		{
			if (tileData[y][x] == 1)	// Solid
			{
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f));
				obj._IsSolid = true;	// By default it is false
				_Bricks.push_back(obj);
			}
			else if (tileData[y][x] > 1)
			{
				glm::vec3 color(1.0f);	// Default (leave untouched texture color)
				if (tileData[y][x] == 2)
					color = glm::vec3(0.1f, 0.6f, 0.9f);
				else if (tileData[y][x] == 3)
					color = glm::vec3(0.0f, 0.7f, 0.0f);
				else if (tileData[y][x] == 4)
					color = glm::vec3(0.8f, 0.8f, 0.4f);
				else if (tileData[y][x] == 5)
					color = glm::vec3(1.0f, 0.5f, 0.0f);
				
				glm::vec2 pos(unit_width * x, unit_height * y);
				glm::vec2 size(unit_width, unit_height);
				GameObject obj(pos, size, ResourceManager::GetTexture("block"), color);
				_Bricks.push_back(obj);
			}
		}
	}
}