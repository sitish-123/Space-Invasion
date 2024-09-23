#pragma once
#include<map>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"
#include "Star.h"
class Game
{
private:
	//window
	sf::RenderWindow* window;

	
	//resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	std::vector<Star*> stars;
	//Player
	Player* player;

	//Enemies
	float spawnTimer;
	float spawnTimermax;
	std::vector<Enemy*>enemies;
	Enemy* enemy;


	//private functions
	void initwindow();
	void initPlayer();
	void initStars();
	void initTextures();
	void initEnemies();
	
	
public:
	Game();
	virtual ~Game();
	// functions
	void run();

	void updatePollEvents();
	void updateInput();
	void updateEnemies();
	void updateBullets();
	void updateStars();
	void update();
	void render();
	


};

