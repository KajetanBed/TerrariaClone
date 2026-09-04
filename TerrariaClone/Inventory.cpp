#include "Inventory.h"
#include "Player.h"

Inventory::Inventory() {
	for(int y =0; y < 4; ++y)
	{
		for(int x =0; x < 9; ++x)
		{
			sf::RectangleShape slot({slotSize, slotSize});
			slot.setFillColor(sf::Color(100, 100, 100, 150));
			slot.setOutlineColor(sf::Color(200, 200, 200, 200));
			slot.setOutlineThickness(2.0f);

			float posX = 20.0f + x * (slotSize + padding);
			float posY = 20.0f + y * (slotSize + padding);
			slot.setPosition({ posX, posY });
			slots.push_back(slot);
		}
	}
}
void Inventory::toggle() {
	isOpen = !isOpen;
}

void Inventory::draw(sf::RenderWindow& window, int currentSelectedSlot) {
    int visibleSlots = isOpen ? 36 : 9;
    sf::View oldView = window.getView();
    window.setView(window.getDefaultView());
    for (int i = 0; i < visibleSlots; ++i) {
        slots[i].setOutlineColor(sf::Color(200, 200, 200, 200));
    }
    int index = currentSelectedSlot - 1;
    if (index >= 0 && index < slots.size()) {
        slots[index].setOutlineColor(sf::Color::Yellow);
    }
    for (int i = 0; i < visibleSlots; ++i) {
        window.draw(slots[i]);
    }

    window.setView(oldView);
}