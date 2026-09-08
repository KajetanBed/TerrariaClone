#include "Game.h"
#include "TerrainGenerator.h"
#include "Config.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Game::Game() : window(sf::VideoMode({ 1920, 1080 }), "Terraria Clone!") {
    window.setFramerateLimit(60);

    // £adowanie tekstur
    if (!grassTex.loadFromFile("assets/grass.png")) std::cerr << "Blad: grass.png\n";
    if (!dirtTex.loadFromFile("assets/dirt.png"))   std::cerr << "Blad: dirt.png\n";
    if (!stoneTex.loadFromFile("assets/stone.png")) std::cerr << "Blad: stone.png\n";
    if (!charTex.loadFromFile("assets/character_right.png")) std::cerr << "Blad: character_right.png\n";
    if (!swordTex.loadFromFile("assets/sword_wood.png")) std::cerr << "Blad: sword_wood.png\n";
    if (!pickTex.loadFromFile("assets/pickaxe_wood.png")) std::cerr << "Blad: pickaxe_wood.png\n";
    if (!axeTex.loadFromFile("assets/axe_wood.png")) std::cerr << "Blad: axe_wood.png\n";

    // Generowanie œwiata
	TerrainGenerator::generateWorld(world, grassTex, dirtTex, stoneTex);

    // Inicjalizacja gracza i kamery
    player = std::make_unique<Player>(charTex, 0.0f, -100.0f);
    player->setInventoryItem(0, std::make_unique<Sword>(swordTex));
    player->setInventoryItem(1, std::make_unique<Pickaxe>(pickTex));
    player->setInventoryItem(2, std::make_unique<Axe>(axeTex));
    camera = window.getDefaultView();
    camera.zoom(0.5f);
}

void Game::run() {
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f) dt = 0.05f;
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
        if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>()) {
            if (keyEvent->code == sf::Keyboard::Key::Escape) {
                inventory.toggle();
            }
        }
		inventory.handleEvent(*event, window, *player);
    }
}

void Game::update(float dt) {
    player->update(dt, world);

    sf::Vector2f targetCenter = player->getPosition();
    float halfScreenWidth = camera.getSize().x / 2.0f;
    float worldLeftBound = Config::MAP_MIN_X * Config::BLOCK_SIZE;
    float worldRightBound = (Config::MAP_MAX_X + 1) * Config::BLOCK_SIZE;
    float minCameraX = worldLeftBound + halfScreenWidth;
    float maxCameraX = worldRightBound - halfScreenWidth;

    targetCenter.x = std::clamp(targetCenter.x, minCameraX, maxCameraX);
    camera.setCenter(targetCenter);
}

void Game::render() {
    window.clear(sf::Color(135, 206, 235));
    window.setView(camera);

    sf::Vector2f viewCenter = camera.getCenter();
    sf::Vector2f viewSize = camera.getSize();
    float margin = Config::BLOCK_SIZE * 2.0f;
    float leftEdge = viewCenter.x - (viewSize.x / 2.0f) - margin;
    float rightEdge = viewCenter.x + (viewSize.x / 2.0f) + margin;
    int startCol = static_cast<int>(std::floor(leftEdge / Config::BLOCK_SIZE)) - Config::MAP_MIN_X;
    int endCol = static_cast<int>(std::floor(rightEdge / Config::BLOCK_SIZE)) - Config::MAP_MIN_X;
    startCol = std::clamp(startCol, 0, static_cast<int>(world.size()) - 1);
    endCol = std::clamp(endCol, 0, static_cast<int>(world.size()) - 1);
    for (int i = startCol; i <= endCol; ++i) {
        for (const auto& block : world[i]) {
            block->draw(window);
        }
    }

    player->draw(window);
	inventory.draw(window, player->getSelectedSlot(), player->getInventoryItems());
    window.display();
}