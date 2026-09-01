#include "Stone.h"

class Stone : public Block {
public:
    Stone(const sf::Texture& texture, float x, float y) : Block(texture, x, y) {}
};