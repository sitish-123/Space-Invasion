#include "Game.h"

void Game::initwindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Invasion", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit((int)144);
	this->window->setVerticalSyncEnabled(false);
}
void Game::initPlayer()
{
	this->player = new Player();
	

}

void Game::initStars()
{
	srand(static_cast<unsigned>(time(0))); // Seed random number generator

	int numStars = 100; // Number of stars
	for (int i = 0; i < numStars; ++i)
	{
		float x = static_cast<float>(rand() % this->window->getSize().x);
		float y = static_cast<float>(rand() % this->window->getSize().y);
		float radius = static_cast<float>(rand() % 3 + 1); // Random radius between 1 and 3

		this->stars.push_back(new Star(x, y, radius));
	}
}

void Game::initEnemies()
{
	this->spawnTimer = 0.f; 
	this->spawnTimermax = 50.f;
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");

}

 //con/des
Game::Game()
{
	this->initwindow();
	this->initStars();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
	
}
Game::~Game()
{
	delete this->window;
	delete this->player;
	delete this->enemy;

	//delete textures
	for (auto& i : this->textures)
	{ 
		delete i.second;
	}
	//delete bullets
	for (auto*i : this->bullets)	
	{
		delete i;
	}

	//delete all enemies
	for (auto* i : this->enemies)
	{
		delete i;
	}
	for (auto* i : this->stars) // Clean up stars
	{
		delete i;
	}

}
//functions

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvents()
{ 
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();
	}
}

void Game::updateInput()
{

	// Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->player->move(0.f, 1.f);

	if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()))
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x+32, this->player->getPos().y,0.f,-1.f,5.f));
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->player->canAttack())
	{
		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 32, this->player->getPos().y, 0.f, -1.f, 5.f));

	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimermax)
	{
		// Spawn an enemy and reset the timer
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x, -50.f));  // spawn at random x position
		this->spawnTimer = 0.f;
	}

	for (int i =0; i<this->enemies.size();i++)
	{
		enemies[i]->update();

		//remove enemies at bottom of screen
		if (this->enemies[i]->getbounds().top > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			std::cout << this->enemies.size() << "\n";
		}
	}

}

void Game::updateBullets()
{
	for (auto* bullet : this->bullets)
	{
		unsigned counter = 0;


		bullet->update();

		//bullet culling(top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height <= 0.f)
		{
			//delete bullets
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;

			
		}

		++counter;

	}
}
void Game::updateStars()
{
	for (auto* star : this->stars)
	{
		star->update();
	}
}


void Game::update()
{
	this->updatePollEvents();

	this->updateInput();
	this->updateStars();
	this->player->update();

	this->updateBullets();
	this->updateEnemies();
	
}

 
void Game::render()
{

	this->window->clear(sf::Color::Black);
	for (auto* star : this->stars)
	{
		star->render(*this->window);
	}
	//draw all the stuffs
	this->player->render(*this->window);

	for (auto *bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->window->display();
}






