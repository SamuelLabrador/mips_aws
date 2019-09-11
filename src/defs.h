#define ALU 0
#define ADD 32
#define ADDU 33
#define ADDI 8
#define ADDIU 9
#define AND 36
#define ANDI 12
#define BEQ 4
#define BGEZ 1
#define DIV 26
#define DIVU 27
#define MULT 24
#define MULTU 25
#define NOR 39
#define OR 37
#define ORI 13
#define BREAK 13
#define SLL 0
#define SLLV 4
#define SRA 3
#define SRAV 7
#define SRL 2
#define SRLV 6
#define SUB 34
#define SUBU 0x23
#define XOR 38
#define XORI 14
#define LHI 25
#define LLO 24
#define SLT 42
#define SLTU 41
#define SLTI 10
#define SLTIU 11
#define BGTZ 7
#define BLEZ 6
#define BNE 5
#define J 2
#define JAL 3
#define JALR 9
#define JR 8
#define LB 32
#define LBU 36
#define LH 33
#define LW 35
#define SB 40
#define SH 41
#define SW 43
#define MFHI 16
#define MFLO 18
#define MTHI 17
#define MTLO 19
#define TRAP 26
#define LUI 15
#define LHU 37
#define MFC0 16
#define SYSCALL 12

typedef enum {
	R_INSTRUCTION,
	I_INSTRUCTION,
	J_INSTRUCTION,
	L_INSTRUCTION
}  instruction_type;