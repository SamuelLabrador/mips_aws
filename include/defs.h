#ifndef __DEFS_H__
#define __DEFS_H__

/* MIPS R300 INSTRUCTION SET */

// OPCODES

// ALU OPCODE
#define ALU 0

// CORRESPONDING FUNCT CODES FOR OPCODE ALU
#define SLL 0
#define SRL 2
#define SRA 3
#define SLLV 4
#define SRAV 7
#define JR 8
#define JALR 9
// #define SLTIU 11
#define SYSCALL 12
#define BREAK 13
#define MFHI 16
#define MTHI 17
#define MFLO 18
#define MTLO 19
#define MULT 24
#define MULTU 25
#define DIV 26
#define DIVU 27
#define ADD 32
#define ADDU 33
#define SUB 34
#define SUBU 35
#define AND 36
#define OR 37
#define XOR 38
#define NOR 39
#define SLT 42
#define SLTU 41

// "PC-relative" test and branch
#define TESTBRANCH 1	// OPCODE FOR TEST AND BRANCH

// Instruction [20:16] FOR TESTBRANCH OPCODE
#define BLTZ 0
#define BGEZ 1
#define BLTZAL 16
#define BGEZAL 17

// COMPARE AND BRANCH INSTRUCTIONS
#define J 2
#define JAL 3

// BRANCH INSTRUCTIONS
#define BEQ 4
#define BNE 5
#define BLEZ 6
#define BGTZ 7

// IMMEDIATE INSTRUCTIONS
#define ADDI 8
#define ADDIU 9
#define SUBI 10
#define SUBIU 11
#define ANDI 12
#define ORI 13
#define XORI 14
#define LUI 15

/* CPU CONTROL INSTRUCTION */
#define CPUCONTROL 24

/* Floating Point Operation */
#define FPOP 25 

/* LOAD AND STORE INSTRUCTIONS */
#define LB 32
#define LH 33
#define LWL 34
#define LW 35
#define LBU 36
#define LHU 37
#define LWR 38
#define SB 40
#define SH 41
#define SWL 42
#define SW 43
#define SWR 46
#define SWC1 49
#define LWC1 57

typedef enum {
	R_INSTRUCTION,
	I_INSTRUCTION,
	J_INSTRUCTION,
	L_INSTRUCTION,
	F_INSTRUCTION
}  instruction_type;

#endif