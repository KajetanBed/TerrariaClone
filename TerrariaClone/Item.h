#pragma once
#include <SFML/Graphics.hpp>


class Item
{
protected:
    sf::Sprite sprite;
public:
    Item(const sf::Texture& texture, float x, float y) : sprite(texture) {
        sprite.setPosition({ x, y });
		sprite.setOrigin({ 0.0f, 16.0f });
    }
    virtual ~Item() = default;
    virtual void draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f pos);
    void setScale(sf::Vector2f scale);
	void setRotation(sf::Angle angle);
    sf::Sprite getIconSprite() const;
};

class Sword : public Item {
public:
    Sword(const sf::Texture& texture, float x = 0, float y = 0) : Item(texture, x, y) {}
};

class Pickaxe : public Item {
public:
    Pickaxe(const sf::Texture& texture, float x = 0, float y = 0) : Item(texture, x, y) {}
};

class Axe : public Item {
public:
    Axe(const sf::Texture& texture, float x = 0, float y = 0) : Item(texture, x, y) {}
};

