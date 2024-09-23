
#include "Player.h"


void Player::initVariables()
{
	this->movementSpeed = 2.f;
	this->attackCooldownmax = 10.f;
	this->attackCooldown = this->attackCooldownmax;

}

void Player::initTexture()
{
	if (!this->texture.loadFromFile("Textures/space2.png"))
	{
		std::cout << "Something went wrong:Player" << "\n";
	}

	//load texture from file
}

void Player::initSprite()
{
	//set texture to sprite
	this->sprite.setTexture(this->texture);
	
	// resize
	this->sprite.scale(0.1f, 0.1f);



}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{

	return this->sprite.getPosition();

}

void Player::move(const float dx, const float dy)
{
	sf::Vector2f newPos = this->sprite.getPosition() + sf::Vector2f(this->movementSpeed * dx, this->movementSpeed * dy);

    // Constrain movement within the window bounds
    if (newPos.x < 0)
        newPos.x = 0;
    if (newPos.x > 800 - this->sprite.getGlobalBounds().width) // Assuming window width is 800
        newPos.x = 800 - this->sprite.getGlobalBounds().width;
    if (newPos.y < 0)
        newPos.y = 0;
    if (newPos.y > 600 - this->sprite.getGlobalBounds().height) // Assuming window height is 600
        newPos.y = 600 - this->sprite.getGlobalBounds().height;

    this->sprite.setPosition(newPos);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownmax)
	{
		this->attackCooldown = 0.f;
		
		return true;
	}
	else
	return false;
}

void Player::updateAttack()
{

	if (this->attackCooldown < this->attackCooldownmax)
		this->attackCooldown += 0.5f;

}

//function 
void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
} 
 