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
    if (!charTex.loadFromFile("assets/character.png")) std::cerr << "Blad: character.png\n";

    // Generowanie œwiata
	TerrainGenerator::generateWorld(world, grassTex, dirtTex, stoneTex);

    // Inicjalizacja gracza i kamery
    player = std::make_unique<Player>(charTex, 0.0f, -100.0f);
    camera = window.getDefaultView();
    camera.zoom(0.3f);
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
    window.display();
}