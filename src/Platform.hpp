#include <cstdint>
#include <SDL2/SDL.h>

class Platform {
public:
	// Constructor
    Platform(char const* title, int windowWidth, int windowHeight, int textureWidth, int textureHeight);
	// Destructor
	~Platform();
	// Handles drawing the graphics by updating the texture with new pixel data then rendering it to the screen
	void Update(void const* buffer, int pitch);
	bool ProcessInput(uint8_t* keys);
private:
    SDL_Window* window{};
	SDL_Renderer* renderer{};
	SDL_Texture* texture{};
};