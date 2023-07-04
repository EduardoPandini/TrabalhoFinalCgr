#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "hitbox.h"

class Enemy {
public:
    Enemy(float x, float y, sf::Texture* texture);
    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime);
    void setPosition(float x, float y);
    const Hitbox& getHitbox() const;
    bool isOutOfScreen() const;
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    bool pew();

private:
    float x, y;
    float width = 100;
    float height = 100;
    sf::Texture* texture;
    sf::Sprite sprite;
    Hitbox hitbox;
    float velocityX; // Velocidade lateral do inimigo
    float minVelocityX = -100.0f; // Velocidade mínima lateral
    float maxVelocityX = 100.0f;
    float shootTime = 3;
    float shootTimer = 0;
    bool cantShoot;
    void updateHorizontalMovement();
};

#endif // ENEMY_H
