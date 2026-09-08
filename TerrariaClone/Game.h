#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Blocks.h"
#include "Player.h"
#include "Inventory.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Texture grassTex, dirtTex, stoneTex, charTex, axeTex, pickTex, swordTex;
    std::vector<std::vector<std::unique_ptr<Block>>> world;
    std::unique_ptr<Player> player;
    sf::View camera;
    sf::Clock clock;

	Inventory inventory;

    void processEvents();
    void update(float dt);
    void render();

public:
    Game();
    void run();
};