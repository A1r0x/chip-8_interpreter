#include <cstdint>
#include <random>

class Chip8 {
public:
    Chip8();
	void LoadROM(char const* filename);

    uint8_t registers[16]{};
    uint8_t memory[4096]{};
    uint16_t index{};
    uint16_t pc{};
    uint16_t stack[16]{};
    uint8_t sp{};
    uint8_t delayTimer{};
    uint8_t soundTimer{};
    uint8_t keypad[16]{};
    uint32_t video[64 * 32]{};
    uint16_t opcode;

    std::default_random_engine randGen;
    std::uniform_int_distribution<uint8_t> randByte;

private:
    // CLS
    void OP_00E0();
    // RET
    void OP_00EE();
    // JP addr
    void OP_1nnn();
    // CALL addr
    void OP_2nnn();
    // SE Vx, byte
    void OP_3xkk();
    // SNE Vx, byte
    void OP_4xkk();
    // SE Vx, Vy
    void OP_5xy0();
    // LD Vx, byte
    void OP_6xkk();
    // ADD Vx, byte
    void OP_7xkk();
    // Set Vx = Vy
    void OP_8xy0();
    // OR Vx, Vy
    void OP_8xy1();
    // AND Vx, Vy
    void OP_8xy2();
    // XOR Vx, Vy
    void OP_8xy3();
};