#pragma once

#include "entity.h"

class main_guy : public Entity
{
public:
	main_guy();
	void Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
private:
};