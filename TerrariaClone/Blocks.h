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
    virtual void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
};

class Dirt : public Block {
public:
    Dirt(const sf::Texture& texture, float x, float y) : Block(texture, x, y) {}
};

class Grass : public Block {
public:
    Grass(const sf::Texture& texture, float x, float y) : Block(texture, x, y) {}
};

class Stone : public Block {
public:
    Stone(const sf::Texture& texture, float x, float y) : Block(texture, x, y) {}
};