#include "projectile.h"
#include <iostream>

Projectile::Projectile(float x, float y, sf::Texture* texture)
    : x(x), y(y), texture(texture), hitbox(x, y, width, height){
    
    
    if (texture == nullptr) {
        std::cout << "Erro: Ponteiro de textura nulo!" << std::endl;
        return;
    }

    sprite.setTexture(*texture);
    setPosition(x, y);

}

void Projectile::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Projectile::update(float deltaTime)
{
    y += velocityY * deltaTime;
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