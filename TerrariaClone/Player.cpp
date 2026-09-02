#include "Player.h"
#include "Config.h" 
#include <cmath>

#include <cmath> // potrzebne do std::floor

void Player::update(float dt, const std::vector<std::vector<std::unique_ptr<Block>>>& world) {
    velocity.y += gravity * dt;
    velocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.x = -speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.x = speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isGrounded) {
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
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return { sprite.getPosition().x + 16.0f, sprite.getPosition().y + 24.0f };
}