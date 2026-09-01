#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "Block.h"
#include "Grass.h"
#include "Dirt.h"
#include "Stone.h"
#include "Player.h" 
#include <algorithm> 

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Terraria Clone - Postac i Kamera!");
    window.setFramerateLimit(60); 

    sf::Texture grassTex, dirtTex, stoneTex, charTex;
    if (!grassTex.loadFromFile("assets/grass.png")) std::cerr << "Blad: grass.png\n";
    if (!dirtTex.loadFromFile("assets/dirt.png"))   std::cerr << "Blad: dirt.png\n";
    if (!stoneTex.loadFromFile("assets/stone.png")) std::cerr << "Blad: stone.png\n";
    if (!charTex.loadFromFile("assets/character.png")) std::cerr << "Blad: character.png\n";

    std::vector<std::unique_ptr<Block>> world;
    for (int i = -60; i <= 60; ++i)
    {
        float posX = i * 32.0f; 

        world.push_back(std::make_unique<Grass>(grassTex, posX, 100.0f));
        world.push_back(std::make_unique<Dirt>(dirtTex, posX, 132.0f));
        world.push_back(std::make_unique<Stone>(stoneTex, posX, 164.0f));
        world.push_back(std::make_unique<Stone>(stoneTex, posX, 196.0f)); 
    }

    Player player(charTex, 0.0f, 10.0f);
    sf::View camera = window.getDefaultView(); 

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        player.update(dt, world); 

        sf::Vector2f targetCenter = player.getPosition();
        float halfScreenWidth = window.getSize().x / 2.0f;
        float worldLeftBound = -50.0f * 32.0f;
        float worldRightBound = 50.0f * 32.0f;
        float minCameraX = worldLeftBound + halfScreenWidth;
        float maxCameraX = worldRightBound - halfScreenWidth;
        targetCenter.x = std::clamp(targetCenter.x, minCameraX, maxCameraX);
        camera.setCenter(targetCenter);


        window.clear(sf::Color(135, 206, 235));

        window.setView(camera);

        for (const auto& block : world)
        {
            block->draw(window);
           // sf::RectangleShape bbox;
           // bbox.setPosition(block->getBounds().position);
           // bbox.setSize(block->getBounds().size);
           // bbox.setFillColor(sf::Color::Transparent);
           // bbox.setOutlineColor(sf::Color::Blue);
           // bbox.setOutlineThickness(1.0f);
           // window.draw(bbox);
        }

        player.draw(window);

        window.display();
    }

    return 0;
}