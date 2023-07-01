#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include <iostream>
#include "hitbox.h"
#include <ctime>
#include "projectile.h"
enum class GameState {
    GAME,
    GAME_OVER
};

int main() {
    srand(time(NULL));
    //cria a janela
    sf::RenderWindow window(sf::VideoMode(1360, 1000), "Jogo 2D");
    window.setFramerateLimit(60);


    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/background/background2.png")) {
        return -1; // Encerra o programa se ocorrer um erro ao carregar a textura
    }
    // Criar duas sprites para o plano de fundo
    sf::Sprite backgroundSprite1(backgroundTexture);
    sf::Sprite backgroundSprite2(backgroundTexture);
    float scrollSpeed = 100.0f;

    // Posiciona as duas sprites na parte superior da janela
    backgroundSprite1.setPosition(0, 0);
    backgroundSprite2.setPosition(0, -1000);

    //define a fonte
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Erro ao carregar a fonte!" << std::endl;
        return 1;
    }
    //criação de projetil
    std::vector<Projectile> projectiles;
    float shooooot_timer = 0.5;
    float shooooot_time = 0;
    // Criação do jogador
    std::vector<Enemy> enemies;
    int activeE = 0;
    Player player(400.0f, 300.0f, "sprites/player/playerFront.png");
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("sprites/enemy/enemy.png")) {
    }
    sf::Texture projectileTexture;
    if (!projectileTexture.loadFromFile("sprites/projeteis/projetilPlayer.png")) {
    }
    
    // Texto de vidas
    sf::Text txtVidas;
    txtVidas.setFont(font);
    txtVidas.setCharacterSize(30);
    txtVidas.setFillColor(sf::Color::Green);

    sf::Clock clock;
    
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Fim de Jogo!");

    // Inicializar o estado do jogo
    GameState gameState = GameState::GAME;

    // Loop do jogo
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        

        // Calcular o tempo decorrido entre cada frame
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        if (gameState == GameState::GAME) {
            // Movimenta as duas sprites do plano de fundo na vertical
            backgroundSprite1.move(0, scrollSpeed * dt);
            backgroundSprite2.move(0, scrollSpeed * dt);


        if ( activeE < 33) {
            activeE++;
            float randomX = static_cast<float>(rand() % 1360); // Gera um valor de x aleatório entre 0 e 1360
            enemies.emplace_back(randomX, -200.0f, &enemyTexture);
        }
                // Atualizar todos os inimigos


        for(size_t i = 0; i < enemies.size(); i++) {
            enemies[i].update(dt);
            for(size_t j = 0; j < projectiles.size(); j++) {
                    projectiles[j].update(dt);
                    //verifica colisão projectil e inimigo
                    if(projectiles[j].getHitbox().checkCollision(enemies[i].getHitbox()) || enemies[i].isOutOfScreen()){
                        enemies.erase(enemies.begin() + i);
                        projectiles.erase(projectiles.begin()+j);
                        j--;
                        i--; // Decrementar o índice para evitar pular o próximo inimigo
                        activeE--;
                    }
                
                }

        }
         

        //player shooto
        if(shooooot_time > shooooot_timer){
            shooooot_time = 0;
            projectiles.emplace_back(player.getx()+player.getw()/2, player.gety(), &projectileTexture);
        }else{
            shooooot_time += dt;
        }
        



        for (auto& enemy : enemies) {
            enemy.update(dt);
            // Verificar colisão entre o jogador e cada inimigo
            if (player.getHitbox().checkCollision(enemy.getHitbox())) {
                player.perderVida();
            }

        }
            // Lógica do jogo
            // Atualizar o texto de vidas
            txtVidas.setString("Vidas: " + std::to_string(player.getVidas()));
            txtVidas.setPosition(10.0f, 10.0f);
            player.update(dt);
            if (player.getVidas() <= 0) {
                gameState = GameState::GAME_OVER;
            }
        }
        
        // Verifica se alguma das sprites chegou ao final da janela e reseta sua posição
        if (backgroundSprite1.getPosition().y >= 1000) {
            backgroundSprite1.setPosition(0, -1000);
        }
        if (backgroundSprite2.getPosition().y >= 1000) {
            backgroundSprite2.setPosition(0, -1000);
        }
        window.clear();
        window.draw(backgroundSprite1);
        window.draw(backgroundSprite2);
        
        if (gameState == GameState::GAME) {
            for(const auto& projectile : projectiles) {   
                projectile.draw(window);
            }
            for (const auto& enemy : enemies) {
                if(enemy.isOutOfScreen()){}
                enemy.draw(window);
            } 
            player.draw(window);
            window.draw(txtVidas);
        } else if (gameState == GameState::GAME_OVER) {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
