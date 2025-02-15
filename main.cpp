#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>

const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
const int CIRCLE_RADIUS = 5;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    bool running = true;
    SDL_Event event;

    int xPos = SCREEN_WIDTH / 2;
    int yPos = SCREEN_HEIGHT / 2;
    int velocity = 1;
    bool w_held = false;
    bool a_held = false;
    bool s_held = false;
    bool d_held = false;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        w_held = true;
                        break;
                    case SDLK_a:
                        a_held = true;
                        break;
                    case SDLK_s:
                        s_held = true;
                        break;
                    case SDLK_d:
                        d_held = true;
                        break;
                }
            }
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        w_held = false;
                        break;
                    case SDLK_a:
                        a_held = false;
                        break;
                    case SDLK_s:
                        s_held = false;
                        break;
                    case SDLK_d:
                        d_held = false;
                        break;
                }
            }
        }
        if (w_held) yPos -= velocity;
        if (a_held) xPos -= velocity;
        if (s_held) yPos += velocity;
        if (d_held) xPos += velocity;

        if (xPos - CIRCLE_RADIUS < 0) xPos = CIRCLE_RADIUS;
        if (xPos + CIRCLE_RADIUS > SCREEN_WIDTH) xPos = SCREEN_WIDTH - CIRCLE_RADIUS;
        if (yPos - CIRCLE_RADIUS < 0) yPos = CIRCLE_RADIUS;
        if (yPos + CIRCLE_RADIUS > SCREEN_HEIGHT) yPos = SCREEN_HEIGHT - CIRCLE_RADIUS;


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        filledCircleColor(renderer, xPos, yPos, CIRCLE_RADIUS, 0xFFFF0000);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
