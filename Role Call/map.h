#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "entity.h"

typedef enum
{
	NONE = -1,
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
}Direction;

class Map : public sf::Sprite
{
public:
	Map();

	void Load(std::string filename);

	virtual void Update(sf::RenderWindow* window);

	int CheckCollision(Entity* entity, Direction direction);

	std::string topArea, bottomArea, leftArea, rightArea;

	~Map();
protected:
	std::string tileSet;
	int width = 0;
	int height = 0;
	int tileWidth = 0;
	int tileHeight = 0;
	int* data;
private:
	sf::Texture* texture;
	sf::Image* tileSetTexture;
};

