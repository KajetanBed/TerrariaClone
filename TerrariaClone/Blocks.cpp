#include "Blocks.h"

void Block::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Block::getBounds() const {
    return sprite.getGlobalBounds();
}