#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include <iostream>
#include "hitbox.h"
#include <ctime>
#include "projectile.h"
#include "vida.h"
#include <cstdlib>
#include <SFML/Audio.hpp>
#include <iostream>
enum class GameState {
    GAME,
    GAME_OVER
};

int main() {
    srand(time(NULL));
    //cria a janela
    sf::RenderWindow window(sf::VideoMode(1360, 1000), "Jogo 2D");
    window.setFramerateLimit(60);

        // Carregue o arquivo de áudio (por exemplo, um arquivo .wav)
    sf::SoundBuffer soundBuffer;    
    if (!soundBuffer.loadFromFile("som/pew.wav")) {
        std::cerr << "Failed to load sound file!" << std::endl;
        return 1;
    }

    // Crie um objeto sf::Sound para reproduzir o som
    sf::Sound sound(soundBuffer);

    // Defina o volume do som (opcional)
    sound.setVolume(100); // Valor entre 0 e 100

    //carrega o background
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

    
    //criação de projetil e vidas
    std::vector<Projectile> projectilesPlayer;
    std::vector<Vida> vidas;


    float shotTimerPlayer = 0.5;
    float shotTimePlayer = 0;



    // Criação do jogador e vetores de inimigos 
    std::vector<Enemy> enemies;
    int activeE = 0;
    Player player(400.0f, 300.0f, "sprites/player/playerFront.png");
    
    //load das texturas de outras coisas
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("sprites/enemy/enemy.png")) {
    }
    sf::Texture projectileTexture;
    if (!projectileTexture.loadFromFile("sprites/projeteis/projetilPlayer.png")) {
    }
    sf::Texture vidaTexture;
    if (!vidaTexture.loadFromFile("sprites/drops/vida.png")) {
        std::cout << "Erro ao carregar a textura do vidas" << std::endl;
    }   
    // Texto de vidas
    sf::Text txtVidas;
    txtVidas.setFont(font);
    txtVidas.setCharacterSize(30);
    txtVidas.setFillColor(sf::Color::Green);

    // Texto de pontos
    sf::Text txtPontos;
    txtPontos.setFont(font);
    txtPontos.setCharacterSize(30);
    txtPontos.setFillColor(sf::Color::White);

    sf::Clock clock;


    //texto de fim de jogo 
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

/////////////////////////////////SPAWN DOS INIMIGOS/////////////////////////////////
        if ( activeE < 5) {
            activeE++;
            float randomX = static_cast<float>(rand() % 1360); // Gera um valor de x aleatório entre 0 e 1360
            enemies.emplace_back(randomX, -200.0f, &enemyTexture);
        }

/////////////////////////////////FIM SPAWN/////////////////////////////////
                // Atualizar todos os inimigos e proieteis
        for(size_t i = 0; i < enemies.size(); i++) {
            enemies[i].update(dt);
        }
        for(size_t i = 0; i < projectilesPlayer.size(); i++) {
            projectilesPlayer[i].update(dt);
        }
        for(size_t i = 0; i < vidas.size(); i++) {
            vidas[i].update(dt);
        }




//////////////////////VERIFICAÇÃO DE COLISÕES///////////////////Q
        for (size_t i = 0; i < vidas.size(); i++){
            if (player.getHitbox().checkCollision(vidas[i].getHitbox()) && player.getVidas() < 5){
                player.ganharVida();
                vidas.erase(vidas.begin()+i);
                i--;
            }
            
        }
        
        
        for(size_t i = 0; i < enemies.size(); i++) {
            enemies[i].update(dt);
            //colisão entre jogador e inimigo
            if (player.getHitbox().checkCollision(enemies[i].getHitbox())) {
                player.perderVida();
            }
            //colisão entre inimigo e projetil
            for(size_t j = 0; j < projectilesPlayer.size(); j++) {
                    if(projectilesPlayer[j].getHitbox().checkCollision(enemies[i].getHitbox())){

                        activeE--;

                        if (std::rand() % 100 <= 5){
                            vidas.emplace_back(enemies[i].getX() + enemies[i].getWidth()/2, enemies[i].getY()+enemies[i].getHeight()/2, &vidaTexture);

                        }
                        enemies.erase(enemies.begin() + i);
                        projectilesPlayer.erase(projectilesPlayer.begin()+j);
                        j--;
                        i--; // Decrementar o índice para evitar pular o próximo inimigo
                        player.ganharPontos(10);

//verifica se o inimigo saiu da tela pelo inferior

                    } else if (enemies[i].isOutOfScreen()){
                        enemies.erase(enemies.begin() + i);
                        i--; // Decrementar o índice para evitar pular o próximo inimigo
                        activeE--;
                    }
                }
        }   
//////////////////////FIM VERIFICAÇÃO DE COLISÕES///////////////////Q
        
         

        //player shooto
        if(shotTimePlayer > shotTimerPlayer){
            shotTimePlayer = 0;
            projectilesPlayer.emplace_back((player.getx()+player.getw()/2 - 10), (player.gety() + 5), 0.0f,-200.0f, &projectileTexture);
            // projectilesPlayer.emplace_back((player.getx()+player.getw()/2 - 10), (player.gety() + 5), 100.0f,-200.0f, &projectileTexture);
            // projectilesPlayer.emplace_back((player.getx()+player.getw()/2 - 10), (player.gety() + 5), -100.f,-200.0f, &projectileTexture);
            sound.play();
        }else{
            shotTimePlayer += dt;
        }
        
            // Lógica do jogo
            // Atualizar o texto de vidas
            txtPontos.setString("Pontos: " + std::to_string(player.getPontos()));
            txtPontos.setPosition(1100.0f, 10.0f);
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
            for(const auto& projectile : projectilesPlayer) {   
                projectile.draw(window);
            }
            for (const auto& enemy : enemies) {
                if(enemy.isOutOfScreen()){}
                enemy.draw(window);
            } 
            for (const auto& vida : vidas){
                vida.draw(window);
            }
            
            player.draw(window);
            window.draw(txtVidas);
            window.draw(txtPontos);
        } else if (gameState == GameState::GAME_OVER) {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
