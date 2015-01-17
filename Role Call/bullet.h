#pragma once

#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet(float x, float y, float direction, float distance);
	bool Update(sf::RenderWindow* window);
	void Collision(Entity* entity);
private:
	float distance;
};