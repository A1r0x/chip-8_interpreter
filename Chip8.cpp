#include <fstream>
#include <chrono>
#include <random>
#include "Chip8.hpp"

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_SIZE = 80;
const unsigned int FONTSET_START_ADDRESS = 0x50;

uint8_t fontset[FONTSET_SIZE] = {
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() 
    : randGen(std::chrono::system_clock::now().time_since_epoch().count()) {
    // initialize pc
    pc = START_ADDRESS;

    // loads fonts into memory
    for (int i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }

    // initialize RNG
    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
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

// clear the display
void Chip8::OP_00E0() {
    memset(video, 0, sizeof(video));
}

// return from a subroutine
void Chip8::OP_00EE() {
    --sp;
    pc = stack[sp];
}

// Jump to location nnn by using bitmask to extract address from last 12 bits of opcode
void Chip8::OP_1nnn() {
    uint16_t address = opcode & 0x0FFFu;
    pc = address;
}

// call subroutine at nnn
void Chip8::OP_2nnn() {
    uint16_t address = opcode & 0x0FFFu;
    
    stack[sp] = pc;
    ++sp;
    pc = address;
}

// Skip instruction if Vx = kk
void Chip8::OP_3xkk() {
    uint8_t Vx = (opcode & 0x00F0u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;

    if (registers[Vx] == kk) {
        pc += 2;
    }
}

// Skip next instruction if Vx != kk
void Chip8::OP_4xkk() {
    uint8_t Vx = (opcode & 0x00F0u) >> 8u;
    uint8_t kk = opcode & 0x00FFu;

    if (registers[Vx] != kk) {
        pc += 2;
    }
}

// Skip next instruction if Vx = Vy
void Chip8::OP_5xy0() {
    uint8_t Vx = (opcode & 0x0F00u) >> 8u;
    uint8_t Vy = (opcode & 0x00F0u) >> 4u;

    if (registers[Vx] == registers[Vy]) {
        pc += 2;
    }
}