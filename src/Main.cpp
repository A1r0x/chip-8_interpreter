#include <chrono>
#include <iostream>
#include "Platform.hpp"
#include "Chip8.hpp"

int main(int argc, char** argv) {
    // if the user doesn't provide the correct number of arguments (4), print error and exit
    if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <Scale> <Delay> <ROM>\n";
		std::exit(EXIT_FAILURE);
	}

    // this value determines how large the emulator window will be scaled
    int videoScale = std::stoi(argv[1]);
    // this value controls how long the emulator waits between each emulation cycle
	int cycleDelay = std::stoi(argv[2]);
    // Stores the path of the ROM file (third argument) as a C-style string
	char const* romFilename = argv[3];

    // creates an instance of the Platform class, initializing the SDL window and renderer.
	Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale, VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	Chip8 chip8;
	chip8.LoadROM(romFilename);

    // number of bytes per row of the screen that will be updated in the SDL texture
	int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

    // records the current time, which will be used to measure time intervals between emulation cycles
	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

    // handles input processing, runs the emulation cycles, and updates the display
	while (!quit)
	{
        // checks for user inputs and updates the chip8.keypad array accordingly
		quit = platform.ProcessInput(chip8.keypad);

        // calculates the time difference between the current time and the last time the emulation cycle was run
		auto currentTime = std::chrono::high_resolution_clock::now();
		float dt = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - lastCycleTime).count();

        // If enough time has passed, the emulator runs one CPU cycle via chip8.Cycle()
		if (dt > cycleDelay)
		{
			lastCycleTime = currentTime;

			chip8.Cycle();

			platform.Update(chip8.video, videoPitch);
		}
	}

	return 0;
}