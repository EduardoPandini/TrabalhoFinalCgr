#ifndef VIDA_H
#define VIDA_H

#include <SFML/Graphics.hpp>
#include "hitbox.h"

class Vida {
public:
    Vida(float x, float y, sf::Texture* texture);
    void draw(sf::RenderWindow& window) const;
    void update(float deltaTime);
    void setPosition(float x, float y);
    const Hitbox& getHitbox() const;
    bool isOutOfScreen() const;

    

private:
    float x, y;
    float width = 200;
    float height = 200;
    sf::Texture* texture;
    sf::Sprite sprite;
    Hitbox hitbox;
    float velocityY = 100; // Velocidade vertical 
    void updateHorizontalMovement();
};

#endif // VIDA_H
