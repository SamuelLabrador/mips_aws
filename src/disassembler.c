#define STRING_SIZE 32
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


#define INPUT_BUFFER 1024
#define BUFFER_SIZE INPUT_BUFFER * 32
#include <stdio.h>

typedef enum {
	R_INSTRUCTION,
	I_INSTRUCTION,
	J_INSTRUCTION,
	L_INSTRUCTION,
	F_INSTRUCTION
}  instruction_type;

typedef struct{
	char value[STRING_SIZE];		// ARRAY SIZE NEEDS TO BE PREDIFNED FOR HLS
	unsigned int size;	
} fpga_string;


void fpga_str_init(fpga_string *target, char *value){
	int i = 0;
	
	while(value[i] != '\0'){
		target->value[i] = value[i];
		i++;
	}

	target->value[i] = '\0';
	target->size = i;
}

// unsigned int fpga_str_init(fpga_string *target, fpga_string 6source){
// 	int i;
	
// 	for(i = 0; i <= source->size; i++){
// // #pragma HLS unroll
// 		target->value[i] = source->value[i];
// 	}
// 	target->size = source->size;
// 	return i;
// }

void fpga_str_insert(fpga_string * target, fpga_string *source, unsigned int index, unsigned int size){
	int i;

	for(i = 0; i < size; i++){
		if(source->value[i] != '\0'){
			target->value[index + i] = source->value[i];
		}
		else{
			target->value[index + i] = 0x20;
		}
	}
}

// unsigned int fpga_str_insert(fpga_string* target, fpga_string *rhs){
	// return fpga_str_insert(target, rhs, target->size);
// }

// Appends integer in string representation to the end of the string
unsigned int fpga_str_int(fpga_string *target, int source){
	
	int i = target->size;

	int mod = 1;
	while(source > (mod * 10)){	// Get upper bound of mod.
		mod *= 10;
	}

	while(mod != 0){
		target->value[i] = '0' + (source / mod);
		
		source = source % mod;
		mod /= 10;
		i++;
	}

	while(i < 4){
		target->value[i] = ' ';
		i++;
	}
	target->value[i] = '\0';

	return i;
}


