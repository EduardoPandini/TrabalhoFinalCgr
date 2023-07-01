#include "player.h"
#include <iostream>
#include "enemy.h"
#include <unistd.h> // Para usar getcwd()


std::string currentWorkingDirectory(getcwd(NULL, 0));
std::string spritesFolderPath = "/home/pandini/Desktop/TrabFinalCGR/sprites/player/";




Player::Player(float x, float y, const std::string& filename)
    : x(x), y(y), hitbox(x, y, width, height), isFacingRight(true), vida(3), isInvulnerable(false), invulnerabilityTime(2.0f), invulnerabilityTimer(0.0f), shootTimer(0.0f){
    
    if (!texture.loadFromFile(filename)) {
        std::cout << "Erro ao carregar a textura do jogador!" << std::endl;
    }

    // Carregar as texturas do jogador virado para a esquerda, para a direita e em estado de repouso
    if (!textureLeft.loadFromFile(spritesFolderPath + "playerLeft.png")) {
        std::cout << "Erro ao carregar a textura do jogador virado para a esquerda!" << std::endl;
    }

    if (!textureRight.loadFromFile(spritesFolderPath + "playerRight.png")) {
        std::cout << "Erro ao carregar a textura do jogador virado para a direita!" << std::endl;
    }

    if (!textureIdle.loadFromFile(spritesFolderPath + "playerFront.png")) {
        std::cout << "Erro ao carregar a textura do jogador em estado de repouso!" << std::endl;
    }

    sprite.setTexture(texture); // Definir a textura inicial para o jogador
}


void Player::move(float dx, float dy) {
    x += dx;
    y += dy;
    hitbox.update(x, y); // Atualiza a posição da hitbox
    sprite.setPosition(x, y); // Atualiza a posição do sprite
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite); // Desenha o sprite do jogador

    // Desenhe a hitbox em vermelho
    // sf::RectangleShape hitboxShape(sf::Vector2f(width, height));
    // hitboxShape.setPosition(x, y);
    // hitboxShape.setFillColor(sf::Color::Transparent);
    // hitboxShape.setOutlineColor(sf::Color::Red);
    // hitboxShape.setOutlineThickness(2.0f);
    // window.draw(hitboxShape);
}

void Player::update(float deltaTime) {
    velocityX = 0.0f;
    velocityY = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocityY = -400.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocityY = 400.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocityX = -400.0f;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocityX = 400.0f;

    if (velocityX > 0) {
        sprite.setTexture(textureRight);
        isFacingRight = true;
    } else if (velocityX < 0) {
        sprite.setTexture(textureLeft);
        isFacingRight = false;
    } else {
        // Definir a textura em estado de repouso quando o jogador não estiver se movendo horizontalmente
        sprite.setTexture(textureIdle);
    }


///////////////////////TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   /////////////////////////////////////
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        perderVida();
        
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    ganharVida();

///////////////////////FIM DO TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   TESTE   /////////////////////////////////////

    
    float dx = velocityX * deltaTime;
    float dy = velocityY * deltaTime;
    float newX = x + dx;
    float newY = y + dy;

    // Limitar a posição do jogador para que ele não saia da tela com base na hitbox
    if (newX < 0.0f) {
        newX = 0.0f;
    }
    if (newX > 1360.0f - hitbox.getWidth()) {
        newX = 1360.0f - hitbox.getWidth();
    }

    if (newY < 0.0f) {
        newY = 0.0f;
    }
    if (newY > 1000.0f - hitbox.getHeight()) {
        newY = 1000.0f - hitbox.getHeight();
    }

    // Atualizar a posição do jogador apenas se ele não ultrapassar os limites da tela
    x = newX;
    y = newY;

    hitbox.update(x, y); // Atualiza a posição da hitbox com a nova posição do jogador
    sprite.setPosition(x, y); // Atualiza a posição do sprite
        // Lidar com a colisão entre o jogador e o inimigo
        if (isInvulnerable) {
            invulnerabilityTimer += deltaTime;
            if (invulnerabilityTimer >= invulnerabilityTime) {
                isInvulnerable = false;
                invulnerabilityTimer = 0.0f;
            }
        }
    }
    
    void Player::perderVida() {
        if (!isInvulnerable) {
            vida--;
            isInvulnerable = true;
        }
    }   

const Hitbox& Player::getHitbox() const {
    return hitbox;
}


void Player::ganharVida(){
    vida++;
}

int Player::getVidas() const {
    return vida;
}

int Player::getx() {
    return x;
}

int Player::gety() {
    return y;
}

int Player::getw(){
    return width;
}