#include "Item.h"

void Item::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void Item::setPosition(sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Item::setScale(sf::Vector2f scale)
{
	sprite.setScale(scale);
}

void Item::setRotation(sf::Angle angle)
{
	sprite.setRotation(angle);
}

sf::Sprite Item::getIconSprite() const
{
	sf::Sprite icon = sprite;
	icon.setOrigin({ 0.0f, 0.0f });
	icon.setRotation(sf::degrees(0.0f));
	return icon;
}
