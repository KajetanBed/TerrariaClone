#pragma once 
#include <SFML/Graphics.hpp>

class Block {
protected:
    sf::Sprite sprite;
public:
    Block(const sf::Texture& texture, float x, float y) : sprite(texture) {
        sprite.setPosition({ x, y });
    }
    virtual ~Block() = default;

    virtual void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds();
    }
};