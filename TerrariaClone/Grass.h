#pragma once
#include "Block.h"

class Grass : public Block {
public:
    Grass(const sf::Texture& texture, float x, float y) : Block(texture, x, y) {}
};