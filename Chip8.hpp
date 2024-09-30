#include <cstdint>
#include <random>

const unsigned int VIDEO_HEIGHT = 32;
const unsigned int VIDEO_WIDTH = 64;

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
    // ADD Vx, Vy
    void OP_8xy4();
    // SUB Vx, Vy
    void OP_8xy5();
    // SHR Vx
    void OP_8xy6();
    // SUBN Vx, Vy
    void OP_8xy7();
    // SHL Vx {, Vy}
    void OP_8xyE();
    // SNE Vx, Vy
    void OP_9xy0();
    // LD I, addr
    void OP_Annn();
    // JP V0, addr
    void OP_Bnnn();
    // RND Vx, byte
    void OP_Cxkk();
    // DRW Vx, Vy, nibble
    void OP_Dxyn();
    // SKP Vx
    void OP_Ex9E();
    // SKNP Vx
    void OP_ExA1();
    // LD Vx, DT
    void OP_Fx07();
    // LD Vx, K
    void OP_Fx0A();
    // LD DT, Vx
    void OP_Fx15();
    // LD ST, Vx
    void OP_Fx18();
    // ADD I, Vx
    void OP_Fx1E();
    // LD F, Vx
    void OP_Fx29();
};