void getOpcode(unsigned int opcode, unsigned int funct, fpga_string *opcodeString){
	switch(opcode){
		case ALU:
			switch(funct){
				case SLL:
					fpga_str_init(opcodeString, "SLL ");
					break;
				case SRL:
					fpga_str_init(opcodeString, "SRL ");
					break;
				case SRA:	
					fpga_str_init(opcodeString, "SRA ");
					break;
				case SLLV:
					fpga_str_init(opcodeString, "SLLV ");
					break;
				case SRAV:
					fpga_str_init(opcodeString, "SRAV ");
					break;
				case JR:
					fpga_str_init(opcodeString, "JR ");
					break;
				case JALR:
					fpga_str_init(opcodeString, "JALR ");
					break;
				case ADD:
					fpga_str_init(opcodeString, "ADD ");
					break;
				case ADDU:
					fpga_str_init(opcodeString, "ADDU ");
					break;
				case AND:
					fpga_str_init(opcodeString, "AND ");
					break;
				case DIV:
					fpga_str_init(opcodeString, "DIV ");
					break;
				case DIVU:
					fpga_str_init(opcodeString, "DIVU ");
					break;
				case MFHI:
					fpga_str_init(opcodeString, "MFHI ");
					break;
				case MTHI:
					fpga_str_init(opcodeString, "MTHI ");
					break;
				case MFLO:
					fpga_str_init(opcodeString, "MFLO ");
					break;
				case MTLO:
					fpga_str_init(opcodeString, "MTLO ");
					break;
				case MULT:
					fpga_str_init(opcodeString, "MULT ");
				case MULTU:
					fpga_str_init(opcodeString, "MULTU ");
					break;
				case NOR:
					fpga_str_init(opcodeString, "NOR ");
					break;
				case XOR:
					fpga_str_init(opcodeString, "XOR ");
					break;
				case OR:
					fpga_str_init(opcodeString, "OR ");
					break;
				case SLT:
					fpga_str_init(opcodeString, "SLT ");
					break;
				case SLTU:
					fpga_str_init(opcodeString, "SLTU ");
					break;
				case SUB:
					fpga_str_init(opcodeString, "SUB ");
					break;
				case SUBU:
					fpga_str_init(opcodeString, "SUBU ");
					break;
				case SUBIU:
					fpga_str_init(opcodeString, "SUBIU ");
					break;	
				case BREAK:
					fpga_str_init(opcodeString, "BREAK ");
					break;
				case SYSCALL:
					fpga_str_init(opcodeString, "SYSCALL ");
					break;
			}
			break;
		case J:
			fpga_str_init(opcodeString, "J ");
			break;
		case JAL:
			fpga_str_init(opcodeString, "JAL ");
			break;
		case ADDI:
			fpga_str_init(opcodeString, "ADDI ");
			break;
		case ADDIU:
			fpga_str_init(opcodeString, "ADDIU ");
			break;	
		case ANDI:
			fpga_str_init(opcodeString, "ANDI ");
			break;
		case BEQ:
			fpga_str_init(opcodeString, "BEQ ");
			break;
		case BGEZ:
			fpga_str_init(opcodeString, "BGEZ ");
			break;
		case BLEZ:
			fpga_str_init(opcodeString, "BLEZ ");
			break;
		case BNE:
			fpga_str_init(opcodeString, "BNE ");
			break;
		case BGTZ:
			fpga_str_init(opcodeString, "BGTZ ");
			break;
		case LB:
			fpga_str_init(opcodeString, "LB ");
			break;
		case LH:
			fpga_str_init(opcodeString, "LH ");
			break;
		case LWL:
			fpga_str_init(opcodeString, "LWL ");
			break;
		case LW:
			fpga_str_init(opcodeString, "LW ");
			break;
		case LBU:
			fpga_str_init(opcodeString, "LBU ");
			break;
		case LHU:
			fpga_str_init(opcodeString, "LHU ");
			break;
		case LWR:
			fpga_str_init(opcodeString, "LWR ");
			break;
		case LUI:
			fpga_str_init(opcodeString, "LUI ");
			break;
		case ORI:
			fpga_str_init(opcodeString, "ORI ");
			break;
		case XORI:
			fpga_str_init(opcodeString, "XORI ");
			break;
		case SB:
			fpga_str_init(opcodeString, "SB ");
			break;
		case SH:
			fpga_str_init(opcodeString, "SH ");
			break;
		case SWL:
			fpga_str_init(opcodeString, "SWL ");
			break;
		case SW:
			fpga_str_init(opcodeString, "SW ");
			break;
		case SWR:
			fpga_str_init(opcodeString, "SWR ");
			break;
		case SWC1:
			fpga_str_init(opcodeString, "SWC1 ");
			break;
		case LWC1:
			fpga_str_init(opcodeString, "LWC1 ");
			break;
		default:
			fpga_str_init(opcodeString, "UNK ");
	}
}

void getRegister(unsigned int reg, fpga_string *registerString){
	if(reg == 0){
		fpga_str_init(registerString, "zero");
	}
	else if(reg == 1){
		fpga_str_init(registerString, "at  ");
	}
	else if(reg == 2 && reg == 3){
		fpga_str_init(registerString, "v");
		fpga_str_int(registerString, reg);
	}
	else if(reg >= 4 && reg <= 7){
		fpga_str_init(registerString, "a");
		fpga_str_int(registerString, reg - 4);
	}
	else if(reg >= 8 && reg <= 15){
		fpga_str_init(registerString, "t");
		fpga_str_int(registerString, reg - 8);
	}
	else if(reg >= 16 && reg <= 23){
		fpga_str_init(registerString, "s");
		fpga_str_int(registerString, reg - 16);
	}
	else if(reg >= 24 && reg <= 25){
		fpga_str_init(registerString, "t");
		fpga_str_int(registerString, reg - 16);
	}
	else if(reg >= 26 && reg <= 27){
		fpga_str_init(registerString, "k");
		fpga_str_int(registerString, reg - 26);
	}
}

void getImmediate(int imm, fpga_string *registerString){
	fpga_str_int(registerString, imm);
}

instruction_type getInstructionType(unsigned int opcode){
	if(opcode == 0){
		return R_INSTRUCTION;
	}
	if(opcode == 2 || opcode == 3){
		return J_INSTRUCTION;
	}
	if(opcode >= 8 && opcode <= 15){
		return I_INSTRUCTION;
	}
	return L_INSTRUCTION;
}

