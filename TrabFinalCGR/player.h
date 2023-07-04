#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp> // Incluir para lidar com eventos de teclado
#include "hitbox.h"
class enemy;
class Player {
public:
    Player(float x, float y, const std::string& filename);
    
    void move(float dx, float dy);

    void draw(sf::RenderWindow& window); // Novo método para desenhar o jogador

    void update(float deltaTime);

    // Função para obter a hitbox atualizada do jogador
    const Hitbox& getHitbox() const;

    // Função para perder uma vida
    void perderVida();

    // Função para obter o número de vidas do jogador
    int getVidas() const;
    void ganharVida();
    void ganharPontos(int pontos);
    int getPontos() const;
    int getx();
    int gety();
    int getw();



private:
    float x, y;
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;
    float width = 100;
    float height = 86;
    Hitbox hitbox;
    int pontos = 0;
    
    int vida = 3; // Número de vidas do jogador
    // Variáveis de invulnerabilidade
    bool isInvulnerable;
    float invulnerabilityTime;
    float invulnerabilityTimer;
    
    
    sf::Texture texture; // Textura do jogador
    sf::Sprite sprite;   // Sprite do jogador
    
    sf::Texture textureLeft;   // Textura do jogador virado para a esquerda
    sf::Texture textureRight;  // Textura do jogador virado para a direita
    sf::Texture textureIdle;   // Textura do jogador em estado de repouso
    bool isFacingRight;        // Flag para verificar a direção do jogador


    // ... outras variáveis
    float shootTimer; // Contador de tempo para o intervalo de disparo
    float shootInterval = 0.5f; // Intervalo de tempo entre os disparos (em segundos)
    // ... outras funções
    bool shootProjectile();
};

#endif // PLAYER_H
