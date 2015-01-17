#include "bullet.h"

Bullet::Bullet(float x, float y, float direction, float distance)
{
	this->active = 1;
	this->groupId = 2;
	this->velocity.x = cos(direction / 180.0f * 3.14f);
	this->velocity.y = sin(direction / 180.0f * 3.14f);
	this->setPosition(x - this->getGlobalBounds().width / 2, y - this->getGlobalBounds().height / 2);
	this->distance = distance;
}

bool Bullet::Update(sf::RenderWindow* window)
{
	if (this->getPosition().y <= 0 || this->getPosition().y + this->getGlobalBounds().height >= window->getSize().y)
	{
		this->Destroy();
	}
	this->distance -= sqrt(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
	if (this->distance <= 0)
	{
		this->Destroy();
	}
	Entity::Update(window);
	return true;
}

void Bullet::Collision(Entity* entity)
{
}
