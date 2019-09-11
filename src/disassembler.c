#include <string.h>
#include <stdio.h>

#include "defs.h"
#include "fpga_string.h"


#define BUFFER_SIZE 4096

// typedef struct fpga_string{
// 	char value [32];	
// 	unsigned char size;
// } fpga_string;

void getOpcode(unsigned int opcode, unsigned int funct, fpga_string *opcodeString){
	switch(opcode){
		case ALU:
			switch(funct){
				case SLL:
					strcpy(opcodeString->value, "SLL ");
					opcodeString->size = 4;
				case ADD:
					strcpy(opcodeString->value, "ADD ");
					opcodeString->size = 4;
				case ADDU:
					strcpy(opcodeString->value, "ADDU ");
					opcodeString->size = 5;
				case AND:
					strcpy(opcodeString->value, "AND ");
					opcodeString->size = 4;
				case DIV:
					strcpy(opcodeString->value, "DIV ");
					opcodeString->size = 4;
				case DIVU:
					strcpy(opcodeString->value, "DIVU ");
					opcodeString->size = 5;
				case JR:
					strcpy(opcodeString->value, "JR ");
					opcodeString->size = 3;
				case MFHI:
					strcpy(opcodeString->value, "MFHI ");
					opcodeString->size = 5;
				case MTHI:
					strcpy(opcodeString->value, "MTHI ");
					opcodeString->size = 5;
				case MFLO:
					strcpy(opcodeString->value, "MFLO ");
					opcodeString->size = 5;
				case MTLO:
					strcpy(opcodeString->value, "MTLO ");
					opcodeString->size = 5;
				case MULT:
					strcpy(opcodeString->value, "MULT ");
					opcodeString->size = 5;
				case MULTU:
					strcpy(opcodeString->value, "MULTU ");
					opcodeString->size = 6;
				case NOR:
					strcpy(opcodeString->value, "NOR ");
					opcodeString->size = 4;
				case XOR:
					strcpy(opcodeString->value, "XOR ");
					opcodeString->size = 4;
				case OR:
					strcpy(opcodeString->value, "OR ");
					opcodeString->size = 3;
				case SLT:
					strcpy(opcodeString->value, "SLT ");
					opcodeString->size = 4;
				case SLTU:
					strcpy(opcodeString->value, "SLTU ");
					opcodeString->size = 5;
				case SRL:
					strcpy(opcodeString->value, "SRL ");
					opcodeString->size = 4;
				case SRA:
					strcpy(opcodeString->value, "SRA ");
					opcodeString->size = 4;
				case SUB:
					strcpy(opcodeString->value, "SUB ");
					opcodeString->size = 4;
				case SUBU:
					strcpy(opcodeString->value, "SUBU ");
					opcodeString->size = 5;
				case BREAK:
					strcpy(opcodeString->value, "BREAK ");
					opcodeString->size = 6;
				case SYSCALL:
					strcpy(opcodeString->value, "SYSCALL ");
					opcodeString->size = 8;
				case JALR:
					strcpy(opcodeString->value, "JALR ");
					opcodeString->size = 5;
			}
			break;
		case ADDI:
			strcpy(opcodeString->value, "ADDI ");
			opcodeString->size = 5;
			break;
		case ADDIU:
			strcpy(opcodeString->value, "ADDIU ");
			opcodeString->size = 6;
			break;	
		case ANDI:
			strcpy(opcodeString->value, "ANDI ");
			opcodeString->size = 5;
			break;
		case BEQ:
			strcpy(opcodeString->value, "BEQ ");
			opcodeString->size = 4;
			break;
		case BGEZ:
			strcpy(opcodeString->value, "BGEZ ");
			opcodeString->size = 4;
			break;
		case BLEZ:
			strcpy(opcodeString->value, "BLEZ ");
			opcodeString->size = 5;
			break;
		case BNE:
			strcpy(opcodeString->value, "BNE ");
			opcodeString->size = 4;
			break;
		case BGTZ:
			strcpy(opcodeString->value, "BGTZ ");
			opcodeString->size = 5;
			break;
		case J:
			strcpy(opcodeString->value, "J ");
			opcodeString->size = 2;
			break;
		case JAL:
			strcpy(opcodeString->value, "JAL ");
			opcodeString->size = 4;
			break;
		case LB:
			strcpy(opcodeString->value, "LB ");
			opcodeString->size = 3;
			break;
		case LBU:
			strcpy(opcodeString->value, "LBU ");
			opcodeString->size = 4;
			break;
		case LHU:
			strcpy(opcodeString->value, "LHU ");
			opcodeString->size = 4;
			break;
		case LUI:
			strcpy(opcodeString->value, "LUI ");
			opcodeString->size = 4;
			break;
		case LW:
			strcpy(opcodeString->value, "LW ");
			opcodeString->size = 3;
			break;
		case MFC0:
			strcpy(opcodeString->value, "MFC0 ");
			opcodeString->size = 5;
			break;
		case ORI:
			strcpy(opcodeString->value, "ORI ");
			opcodeString->size = 4;
			break;
		case SB:
			strcpy(opcodeString->value, "SB ");
			opcodeString->size = 3;
			break;
		case SH:
			strcpy(opcodeString->value, "SH ");
			opcodeString->size = 3;
			break;
		case SLTI:
			strcpy(opcodeString->value, "SLTI ");
			opcodeString->size = 5;
			break;
		case SLTIU:
			strcpy(opcodeString->value, "SLTIU ");
			opcodeString->size = 6;
			break;
		case SW:
			strcpy(opcodeString->value, "SW ");
			opcodeString->size = 3;
			break;
		default:
			strcpy(opcodeString->value, "UNK ");
			opcodeString->size = 4;
	}
}

