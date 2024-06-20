#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// Platform class definition
class Platform {
public:
    virtual vector<uint8_t> encode(const string& instruction, const vector<string>& operands) = 0;
    virtual ~Platform() {}
};

// x86 Platform class definition
class x86Platform : public Platform {
private:
    map<string, uint8_t> instructionMap = {
        {"mov", 0xB8},
        {"add", 0x05},
        {"sub", 0x2D}
    };

    map<string, uint8_t> registerMap = {
        {"eax", 0x00},
        {"ebx", 0x03},
        {"ecx", 0x01},
        {"edx", 0x02}
    };

public:
    vector<uint8_t> encode(const string& instruction, const vector<string>& operands) override {
        vector<uint8_t> machineCode;
        if (instructionMap.find(instruction) != instructionMap.end() && registerMap.find(operands[0]) != registerMap.end()) {
            machineCode.push_back(instructionMap[instruction] + registerMap[operands[0]]);
            int32_t imm = stoi(operands[1]);
            for (int i = 0; i < 4; ++i) {
                machineCode.push_back((imm >> (i * 8)) & 0xFF);
            }
        }
        return machineCode;
    }
};

// RISC-V Platform class definition
class RiscVPlatform : public Platform {
private:
    enum RiscVOpcode {
        OP_IMM = 0x13,
        LOAD = 0x03,
        STORE = 0x23
    };

    map<string, uint8_t> registerMap = {
        {"x0", 0x00}, {"x1", 0x01}, {"x2", 0x02}, {"x3", 0x03},
        {"x4", 0x04}, {"x5", 0x05}, {"x6", 0x06}, {"x7", 0x07},
        {"x8", 0x08}, {"x9", 0x09}, {"x10", 0x0A}, {"x11", 0x0B},
        {"x12", 0x0C}, {"x13", 0x0D}, {"x14", 0x0E}, {"x15", 0x0F},
        {"x16", 0x10}, {"x17", 0x11}, {"x18", 0x12}, {"x19", 0x13},
        {"x20", 0x14}, {"x21", 0x15}, {"x22", 0x16}, {"x23", 0x17},
        {"x24", 0x18}, {"x25", 0x19}, {"x26", 0x1A}, {"x27", 0x1B},
        {"x28", 0x1C}, {"x29", 0x1D}, {"x30", 0x1E}, {"x31", 0x1F}
    };

public:
    vector<uint8_t> encode(const string& instruction, const vector<string>& operands) override {
        vector<uint8_t> machineCode(4, 0);
        if (instruction == "addi") {
            int32_t imm = stoi(operands[2]);
            machineCode[0] = (imm & 0xFF);
            machineCode[1] = ((imm >> 8) & 0x0F) | (registerMap[operands[1]] << 4);
            machineCode[2] = (registerMap[operands[0]] << 4) | ((imm >> 12) & 0x0F);
            machineCode[3] = OP_IMM;
        }
        return machineCode;
    }
};


int main() {
    auto x86 = new x86Platform();
    auto riscv = new RiscVPlatform();

    vector<string> x86Operands = {"eax", "42"};
    auto x86Code = x86->encode("mov", x86Operands);
    cout << "x86 Machine Code for 'mov eax, 42': ";
    for (auto byte : x86Code) {
        cout << hex << static_cast<int>(byte) << " ";
    }
    cout << endl;

    vector<string> riscvOperands = {"x1", "x0", "42"};
    auto riscvCode = riscv->encode("addi", riscvOperands);
    cout << "RISC-V Machine Code for 'addi x1, x0, 42': ";
    for (auto byte : riscvCode) {
        cout << hex << static_cast<int>(byte) << " ";
    }
    cout << endl;

    delete x86;
    delete riscv;

    return 0;
}
