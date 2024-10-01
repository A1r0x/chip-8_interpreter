#include "Platform.hpp"
#include <cstdint>
#include <SDL.h>
#include <SDL_render.h>

Platform::Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight) {
    // Initializes SDL library with video subsystem to enable graphics
    SDL_init(SDL_INIT_VIDEO);
    // Creates a window with the given title, width, and height
    window = SDL_CreateWindow(title, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    // Creates a renderer to handle rendering within the window, using hardware acceleration 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // Creates a texture to store pixel data for the display, in RGBA8888 format with streaming access
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight);
}

Platform::~Platform() {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}