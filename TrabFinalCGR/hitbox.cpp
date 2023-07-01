#include "hitbox.h"

Hitbox::Hitbox(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

bool Hitbox::checkCollision(const Hitbox& other) const {
    return (x < other.x + other.width) &&
           (x + width > other.x) &&
           (y < other.y + other.height) &&
           (y + height > other.y);
}

void Hitbox::update(float x, float y) {
    this->x = x;
    this->y = y;
}

float Hitbox::getX() const {
    return x;
}

float Hitbox::getY() const {
    return y;
}

float Hitbox::getWidth() const {
    return width;
}

float Hitbox::getHeight() const {
    return height;
}

