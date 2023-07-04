#include "projectile.h"
#include <iostream>

Projectile::Projectile(float x, float y, float velocityX,  float velocityY, sf::Texture* texture)
    : x(x), y(y), texture(texture), hitbox(x, y, width, height){
    
    
    if (texture == nullptr) {
        std::cout << "Erro: Ponteiro de textura nulo!" << std::endl;
        return;
    }

    sprite.setTexture(*texture);
    setPosition(x, y);

    setvelocityY(velocityY);
    setvelocityX(velocityX);

}

void Projectile::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Projectile::update(float deltaTime)
{
    y += velocityY * deltaTime;
    x += velocityX * deltaTime;
    sprite.setPosition(x, y);
    hitbox.update(x, y);
}



const Hitbox& Projectile::getHitbox() const
{
    return hitbox;
}

bool Projectile::isOutOfScreen() const
{
    return y < 0.0f;
}

void Projectile::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);
    hitbox.update(x, y);
}


void Projectile::setvelocityY(float velocityY){
    this->velocityY = velocityY;
}
void Projectile::setvelocityX(float velocityX){
    this->velocityX = velocityX;
}
