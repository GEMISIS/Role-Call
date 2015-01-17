#include "main_game.h"
#include "main_menu.h"
#include "game_over.h"
#include "win_screen.h"

#include "main_guy.h"

bool gameOver = false;
float startingX = 1280 / 2;
float startingY = 768 / 2;
std::string nextArea = "test.map";

void main_game::Initialize(sf::RenderWindow* window)
{
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");
	this->score = new Score(*font, 64U);
	this->lives = new Lives(*font, 64U);
	this->lives->setPosition(window->getSize().x - this->lives->getGlobalBounds().width, 0);

	this->pausedText = new sf::Text("Paused\nPress Escape to Quit", *font, 64U);
	this->pausedText->setOrigin(this->pausedText->getGlobalBounds().width / 2, this->pausedText->getGlobalBounds().height / 2);
	this->pausedText->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->paused = false;
	this->enterKey = true;

	manager = new EntityManager();

	map.Load(nextArea);

	this->manager->Add("main_guy", new main_guy(&map, startingX, startingY));
}
void main_game::Update(sf::RenderWindow* window)
{
	if (this->paused)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->paused = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			coreState.SetState(new main_menu());
			return;
		}
	}
	else
	{
		if (!this->manager->Update(window))
		{
			return;
		}
		this->score->Update();
		this->lives->Update();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return) && !this->enterKey)
		{
			this->paused = true;
		}
	}
	if (gameOver || this->lives->Value() <= 0)
	{
		gameOver = false;
		coreState.SetState(new game_over());
		return;
	}
	this->enterKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return);
}
void main_game::Render(sf::RenderWindow* window)
{
	window->draw(map);
	this->manager->Render(window);
	window->draw(*this->score);
	window->draw(*this->lives);

	if (this->paused)
	{
		window->draw(*this->pausedText);
	}
}
void main_game::Destroy(sf::RenderWindow* window)
{
	delete this->score;
	delete this->lives;
	delete this->pausedText;
	delete this->font;

	delete this->manager;
}
