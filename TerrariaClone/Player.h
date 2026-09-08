#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <memory>
#include <array>
#include "Blocks.h" 
#include "Item.h"

class Player {
public:
    sf::Sprite sprite;
    sf::Vector2f velocity; 
    sf::FloatRect bounds = sprite.getGlobalBounds();
    std::array<std::unique_ptr<Item>, 36> inventoryItems;
    
    float speed = 200.0f;  
    float gravity = 1200.0f; 
    float jumpForce = -350.0f; 
    bool isGrounded = false;
	bool isFacingRight = true;
    int selectedSlotIndex = 1;

    Player(const sf::Texture& texture, float startX, float startY) : sprite(texture) {
        sprite.setPosition({ startX, startY });
		sprite.setOrigin({ 
            bounds.position.x + (bounds.size.x / 2.0f),
            bounds.position.y + (bounds.size.y / 2.0f) });
    }
    void selectedSlot();
    int getSelectedSlot() const { return selectedSlotIndex; }

    void update(float dt, const std::vector<std::vector<std::unique_ptr<Block>>>& world);

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

    void setInventoryItem(int slotIndex, std::unique_ptr<Item> item);

    const std::array<std::unique_ptr<Item>, 36>& getInventoryItems() const;

    void swapInventoryItems(int index1, int index2);
};