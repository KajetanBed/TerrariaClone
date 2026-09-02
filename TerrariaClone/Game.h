#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Blocks.h"
#include "Player.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Texture grassTex, dirtTex, stoneTex, charTex;
    std::vector<std::vector<std::unique_ptr<Block>>> world;
    std::unique_ptr<Player> player;
    sf::View camera;
    sf::Clock clock;

    void processEvents();
    void update(float dt);
    void render();

public:
    Game();
    void run();
};