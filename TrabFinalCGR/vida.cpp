#include "vida.h"
#include <iostream>
#include <cstdlib> // Para usar rand() e srand()

#define WINDOW_H 720
#define WINDOW_W 1280

Vida::Vida(float x, float y, sf::Texture* texture)
    : x(x), y(y), texture(texture), hitbox(x, y, width, height) {
    
    if (texture == nullptr) {
        std::cout << "Erro: Ponteiro de textura nulo!" << std::endl;
        return;
    }

    sprite.setTexture(*texture);
    setPosition(x, y);
}


void Vida::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Vida::update(float deltaTime) {
    
    float dy = 1.0f;
    dy += velocityY + deltaTime;
    y += dy;
    sprite.setPosition(x, y);
    hitbox.update(x, y); // Atualiza a posição da hitbox com a nova posição do hp
}

void Vida::setPosition(float x, float y) {
   
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);
    hitbox.update(x, y);
}

bool Vida::isOutOfScreen() const {
    return y > WINDOW_H; // Define o limite superior para remover o inimigo da tela
}

const Hitbox& Vida::getHitbox() const {
    return hitbox;
}
