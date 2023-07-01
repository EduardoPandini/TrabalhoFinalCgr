#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "hitbox.h"

class Projectile {
public:
    Projectile(float x, float y, sf::Texture* texture);
    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime);
    void setPosition(float x, float y);
    const Hitbox& getHitbox() const;
    bool isOutOfScreen() const;

private:
    float x, y;
    float velocityY = -10; // Velocidade vertical (direção para cima)
    float width = 20;
    float height = 20;
    sf::Texture* texture;
    sf::Sprite sprite;
    Hitbox hitbox;
};

#endif // PROJECTILE_H
