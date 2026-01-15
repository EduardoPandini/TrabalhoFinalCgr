#include <SFML/Graphics.hpp>
#include "player.h"
#include <iostream>

enum class GameState {
    GAME,
    GAME_OVER
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "Jogo 2D");
    window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Erro ao carregar a fonte!" << std::endl;
        return 1;
    }

    // Criação do jogador
    Player player(400.0f, 300.0f, "player.png");
    // Texto de vidas
    sf::Text txtVidas;
    txtVidas.setFont(font);
    txtVidas.setCharacterSize(30);
    txtVidas.setFillColor(sf::Color::White);

    sf::Clock clock;
    
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("Fim de Jogo!\nPressione R para reiniciar.");

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
                // Lógica do jogo
                // Atualizar o texto de vidas
                txtVidas.setString("Vidas: " + std::to_string(player.getVidas()));
                txtVidas.setPosition(10.0f, 10.0f);

                // Verificar se as vidas chegaram a 0 para mudar para o estado de GAME_OVER
                if (player.getVidas() <= 0) {
                    gameState = GameState::GAME_OVER;
                }
            }
            
            
// Renderização do jogo
        window.clear();
        
        if (gameState == GameState::GAME) {
            player.draw(window);
            window.draw(txtVidas);
        } else if (gameState == GameState::GAME_OVER) {
            window.draw(gameOverText);
        }

        window.display();
        }
    return 0;
}