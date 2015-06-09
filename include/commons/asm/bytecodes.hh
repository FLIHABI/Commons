#ifndef BYTECODE_HH
# define BYTECODE_HH

/*
------------------------------------------------
VM management
------------------------------------------------
*/

enum Bytecode {
    OP_HALT = 0x00,

/*
------------------------------------------------
Stack and register management
------------------------------------------------
*/

    OP_SAVE = 0x10,
    OP_RESTORE = 0x11,
    OP_SETR = 0x12,
    OP_POP = 0x13,
    OP_PUSH = 0x17,
    OP_PUSHR = 0x18,
    OP_POPR = 0x19,

/*
------------------------------------------------
Arithmetic and bitwise
------------------------------------------------
*/

    OP_ADD = 0x20,
    OP_SUB = 0x21,
    OP_MUL = 0x22,
    OP_DIV = 0x23,
    OP_MOD = 0x24,
    OP_AND = 0x25,
    OP_OR = 0x26,
    OP_XOR = 0x27,
    OP_NOT = 0x28,
    OP_SHR = 0x29,
    OP_SHL = 0x2A,

/*
------------------------------------------------
Tests
------------------------------------------------
*/

    OP_CMP = 0x30,

/*
------------------------------------------------
Branching
------------------------------------------------
*/

    OP_CALL = 0x40,
    OP_RET = 0x41,
    OP_JMP = 0x42,
    OP_JE = 0x43,
    OP_JL = 0x44,
    OP_JG = 0x45,
    OP_JNE = 0x46,
    OP_JLE = 0x47,
    OP_JGE = 0x48,
    OP_CALLR = 0x49,
    OP_JMPS = 0x4A,

/*
------------------------------------------------
Object management
------------------------------------------------
*/

    OP_CREATE = 0x50,
    OP_DELETE = 0x51,
    OP_READ = 0x52,
    OP_WRITE = 0x53,

/*
------------------------------------------------
Parallel
------------------------------------------------
*/
    OP_PCALL = 0xA0,
    OP_PWAIT = 0xA1,
};

namespace bytecode {

    constexpr static inline bool in_range_(const Bytecode& b, int low, int high) {
        return b >= low && b <= high;
    }

    constexpr inline bool has_parameter(const Bytecode& b) {
        return ((in_range_(b, OP_PUSH, OP_POPR)
             || in_range_(b, OP_CALL, OP_CALLR)
             || b == OP_PCALL
             || in_range_(b, OP_JMP, OP_JGE)
             || in_range_(b, OP_SAVE, OP_RESTORE)) && (b != OP_RET));
    }
}

#endif /* !BYTECODE_HH */