void getRegister(unsigned int reg, fpga_string *registerString){
	if(reg == 0){
		strcpy(registerString->value, "$zero");
		registerString->size = 5;
	}
	else if(reg == 1){
		strcpy(registerString->value, "$at");
		registerString->size = 3;
	}
	else if(reg == 2 && reg == 3){
		sprintf(registerString->value, "$v%d", reg - 2);
		registerString->size = 2;
	}
	else if(reg >= 4 && reg <= 7){
		sprintf(registerString->value, "$a%d", reg - 4);
		registerString->size = 	2;
	}
	else if(reg >= 8 && reg <= 15){
		sprintf(registerString->value, "$t%d", reg - 8);
		registerString->size = 	2;	
	}
	else if(reg >= 16 && reg <= 23){
		sprintf(registerString->value, "$s%d", reg - 16);
		registerString->size = 	2;	
	}
	else if(reg >= 24 && reg <= 25){
		sprintf(registerString->value, "$t%d", reg - 16);
		registerString->size = 	2;	
	}
	else if(reg >= 26 && reg <= 27){
		sprintf(registerString->value, "$k%d", reg - 26);
		registerString->size = 	3;	
	}
}

void getImmediate(int imm, fpga_string *registerString){
	sprintf(registerString->value, "%d", imm);
	registerString->size = strlen(registerString->value);
}

instruction_type getInstructionType(unsigned int opcode){
	if(opcode == 0){
		return R_INSTRUCTION;
	}
	if(opcode >= 2 && opcode <= 3){
		return J_INSTRUCTION;
	}
	if(opcode >= 8 && opcode <= 15){
		return I_INSTRUCTION;
	}
	// if(opcode >= 32 && opcode <= 57){
	// printf("L INSTRUCTION");
	return L_INSTRUCTION;
	// }
}

void disassemble(
	unsigned char *instructions, 
	// unsigned char *out, 
	unsigned int size_in
	// unsigned int size_out
	){

	// #pragma HLS INTERFACE m_axi port=in1  offset=slave bundle=gmem
	// #pragma HLS INTERFACE m_axi port=in2  offset=slave bundle=gmem
	// #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem
	// #pragma HLS INTERFACE s_axilite port=in1  bundle=control
	// #pragma HLS INTERFACE s_axilite port=in2  bundle=control
	// #pragma HLS INTERFACE s_axilite port=out bundle=control
	// #pragma HLS INTERFACE s_axilite port=size bundle=control
	// #pragma HLS INTERFACE s_axilite port=return bundle=control

	// Buffer to write fpga_string to
	unsigned char outputBuffer[BUFFER_SIZE];
	unsigned int bufferPosition = 0;

	// Variables for instruction meta data
	unsigned int instruction, opcode, rs, rt, rd, shift, funct, imm;

	// String declerations	
	fpga_string opcodeString, rsString, rtString, rdString, shiftString, functString, immString, instructionString;

	printf("%d\n", size_in);

	for(int i = 0; i < size_in; i += 4){
		instruction = 	(instructions[i] << 24) | 

						(instructions[i + 1] << 16)|
						(instructions[i + 2] << 8) |
						(instructions[i + 3])	;
		// Get appropriate values of instruction	
		opcode = (instruction & 0xFC000000) >> 26;
		rs = (instruction >> 21) & 0x1F;
		rt = (instruction >> 16) & 0x1F;
		rd = (instruction >> 11) & 0x1F;
		shift = (instruction >> 6) & 0x1F;
		funct = instruction & 0x3F;
		imm = instruction & 0xFFFF;

		// GET ALL POSSIBLE INSTRUCTION PIECES IN PARALLEL
		getOpcode(opcode, funct, &opcodeString);
		// printf("%d | %d ", opcode, funct);
		getRegister(rs, &rsString);
		getRegister(rt, &rtString);
		getRegister(rd, &rdString);
		getImmediate(imm, &immString);

		// FIGURE OUT STRING FORMAT FOR INSTRUCTION
		switch(getInstructionType(opcode)){
			case R_INSTRUCTION:
				sprintf(instructionString.value, "%s%s, %s, %s\n", opcodeString.value, rsString.value, rtString.value, rdString.value);
				instructionString.size = opcodeString.size + rsString.size + rtString.size + rdString.size + 5;
				break;
			case J_INSTRUCTION:
				sprintf(instructionString.value, "%s%s\n", opcodeString.value, immString.value);
				instructionString.size = opcodeString.size + immString.size + 2;
				break;
			case L_INSTRUCTION:
				sprintf(instructionString.value, "%s%s %s(%s)\n", opcodeString.value, rtString.value, immString.value, rsString.value);
				instructionString.size = opcodeString.size + rtString.size + immString.size + rsString.size + 4;
				break;
			default:
				sprintf(instructionString.value, "%s %s, %s, %s\n", opcodeString.value, rsString.value, rtString.value, immString.value);
				instructionString.size = opcodeString.size + rsString.size + rtString.size + immString.size + 2;
		}
		printf("%s", instructionString.value);
		// WRITE STRING TO BUFFER
		// USE PRAMA TO OPTIMIZE PIPELINE
		for(unsigned int j = 0; j < (instructionString.size); j++){
			outputBuffer[j + bufferPosition] = instructionString.value[j];
		}
		bufferPosition += instructionString.size;
	}
	// printf("%s", outputBuffer);
	for(int i = 0; i < bufferPosition; i++){
		// out[i] = outputBuffer[i];
	}
	// printf("%s", out);
}

// int main(int argc, char** argv){

// 	if (argc < 2){
// 		printf("Please provide path to the file name.\n");
// 		return 0;
// 	}

	
	
	// disassemble(0xAAAAAAAA);
	// disassemble(0x0123F83F);
	// printf("%s\n", argv[1]);
	// return 0;

// }
