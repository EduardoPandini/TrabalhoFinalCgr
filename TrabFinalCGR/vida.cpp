#include "vida.h"
#include <iostream>
#include <cstdlib> // Para usar rand() e srand()

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
    // Atualizar a posição do inimigo com base na velocidade (o inimigo está parado no exemplo)
    // Você pode adicionar lógica para o movimento do inimigo aqui
    float dx = 0.0f;
    float dy = 1.0f;
    x += dx;
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
    return y > 1000.0f; // Define o limite superior para remover o inimigo da tela
}

const Hitbox& Vida::getHitbox() const {
    return hitbox;
}