void disassembler(
	unsigned char instructions[INPUT_BUFFER], 
	unsigned char out[BUFFER_SIZE], 
	unsigned int size_in
	){

	#pragma HLS INTERFACE m_axi port=instructions  offset=slave bundle=gmem
	#pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem
	
	#pragma HLS INTERFACE s_axilite port=instructions  bundle=control
	#pragma HLS INTERFACE s_axilite port=out bundle=control

	#pragma HLS INTERFACE s_axilite port=size_in bundle=control

	#pragma HLS INTERFACE s_axilite port=return bundle=control

	// Buffer to write fpga_string to
	unsigned char outputBuffer[BUFFER_SIZE];
	unsigned int bufferPosition = 0;

	// Variables for instruction meta data
	unsigned int instruction, opcode, rs, rt, rd, shift, funct, imm;

	// String declerations	
	fpga_string opcodeString, rsString, rtString, rdString, shiftString, functString, immString, instructionString, null;

	fpga_string tab, space, newline, lparen, rparen, comma;
	
	fpga_str_init(&tab, "\t");
	fpga_str_init(&comma, ",");
	fpga_str_init(&newline, "\n");
	fpga_str_init(&lparen, "(");
	fpga_str_init(&rparen, ")");
	fpga_str_init(&null, "\0");

	unsigned int i;

	for(i = 0; i < size_in; i ++){
		#pragma HLS PIPELINE
		instruction = 	(instructions[(i * 4)] << 24) | 
						(instructions[(i * 4) + 1] << 16)|
						(instructions[(i * 4) + 2] << 8) |
						(instructions[(i * 4) + 3]);

		// Get appropriate values of instruction	
		opcode = (instruction & 0xFC000000) >> 26;
		rs = (instruction >> 21) & 0x1F;
		rt = (instruction >> 16) & 0x1F;
		rd = (instruction >> 11) & 0x1F;
		shift = (instruction >> 6) & 0x1F;
		funct = instruction & 0x3F;
		imm = instruction & 0xFFFF;

		// // GET ALL POSSIBLE INSTRUCTION PIECES IN PARALLEL
		getOpcode(opcode, funct, &opcodeString);
		getRegister(rs, &rsString);
		getRegister(rt, &rtString);
		getRegister(rd, &rdString);
		getImmediate(imm, &immString);

		int k;

		// FIGURE OUT STRING FORMAT FOR INSTRUCTION
		switch(getInstructionType(opcode)){
			case R_INSTRUCTION:
				fpga_str_insert(&instructionString, &opcodeString, 0, 8);
				fpga_str_insert(&instructionString, &rsString, 8, 6);
				fpga_str_insert(&instructionString, &rtString, 14, 6);
				fpga_str_insert(&instructionString, &rdString, 20, 6);
				fpga_str_insert(&instructionString, &null, 26, 1);
				break;
			case J_INSTRUCTION:
				fpga_str_insert(&instructionString, &opcodeString, 0, 8);
				fpga_str_insert(&instructionString, &immString, 8, 20);
				fpga_str_insert(&instructionString, &null, 28, 1);
				break;
			case L_INSTRUCTION:
				fpga_str_insert(&instructionString, &opcodeString, 0, 8);
				fpga_str_insert(&instructionString, &immString, 8, 16);
				fpga_str_insert(&instructionString, &lparen, 16, 1);
				fpga_str_insert(&instructionString, &rsString, 17, 6);
				fpga_str_insert(&instructionString, &rparen, 23, 2);
				fpga_str_insert(&instructionString, &null, 25, 1);
				break;
			default:
				fpga_str_insert(&instructionString, &opcodeString, 0, 8);
				fpga_str_insert(&instructionString, &rsString, 8, 6);
				fpga_str_insert(&instructionString, &rtString, 14, 6);
				fpga_str_insert(&instructionString, &immString, 20, 8);
				fpga_str_insert(&instructionString, &null, 28, 1);
				break;
		}

		// // WRITE STRING TO BUFFER
		// // USE PRAMA TO OPTIMIZE PIPELINE
		for(unsigned int j = 0; j < 32; j++){
			#pragma HLS unroll
			outputBuffer[j + bufferPosition] = instructionString.value[j];
		}
		bufferPosition += 32;
		// printf("%s\t%x\n", instructionString.value, instruction);
	}
	
	for(i = 0; i < BUFFER_SIZE; i++){
		out[i] = outputBuffer[i];
	}

}