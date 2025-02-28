#include <utility>
#include "Player.h"

Player::Player(SDL_Rect rect, SDL_Texture *texture, float s)
    : x(rect.x), y(rect.y), width(rect.w), height(rect.h), texture(texture), speed(s) {}

Player::~Player() {
    SDL_DestroyTexture(texture);
}

void Player::update(double deltaTime, float xVelocity, float yVelocity, std::pair<int, int> windowSize) {
    xVelocity *= speed * deltaTime;
    yVelocity *= speed * deltaTime;

    x += xVelocity;
    y += yVelocity;

    // Make sure player does not go past edge of window
    if (x < 0) x = 0;
    if (x + width > windowSize.first) x = windowSize.first - width;
    if (y < 0) y = 0;
    if (y + height > windowSize.second) y = windowSize.second - height;
}

void Player::render(SDL_Renderer *renderer) {
    SDL_Rect playerRect = {static_cast<int>(std::round(x)), static_cast<int>(std::round(y)), width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &playerRect);
}