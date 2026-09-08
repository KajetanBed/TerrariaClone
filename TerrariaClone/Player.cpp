#include "Player.h"
#include "Config.h" 
#include "Inventory.h"
#include <cmath>

void Player::update(float dt, const std::vector<std::vector<std::unique_ptr<Block>>>& world) {
    velocity.y += gravity * dt;
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		isFacingRight = false;
        velocity.x = -speed;
		sprite.setScale({ -1.0f, 1.0f });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		isFacingRight = true;
        velocity.x = speed;
		sprite.setScale({ 1.0f, 1.0f });
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && isGrounded) {
        velocity.y = jumpForce;
        isGrounded = false;
    }
    auto getColumns = [&](sf::FloatRect bounds) {
        float margin = Config::BLOCK_SIZE * 2.0f;
        int startCol = static_cast<int>(std::floor((bounds.position.x - margin) / Config::BLOCK_SIZE)) - Config::MAP_MIN_X;
        int endCol = static_cast<int>(std::floor((bounds.position.x + bounds.size.x + margin) / Config::BLOCK_SIZE)) - Config::MAP_MIN_X;
        startCol = std::clamp(startCol, 0, static_cast<int>(world.size()) - 1);
        endCol = std::clamp(endCol, 0, static_cast<int>(world.size()) - 1);
        return std::make_pair(startCol, endCol);
        };
    sprite.move({ velocity.x * dt, 0.0f });
    sf::FloatRect boundsX = sprite.getGlobalBounds();
    auto [startX, endX] = getColumns(boundsX);

    for (int i = startX; i <= endX; ++i) {
        for (const auto& block : world[i]) {
            if (boundsX.findIntersection(block->getBounds())) {
                sprite.move({ -velocity.x * dt, 0.0f });
                velocity.x = 0.0f;
                break;
            }
        }
    }
    float leftLimit = Config::MAP_MIN_X * Config::BLOCK_SIZE;
    float rightLimit = (Config::MAP_MAX_X + 1) * Config::BLOCK_SIZE;
    float playerWidth = sprite.getGlobalBounds().size.x;
    if (sprite.getPosition().x < leftLimit) {
        sprite.setPosition({ leftLimit, sprite.getPosition().y });
        velocity.x = 0.0f;
    }
    else if (sprite.getPosition().x + playerWidth > rightLimit) {
        sprite.setPosition({ rightLimit - playerWidth, sprite.getPosition().y });
        velocity.x = 0.0f;
    }
    sprite.move({ 0.0f, velocity.y * dt });
    sf::FloatRect boundsY = sprite.getGlobalBounds();
    isGrounded = false;
    auto [startY, endY] = getColumns(boundsY);

    for (int i = startY; i <= endY; ++i) {
        for (const auto& block : world[i]) {
            if (boundsY.findIntersection(block->getBounds())) {
                if (velocity.y > 0) isGrounded = true;
                sprite.move({ 0.0f, -velocity.y * dt });
                velocity.y = 0.0f;
                break;
            }
        }
    }
	selectedSlot();

    Item* activeItem = inventoryItems[selectedSlotIndex - 1].get();

    if (activeItem) {
		sf::Vector2f basePos = getPosition();
        float offsetX = 3.0f;
		float offsetY = 7.0f;
        if (!isFacingRight) {
            activeItem->setScale({ -1.0f, 1.0f });
            offsetX = -offsetX;
        }
        else {
            activeItem->setScale({ 1.0f, 1.0f });
        }
        activeItem->setPosition({ basePos.x + offsetX, basePos.y + offsetY });
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			float swingAngle = isFacingRight ? -45.0f : 45.0f;
			activeItem->setRotation(sf::degrees(swingAngle));
        }
        else {
            activeItem->setRotation(sf::degrees(0.0f));
		}
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    Item* activeItem = inventoryItems[selectedSlotIndex - 1].get();
    if (activeItem) {
        activeItem->draw(window);
    }
}

sf::Vector2f Player::getPosition() const {
	sf::FloatRect bounds = sprite.getGlobalBounds();
    return {
        bounds.position.x + (bounds.size.x / 2.0f),
        bounds.position.y + (bounds.size.y / 2.0f)
    };
}

void Player::setInventoryItem(int slotIndex, std::unique_ptr<Item> item)
{
    if (slotIndex >= 0 && slotIndex < inventoryItems.size()) {
        inventoryItems[slotIndex] = std::move(item);
    }
}

const std::array<std::unique_ptr<Item>, 36>& Player::getInventoryItems() const
{
    return inventoryItems;
}

void Player::swapInventoryItems(int index1, int index2)
{
	std::swap(inventoryItems[index1], inventoryItems[index2]);
}




void Player::selectedSlot() {
    const sf::Keyboard::Key numKeys[] = {
    sf::Keyboard::Key::Num1, sf::Keyboard::Key::Num2, sf::Keyboard::Key::Num3,
    sf::Keyboard::Key::Num4, sf::Keyboard::Key::Num5, sf::Keyboard::Key::Num6,
    sf::Keyboard::Key::Num7, sf::Keyboard::Key::Num8, sf::Keyboard::Key::Num9
    };

    for (int i = 0; i < 9; ++i) {
        if (sf::Keyboard::isKeyPressed(numKeys[i])) {
            selectedSlotIndex = i + 1;
        }
    }
	
}