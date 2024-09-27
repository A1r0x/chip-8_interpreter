#include <fstream>
#include "Chip8.hpp"

const unsigned int START_ADDRESS = 0x200;

Chip8::Chip8() {
    // initialize pc
    pc = START_ADDRESS;
}

void Chip8::LoadROM(char const* filename) {
    // opens file in binary mode and sets file pointer to end
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open()) {
        // get size of file and allocate buffer of that size to hold contents
        std::streampos size = file.tellg();
        char* buffer = new char[size];
        
        // set file pointer to beginning then fill buffer
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        // load ROM contents into CHIP8's memory, starting at 0x200
        for (int i = 0; i < size; i++) {
            memory[START_ADDRESS + i] = buffer[i];
        }

        // free buffer
        delete[] buffer;
    }
}