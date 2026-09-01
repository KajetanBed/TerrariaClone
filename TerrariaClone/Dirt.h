#pragma once
#include "Block.h"

class Dirt : public Block {
public:
    Dirt(const sf::Texture& texture, float x, float y) : Block(texture, x, y) {}
};