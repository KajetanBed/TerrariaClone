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

void Inventory::handleEvent(const sf::Event& event, const sf::RenderWindow& window, Player& player) {
    if (!isOpen) return; 
    if (const auto* mouseBtn = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mouseBtn->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseBtn->position, window.getDefaultView());

            for (int i = 0; i < 36; ++i) {
                if (slots[i].getGlobalBounds().contains(mousePos)) {
                    if (player.getInventoryItems()[i]) { 
                        isDragging = true;
                        draggedSlot = i;
                    }
                    break;
                }
            }
        }
    }
    else if (const auto* mouseRelease = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mouseRelease->button == sf::Mouse::Button::Left && isDragging) {
            sf::Vector2f mousePos = window.mapPixelToCoords(mouseRelease->position, window.getDefaultView());

            for (int i = 0; i < 36; ++i) {
                if (slots[i].getGlobalBounds().contains(mousePos)) {
                    player.swapInventoryItems(draggedSlot, i);
                    break;
                }
            }
            isDragging = false;
            draggedSlot = -1;
        }
    }
}

void Inventory::draw(sf::RenderWindow& window, int currentSelectedSlot, const std::array<std::unique_ptr<Item>, 36>& items) {
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
        if (items[i] && (!isDragging || i != draggedSlot)) {
            sf::Sprite icon = items[i]->getIconSprite();
            icon.setScale({ 2.0f, 2.0f });

            sf::FloatRect slotBounds = slots[i].getGlobalBounds();
            sf::FloatRect iconBounds = icon.getGlobalBounds();
            float iconX = slotBounds.position.x + (slotBounds.size.x - iconBounds.size.x) / 2.0f;
            float iconY = slotBounds.position.y + (slotBounds.size.y - iconBounds.size.y) / 2.0f;

            icon.setPosition({ iconX, iconY });
            window.draw(icon);
        }
    }
    if (isDragging && draggedSlot >= 0 && items[draggedSlot]) {
        sf::Sprite draggedIcon = items[draggedSlot]->getIconSprite();
        draggedIcon.setScale({ 2.0f, 2.0f });
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::FloatRect bounds = draggedIcon.getGlobalBounds();
        draggedIcon.setPosition({ mousePos.x - bounds.size.x / 2.0f, mousePos.y - bounds.size.y / 2.0f });
        window.draw(draggedIcon);
    }

    window.setView(oldView);
}