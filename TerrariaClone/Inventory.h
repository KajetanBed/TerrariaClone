#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>
#include "Item.h"
#include "Player.h"

class Inventory
{
private:
	std::vector<sf::RectangleShape> slots;
	bool isOpen = false;
	bool isDragging = false;
	float slotSize = 40.0f;
	float padding = 5.0f;
	int draggedSlot = -1;

public:
	Inventory();
	void toggle();
	void handleEvent(const sf::Event& event, const sf::RenderWindow& window, Player& player);
	void draw(sf::RenderWindow& window, int currentSelectedSlot, const std::array<std::unique_ptr<Item>, 36>& items);
	bool getIsOpen() const;
};

