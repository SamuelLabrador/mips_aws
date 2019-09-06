#include <stdio.h>
#include <string.h>

#include "defs.h"
#define BUFFER_SIZE 4096


typedef struct string{
	char value [16];	
	unsigned char size;
} string;

void getOpcode(unsigned int opcode, unsigned int funct, string *opcodeString){
	switch(opcode){
		case ALU:
			switch(funct){
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
				case SLL:
					strcpy(opcodeString->value, "SLL ");
					opcodeString->size = 4;
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
			}
		case ADDI:
			strcpy(opcodeString->value, "ADDI ");
			opcodeString->size = 5;
		case ADDIU:
			strcpy(opcodeString->value, "ADDIU ");
			opcodeString->size = 6;
		case ANDI:
			strcpy(opcodeString->value, "ANDI ");
			opcodeString->size = 5;
		case BEQ:
			strcpy(opcodeString->value, "BEQ ");
			opcodeString->size = 4;
		case BLEZ:
			strcpy(opcodeString->value, "BLEZ ");
			opcodeString->size = 5;
		case BNE:
			strcpy(opcodeString->value, "BNE ");
			opcodeString->size = 4;
		case BGTZ:
			strcpy(opcodeString->value, "BGTZ ");
			opcodeString->size = 5;
		case J:
			strcpy(opcodeString->value, "J ");
			opcodeString->size = 2;
		case JAL:
			strcpy(opcodeString->value, "JAL ");
			opcodeString->size = 4;
		case LB:
			strcpy(opcodeString->value, "LB ");
			opcodeString->size = 3;
		case LBU:
			strcpy(opcodeString->value, "LBU ");
			opcodeString->size = 4;
		case LHU:
			strcpy(opcodeString->value, "LHU ");
			opcodeString->size = 4;
		case LUI:
			strcpy(opcodeString->value, "LUI ");
			opcodeString->size = 4;
		case LW:
			strcpy(opcodeString->value, "LW ");
			opcodeString->size = 3;
		case MFC0:
			strcpy(opcodeString->value, "MFC0 ");
			opcodeString->size = 5;
		case ORI:
			strcpy(opcodeString->value, "ORI ");
			opcodeString->size = 4;
		case SB:
			strcpy(opcodeString->value, "SB ");
			opcodeString->size = 3;
		case SH:
			strcpy(opcodeString->value, "SH ");
			opcodeString->size = 3;
		case SLTI:
			strcpy(opcodeString->value, "SLTI ");
			opcodeString->size = 5;
		case SLTIU:
			strcpy(opcodeString->value, "SLTIU ");
			opcodeString->size = 6;
		case SW:
			strcpy(opcodeString->value, "SW ");
			opcodeString->size = 3;
	}
}

void disassemble(
	const unsigned int instructions
	// const unsigned int *instructions, 
	// unsigned char *out, 
	// unsigned int size_in,
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

	// Buffer to write string to
	unsigned char outputBuffer[BUFFER_SIZE];

	// Variables for instruction meta data
	unsigned int instruction, opcode, rs, rt, rd, shift, funct, imm;
	
	string opcodeString, rsString, rtString, rdString, shiftString, functString, immString;

	instruction = instructions;
	
	opcode = (instruction & 0xFC000000) >> 26;
	rs = (instruction >> 21) & 0x1F;
	rt = (instruction >> 16) & 0x1F;
	rd = (instruction >> 11) & 0x1F;
	shift = (instruction >> 6) & 0x1F;
	funct = instruction & 0x3F;
	imm = instruction & 0xFFFF;

	getOpcode(opcode, funct, &opcodeString);
	
	printf("%s\n", opcodeString.value);

	// opcodeString = getOpcode(opcode, &opcodeString);

	// printf("%s\n", opcodeString->value);
	// printf("%x\n", opcode);	
	// printf("%x\n", rs);	
	// printf("%x\n", rt);	
	// printf("%x\n", rd);	
	// printf("%x\n", shift);	
	// printf("%x\n", funct);	
	
}

int main(int argc, char** argv){
	if (argc < 2){
		printf("Please provide path to the file name.\n");
		return 0;
	}
	// 0001 0001 0000 0000 0000 0000 0000 0101
	// disassemble(0xAAAAAAAA);
	disassemble(0x03E0F83F);
	// printf("%s\n", argv[1]);
	return 0;

}