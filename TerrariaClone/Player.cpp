#include "Player.h"

void Player::update(float dt, const std::vector<std::unique_ptr<Block>>& world) {
    velocity.y += gravity * dt;
    velocity.x = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) velocity.x = -speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) velocity.x = speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && isGrounded) {
        velocity.y = jumpForce;
        isGrounded = false;
    }
    // KOLIZJE W OSI X (Poziom)
    sprite.move({ velocity.x * dt, 0.0f });
    sf::FloatRect playerBounds = sprite.getGlobalBounds();

    for (const auto& block : world) {
        if (playerBounds.findIntersection(block->getBounds())) {
            sprite.move({ -velocity.x * dt, 0.0f });
            velocity.x = 0.0f;
            break;
        }
    }
	float leftLimit = -50.0f * 32.0f;
    float rightLimit = 50.0f * 32.0f;

    if (sprite.getPosition().x < leftLimit)
    {
		sprite.setPosition({ leftLimit, sprite.getPosition().y });
        velocity.x = 0.0f;
    }
    else if (sprite.getPosition().x > rightLimit)
    {
        sprite.setPosition({ rightLimit, sprite.getPosition().y });
        velocity.x = 0.0f;
    }
    // KOLIZJE W OSI Y (Pion)
    sprite.move({ 0.0f, velocity.y * dt });
    playerBounds = sprite.getGlobalBounds();
    isGrounded = false;

    for (const auto& block : world) {
        if (playerBounds.findIntersection(block->getBounds())) {
            if (velocity.y > 0) {
                isGrounded = true;
            }
            sprite.move({ 0.0f, -velocity.y * dt });
            velocity.y = 0.0f;
            break;
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return { sprite.getPosition().x + 16.0f, sprite.getPosition().y + 24.0f };
}