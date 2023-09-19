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
enum class GameState
{
    GAME,
    GAME_OVER
};

using namespace sf;

int main()
{
    srand(time(NULL));
    // cria a janela
    RenderWindow window(VideoMode(1280, 720), "Jogo 2D");
    window.setFramerateLimit(60);

    // Carregue o arquivo de áudio (por exemplo, um arquivo .wav)
    SoundBuffer soundBuffer;
    if (!soundBuffer.loadFromFile("som/pew.wav"))
    {
        std::cerr << "Failed to load sound file!" << std::endl;
        return 1;
    }

    // Crie um objeto Sound para reproduzir o som
    Sound sound(soundBuffer);

    // Defina o volume do som (opcional)
    sound.setVolume(100); // Valor entre 0 e 100

    // carrega o background
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("sprites/background/background2.png"))
    {
        return -1; // Encerra o programa se ocorrer um erro ao carregar a textura
    }

    // Criar duas sprites para o plano de fundo
    Sprite backgroundSprite1(backgroundTexture);
    Sprite backgroundSprite2(backgroundTexture);
    float scrollSpeed = 100.0f;

    // Posiciona as duas sprites na parte superior da janela
    backgroundSprite1.setPosition(0, 0);
    backgroundSprite2.setPosition(0, -1000);

    // define a fonte
    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "Erro ao carregar a fonte!" << std::endl;
        return 1;
    }

    // criação de projetil e vidas
    std::vector<Projectile> projectilesPlayer;
    std::vector<Projectile> projectilesEnemy;
    std::vector<Vida> vidas;

    float shotTimerPlayer = 0.5;
    float shotTimePlayer = 0;

    // Criação do jogador e vetores de inimigos
    std::vector<Enemy> enemies;
    int activeE = 0;
    Player player(400.0f, 300.0f, "sprites/player/playerFront.png");

    // load das texturas de outras coisas
    Texture enemyTexture;
    if (!enemyTexture.loadFromFile("sprites/enemy/enemy.png"))
    {
    }
    Texture projectileTexturePlayer;
    if (!projectileTexturePlayer.loadFromFile("sprites/projeteis/projetilPlayer.png"))
    {
    }
    Texture projectileTextureEnemy;
    if (!projectileTextureEnemy.loadFromFile("sprites/projeteis/projetilEnemy.png"))
    {
    }
    Texture vidaTexture;
    if (!vidaTexture.loadFromFile("sprites/drops/vida.png"))
    {
        std::cout << "Erro ao carregar a textura do vidas" << std::endl;
    }
    // Texto de vidas
    Text txtVidas;
    txtVidas.setFont(font);
    txtVidas.setCharacterSize(30);
    txtVidas.setFillColor(Color::Green);
    txtVidas.setPosition(10.0f, 10.0f);

    // Texto de pontos
    Text txtPontos;
    txtPontos.setFont(font);
    txtPontos.setCharacterSize(30);
    txtPontos.setFillColor(Color::White);
    txtPontos.setPosition(1100.0f, 10.0f);
    Clock clock;

    // texto de fim de jogo
    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setString("Fim de Jogo!");

    // texto de tempo
    Text gameTimeText;
    gameTimeText.setFont(font);
    gameTimeText.setCharacterSize(50);
    gameTimeText.setFillColor(Color::Cyan);
    gameTimeText.setPosition(500.0f, 10.0f);

    float gametime = 0;

    // Inicializar o estado do jogo
    GameState gameState = GameState::GAME;

    // Loop do jogo
    while (window.isOpen())
    {
        // Process events
        Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == Event::Closed)
                window.close();

            // Escape key: exit
            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
                window.close();

            // Enter key: restart
            if ((event.type == Event::KeyPressed) &&
                (event.key.code == Keyboard::Enter) &&
                gameState == GameState::GAME_OVER)
            {
                gameState = GameState::GAME;
                player = Player(400.0f, 300.0f, "sprites/player/playerFront.png");
                activeE = 0;
                gametime = 0;
                gameTimeText.setPosition(500.0f, 10.0f);
            }
        }

        // Calcular o tempo decorrido entre cada frame
        Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        gametime += dt;
        if (gameState == GameState::GAME)
        {
            // Movimenta as duas sprites do plano de fundo na vertical
            backgroundSprite1.move(0, scrollSpeed * dt);
            backgroundSprite2.move(0, scrollSpeed * dt);

            /////////////////////////////////SPAWN DOS INIMIGOS/////////////////////////////////
            if (activeE < 5)
            { // rand() % 60 == 0 &&
                activeE++;
                float randomX = static_cast<float>(rand() % 1280); // Gera um valor de x aleatório entre 0 e 1280
                enemies.emplace_back(randomX, -200.0f, &enemyTexture);
                // std::cout << enemies.back().getX() << std::endl;
            }

            /////////////////////////////////FIM SPAWN/////////////////////////////////
            // Atualizar todos os inimigos e proieteis
            for (auto &enemie : enemies)
            {
                enemie.update(dt);
            }
            for (auto &plProjectile : projectilesPlayer)
            {
                plProjectile.update(dt);
            }
            for (auto &enProjectile : projectilesEnemy)
            {
                enProjectile.update(dt);
            }
            for (auto &life : vidas)
            {
                life.update(dt);
            }
            player.update(dt);

            //////////////////////VERIFICAÇÃO DE COLISÕES///////////////////Q
            for (size_t i = 0; i < vidas.size(); i++)
            {
                if (player.getHitbox().checkCollision(vidas[i].getHitbox()) && player.getVidas() < 5)
                {
                    player.ganharVida();
                    vidas.erase(vidas.begin() + i);
                    i -= (i != 0);
                }
            }

            for (size_t i = 0; i < enemies.size(); i++)
            {
                while (enemies[i].isOutOfScreen())
                {
                    enemies.erase(enemies.begin() + i);
                    i -= (i != 0); // Decrementar o índice para evitar pular o próximo inimigo
                    activeE--;
                }
                // enemies[i].update(dt);
                // colisão entre jogador e inimigo
                if (player.getHitbox().checkCollision(enemies[i].getHitbox()))
                {
                    player.perderVida();
                    enemies.erase(enemies.begin() + i);
                    i -= (i != 0); // Decrementar o índice para evitar pular o próximo inimigo
                    activeE--;
                }
                // colisão entre inimigo e projetil
                for (size_t j = 0; j < projectilesPlayer.size(); j++)
                {
                    while (projectilesPlayer[j].isOutOfScreen())
                    {
                        projectilesPlayer.erase(projectilesPlayer.begin() + j);
                        j -= (j != 0);
                    }
                    while (projectilesPlayer[j].getHitbox().checkCollision(enemies[i].getHitbox()))
                    {
                        activeE--;
                        if (std::rand() % 100 <= 5)
                        {
                            vidas.emplace_back(enemies[i].getX() + enemies[i].getWidth() / 2, enemies[i].getY() + enemies[i].getHeight() / 2, &vidaTexture);
                        }
                        enemies.erase(enemies.begin() + i);
                        i -= (i != 0); // Decrementar o índice para evitar pular o próximo inimigo
                        projectilesPlayer.erase(projectilesPlayer.begin() + j);
                        j -= (j != 0);
                        player.ganharPontos(10);
                    }
                }
                if (enemies[i].pew())
                {
                    projectilesEnemy.emplace_back(enemies[i].getX() + enemies[i].getWidth() / 2, enemies[i].getY() + enemies[i].getHeight(), 100.0f, 200.0f, &projectileTextureEnemy);
                    projectilesEnemy.emplace_back(enemies[i].getX() + enemies[i].getWidth() / 2, enemies[i].getY() + enemies[i].getHeight(), -100.0f, 200.0f, &projectileTextureEnemy);
                    projectilesEnemy.emplace_back(enemies[i].getX() + enemies[i].getWidth() / 2, enemies[i].getY() + enemies[i].getHeight(), 0.0f, 200.0f, &projectileTextureEnemy);
                }
            }
            for (size_t i = 0; i < projectilesEnemy.size(); i++)
            {
                if (projectilesEnemy[i].isOutOfScreen())
                {
                    projectilesEnemy.erase(projectilesEnemy.begin() + i);
                    i -= (i != 0);
                }

                if (projectilesEnemy[i].getHitbox().checkCollision(player.getHitbox()))
                {
                    player.perderVida();
                    projectilesEnemy.erase(projectilesEnemy.begin() + i);
                    i -= (i != 0);
                }
            }

            //////////////////////FIM VERIFICAÇÃO DE COLISÕES///////////////////Q

            // player shooto
            shotTimePlayer += dt;
            if (shotTimePlayer > shotTimerPlayer)
            {
                shotTimePlayer = 0;
                projectilesPlayer.emplace_back((player.getx() + player.getw() / 2 - 10), (player.gety() + 5), 0.0f, -200.0f, &projectileTexturePlayer);
                // projectilesPlayer.emplace_back((player.getx()+player.getw()/2 - 10), (player.gety() + 5), 100.0f,-200.0f, &projectileTexturePlayer);
                // projectilesPlayer.emplace_back((player.getx()+player.getw()/2 - 10), (player.gety() + 5), -100.f,-200.0f, &projectileTexturePlayer);
                sound.play();
            }

            // Lógica do jogo
            // Atualizar o texto de vidas
            txtPontos.setString("Pontos: " + std::to_string(player.getPontos()));
            txtVidas.setString("Vidas: " + std::to_string(player.getVidas()));
            std::string timetex(std::to_string(gametime));
            timetex.resize(timetex.size()-4);
            gameTimeText.setString(timetex);

            if (player.getVidas() <= 0)
            {
                gameState = GameState::GAME_OVER;
            }
        }

        // Verifica se alguma das sprites chegou ao final da janela e reseta sua posição
        if (backgroundSprite1.getPosition().y >= 1000)
        {
            backgroundSprite1.setPosition(0, -1000);
        }
        if (backgroundSprite2.getPosition().y >= 1000)
        {
            backgroundSprite2.setPosition(0, -1000);
        }
        window.clear();
        window.draw(backgroundSprite1);
        window.draw(backgroundSprite2);

        if (gameState == GameState::GAME)
        {
            for (const auto &projectile : projectilesPlayer)
            {
                projectile.draw(window);
            }
            for (const auto &projectile : projectilesEnemy)
            {
                projectile.draw(window);
            }
            for (const auto &enemy : enemies)
            {
                enemy.draw(window);
            }
            for (const auto &vida : vidas)
            {
                vida.draw(window);
            }

            // Piscar quando invulneravel
            if (!player.invulneravel() || (static_cast<int>(gametime * 10) % 5 != 0))
            {
                player.draw(window);
            }
            window.draw(txtVidas);
            window.draw(txtPontos);
        }

        else if (gameState == GameState::GAME_OVER)
        {
            enemies.clear();
            projectilesEnemy.clear();
            projectilesPlayer.clear();
            vidas.clear();
            gameTimeText.setPosition(500.0f, 300.0f);
            window.draw(gameOverText);
        }
        window.draw(gameTimeText);
        window.display();
    }
    window.close();
    return 0;
}