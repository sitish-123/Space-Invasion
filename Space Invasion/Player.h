#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;
    float attackCooldown;
    float attackCooldownmax;

    void initVariables();
    void initTexture();
    void initSprite();

public:
    Player();
    virtual ~Player();

    const sf::Vector2f& getPos() const;
    sf::FloatRect getGlobalBounds() const {
        return this->sprite.getGlobalBounds();
    }

    void move(const float dx, const float dy);
    const bool canAttack();
    void updateAttack();
    void update();
    void render(sf::RenderTarget& target);
};
