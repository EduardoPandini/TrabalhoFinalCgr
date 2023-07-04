#include "enemy.h"
#include <iostream>
#include <cstdlib> // Para usar rand() e srand()

Enemy::Enemy(float x, float y, sf::Texture* texture)
    : x(x), y(y), texture(texture), hitbox(x, y, width, height), cantShoot(true), shootTimer(0) {
    
    if (texture == nullptr) {
        std::cout << "Erro: Ponteiro de textura nulo!" << std::endl;
        return;
    }

    sprite.setTexture(*texture);
    setPosition(x, y);
}


void Enemy::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

void Enemy::update(float deltaTime) {
    // Atualizar a posição do inimigo com base na velocidade (o inimigo está parado no exemplo)
    // Você pode adicionar lógica para o movimento do inimigo aqui
    float dx = 0.0f;
    float dy = 1.0f;

    // Movimento lateral aleatório
    float maxHorizontalSpeed = 50.0f; // Velocidade máxima horizontal
    float chanceToChangeDirection = 0.01f; // Probabilidade de mudar de direção

    if (rand() / static_cast<float>(RAND_MAX) < chanceToChangeDirection) {
        
    velocityX = (rand() / static_cast<float>(RAND_MAX)) * maxHorizontalSpeed * 8 - maxHorizontalSpeed * 8; // Gera um valor aleatório entre -maxHorizontalSpeed e maxHorizontalSpeed
    }

    dx += velocityX * deltaTime;

    // Atualizar posição vertical
    x += dx;
    y += dy;

    // Limitar a posição horizontal dentro da janela
    float windowWidth = 1360.0f; // Largura da janela (ajuste para o tamanho desejado)
    if (x < 0) {
        x = 0;
        velocityX = -velocityX; // Inverte a direção ao atingir a borda esquerda
    } else if (x + width > windowWidth) {
        x = windowWidth - width;
        velocityX = -velocityX; // Inverte a direção ao atingir a borda direita
    }

    sprite.setPosition(x, y);
    hitbox.update(x, y); // Atualiza a posição da hitbox com a nova posição do inimigo
    if (cantShoot) {
            shootTimer += deltaTime;
            if (shootTimer >= shootTime) {
                cantShoot = false;
                shootTimer = 0.0f;
            }
        }
}

bool Enemy::pew(){
    if (!cantShoot){
        cantShoot = true;
        return true;
    }else{
        return false;
    }
}

void Enemy::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    sprite.setPosition(x, y);
    hitbox.update(x, y);
}

bool Enemy::isOutOfScreen() const {
    return y > 1000.0f; // Define o limite inferior para remover o inimigo da tela
}

const Hitbox& Enemy::getHitbox() const {
    return hitbox;
}

float Enemy::getX(){
    return x;
}

float Enemy::getY(){
    return y;
}

float Enemy::getWidth(){
    return width;
}
float Enemy::getHeight(){
    return height;
}