#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <memory>
#include "Blocks.h" 

class Player {
public:
    sf::Sprite sprite;
    sf::Vector2f velocity; 
    float speed = 200.0f;  
    float gravity = 1200.0f; 
    float jumpForce = -350.0f; 
    bool isGrounded = false;

    Player(const sf::Texture& texture, float startX, float startY) : sprite(texture) {
        sprite.setPosition({ startX, startY });
    }

    void update(float dt, const std::vector<std::vector<std::unique_ptr<Block>>>& world);

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
};