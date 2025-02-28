#ifndef PLAYER_H
#define PLAYER_H
#include <SDL2/SDL.h>

class Player {
private:
    float x, y;
    int width, height;
    float speed;
    SDL_Texture *texture;

public:
    Player(SDL_Rect rect, SDL_Texture *texture, float s);
    ~Player();

    void update(double deltaTime, float xVelocity, float yVelocity, std::pair<int, int> windowSize);
    void render(SDL_Renderer *renderer);
};

#endif //PLAYER_H
