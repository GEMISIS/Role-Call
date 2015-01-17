#include "main_game.h"
#include "main_guy.h"

main_guy::main_guy(Map* map, float x, float y)
{
	this->Load("ship.png");
	this->setPosition(x, y);
	this->map = map;
	this->speed = 1.0f;
}

bool main_guy::Update(sf::RenderWindow* window)
{
	this->velocity.x = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) * this->speed;
	this->velocity.y = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) * this->speed;

	if (this->getPosition().y <= 0)
	{
		nextArea = map->topArea;
		startingX = this->getPosition().x;
		startingY = window->getSize().y - this->getGlobalBounds().height - 32;
		coreState.SetState(new main_game());
		return false;
	}
	if (this->getPosition().y + this->getGlobalBounds().height >= window->getSize().y)
	{
		nextArea = map->bottomArea;
		startingX = this->getPosition().x;
		startingY = 32;
		coreState.SetState(new main_game());
		return false;
	}
	if (this->getPosition().x <= 0)
	{
		nextArea = map->leftArea;
		startingX = window->getSize().x - this->getGlobalBounds().width - 32;
		startingY = this->getPosition().y;
		coreState.SetState(new main_game());
		return false;
	}
	if (this->getPosition().x + this->getGlobalBounds().width >= window->getSize().x)
	{
		nextArea = map->rightArea;
		startingX = 32;
		startingY = this->getPosition().y;
		coreState.SetState(new main_game());
		return false;
	}

	switch (this->map->CheckCollision(this, NONE))
	{
	case 0:
		break;
	case 1:
		this->speed = 1.0f;
		this->setColor(sf::Color::White);
		break;
	case 2:
		this->speed = 0.5f;
		this->setColor(sf::Color::Blue);
		break;
	}

	if (this->map->CheckCollision(this, LEFT) > 2)
	{
		this->move(-abs(this->velocity.x), 0);
	}
	if (this->map->CheckCollision(this, RIGHT) > 2)
	{
		this->move(abs(this->velocity.x), 0);
	}
	if (this->map->CheckCollision(this, UP) > 2)
	{
		this->move(0, abs(this->velocity.y));
	}
	if (this->map->CheckCollision(this, DOWN) > 2)
	{
		this->move(0, -abs(this->velocity.y));
	}

	Entity::Update(window);
	return true;
}

void main_guy::Collision(Entity* entity)
{
}

