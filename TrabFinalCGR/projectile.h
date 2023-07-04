#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "hitbox.h"

class Projectile {
public:
    Projectile(float x, float y, float velocityX, float velocityY,sf::Texture* texture);
    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime);
    void setPosition(float x, float y);
    const Hitbox& getHitbox() const;
    bool isOutOfScreen();
    void setvelocityY(float velocityY);
    void setvelocityX(float velocityX);
private:
    float x, y;
    float velocityY; // Velocidade vertical (direção para cima)
    float velocityX; 
    float width = 20;
    float height = 20;
    sf::Texture* texture;
    sf::Sprite sprite;
    Hitbox hitbox;
};

#endif // PROJECTILE_H
