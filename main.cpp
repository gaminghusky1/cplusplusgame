#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <iostream>
#include "Player.h"

const int FPS = 60;
const double frameTime = 1.0 / FPS;
const int WINDOW_WIDTH = 1250;
const int WINDOW_HEIGHT = 750;

Uint32 getHex(int r, int g, int b) {
    return SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), r, g, b);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "SDL_image could not initialize! SDL_image error: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

    SDL_Surface* temp = IMG_Load("../Sprites/img.png");
    SDL_Texture* playerImg = SDL_CreateTextureFromSurface(renderer, temp);
    SDL_FreeSurface(temp);

    int playerHeight = 50;
    int playerWidth = 50;

    SDL_Rect playerRect = {WINDOW_WIDTH / 2 - playerWidth / 2, WINDOW_HEIGHT / 2 - playerHeight / 2, playerWidth, playerHeight};

    Player player = Player(playerRect, playerImg, 300);

    bool running = true;
    SDL_Event event;

    bool w_held = false;
    bool a_held = false;
    bool s_held = false;
    bool d_held = false;

    Uint64 lastTime = SDL_GetPerformanceCounter();
    double dt = 0.0;

    while (running) {
        Uint64 currentTime = SDL_GetPerformanceCounter();
        dt = static_cast<double>(currentTime - lastTime) / SDL_GetPerformanceFrequency();
        lastTime = currentTime;

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
        player.update(dt, d_held - a_held, s_held - w_held, std::make_pair(WINDOW_WIDTH, WINDOW_HEIGHT));


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // filledCircleColor(renderer, xPos, yPos, CIRCLE_RADIUS, getHex(255, 255, 255));
        // Draw player onto screen
        player.render(renderer);

        SDL_RenderPresent(renderer);

        // Ensure fps stays at 60
        if (dt < frameTime) {
            SDL_Delay((frameTime - dt) * 1000);
        }
    }

    SDL_DestroyTexture(playerImg);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
