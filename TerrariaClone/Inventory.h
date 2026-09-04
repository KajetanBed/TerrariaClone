#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Inventory
{
private:
	std::vector<sf::RectangleShape> slots;
	bool isOpen = false;
	float slotSize = 40.0f;
	float padding = 5.0f;

public:
	Inventory();
	void toggle();
	
	void draw(sf::RenderWindow& window, int currentSelectedSlot);
	bool getIsOpen() const;
};

