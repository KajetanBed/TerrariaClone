#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Blocks.h"

class TerrainGenerator {
public:
    static void generateWorld(
        std::vector<std::vector<std::unique_ptr<Block>>>& world,
        const sf::Texture& grassTex,
        const sf::Texture& dirtTex,
        const sf::Texture& stoneTex
    );
};