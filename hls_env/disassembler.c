#include "disassembler.h"

void getOpcode(unsigned int opcode, unsigned int funct, fpga_string *opcodeString){
	switch(opcode){
		case ALU:
			switch(funct){
				case SLL:
					fpga_str_char_cpy(opcodeString, "SLL ");
					break;
				case SRL:
					fpga_str_char_cpy(opcodeString, "SRL ");
					break;
				case SRA:	
					fpga_str_char_cpy(opcodeString, "SRA ");
					break;
				case SLLV:
					fpga_str_char_cpy(opcodeString, "SLLV ");
					break;
				case SRAV:
					fpga_str_char_cpy(opcodeString, "SRAV ");
					break;
				case JR:
					fpga_str_char_cpy(opcodeString, "JR ");
					break;
				case JALR:
					fpga_str_char_cpy(opcodeString, "JALR ");
					break;
				case ADD:
					fpga_str_char_cpy(opcodeString, "ADD ");
					break;
				case ADDU:
					fpga_str_char_cpy(opcodeString, "ADDU ");
					break;
				case AND:
					fpga_str_char_cpy(opcodeString, "AND ");
					break;
				case DIV:
					fpga_str_char_cpy(opcodeString, "DIV ");
					break;
				case DIVU:
					fpga_str_char_cpy(opcodeString, "DIVU ");
					break;
				case MFHI:
					fpga_str_char_cpy(opcodeString, "MFHI ");
					break;
				case MTHI:
					fpga_str_char_cpy(opcodeString, "MTHI ");
					break;
				case MFLO:
					fpga_str_char_cpy(opcodeString, "MFLO ");
					break;
				case MTLO:
					fpga_str_char_cpy(opcodeString, "MTLO ");
					break;
				case MULT:
					fpga_str_char_cpy(opcodeString, "MULT ");
					break;
				case MULTU:
					fpga_str_char_cpy(opcodeString, "MULTU ");
					break;
				case NOR:
					fpga_str_char_cpy(opcodeString, "NOR ");
					break;
				case XOR:
					fpga_str_char_cpy(opcodeString, "XOR ");
					break;
				case OR:
					fpga_str_char_cpy(opcodeString, "OR ");
					break;
				case SLT:
					fpga_str_char_cpy(opcodeString, "SLT ");
					break;
				case SLTU:
					fpga_str_char_cpy(opcodeString, "SLTU ");
					break;
				case SUB:
					fpga_str_char_cpy(opcodeString, "SUB ");
					break;
				case SUBU:
					fpga_str_char_cpy(opcodeString, "SUBU ");
					break;
				case SUBIU:
					fpga_str_char_cpy(opcodeString, "SUBIU ");
					break;	
				case BREAK:
					fpga_str_char_cpy(opcodeString, "BREAK ");
					break;
				case SYSCALL:
					fpga_str_char_cpy(opcodeString, "SYSCALL ");
					break;
			}
			break;
		case J:
			fpga_str_char_cpy(opcodeString, "J ");
			break;
		case JAL:
			fpga_str_char_cpy(opcodeString, "JAL ");
			break;
		case ADDI:
			fpga_str_char_cpy(opcodeString, "ADDI ");
			break;
		case ADDIU:
			fpga_str_char_cpy(opcodeString, "ADDIU ");
			break;	
		case ANDI:
			fpga_str_char_cpy(opcodeString, "ANDI ");
			break;
		case BEQ:
			fpga_str_char_cpy(opcodeString, "BEQ ");
			break;
		case BGEZ:
			fpga_str_char_cpy(opcodeString, "BGEZ ");
			break;
		case BLEZ:
			fpga_str_char_cpy(opcodeString, "BLEZ ");
			break;
		case BNE:
			fpga_str_char_cpy(opcodeString, "BNE ");
			break;
		case BGTZ:
			fpga_str_char_cpy(opcodeString, "BGTZ ");
			break;
		case LB:
			fpga_str_char_cpy(opcodeString, "LB ");
			break;
		case LH:
			fpga_str_char_cpy(opcodeString, "LH ");
			break;
		case LWL:
			fpga_str_char_cpy(opcodeString, "LWL ");
			break;
		case LW:
			fpga_str_char_cpy(opcodeString, "LW ");
			break;
		case LBU:
			fpga_str_char_cpy(opcodeString, "LBU ");
			break;
		case LHU:
			fpga_str_char_cpy(opcodeString, "LHU ");
			break;
		case LWR:
			fpga_str_char_cpy(opcodeString, "LWR ");
			break;
		case LUI:
			fpga_str_char_cpy(opcodeString, "LUI ");
			break;
		case ORI:
			fpga_str_char_cpy(opcodeString, "ORI ");
			break;
		case XORI:
			fpga_str_char_cpy(opcodeString, "XORI ");
			break;
		case SB:
			fpga_str_char_cpy(opcodeString, "SB ");
			break;
		case SH:
			fpga_str_char_cpy(opcodeString, "SH ");
			break;
		case SWL:
			fpga_str_char_cpy(opcodeString, "SWL ");
			break;
		case SW:
			fpga_str_char_cpy(opcodeString, "SW ");
			break;
		case SWR:
			fpga_str_char_cpy(opcodeString, "SWR ");
			break;
		case SWC1:
			fpga_str_char_cpy(opcodeString, "SWC1 ");
			break;
		case LWC1:
			fpga_str_char_cpy(opcodeString, "LWC1 ");
			break;
		default:
			fpga_str_char_cpy(opcodeString, "UNK ");
	}
}

void getRegister(unsigned int reg, fpga_string *registerString){
	if(reg == 0){
		fpga_str_char_cpy(registerString, "zero");
	}
	else if(reg == 1){
		fpga_str_char_cpy(registerString, "at");
	}
	else if(reg == 2 && reg == 3){
		fpga_str_char_cpy(registerString, "v");
		fpga_str_int(registerString, reg);
	}
	else if(reg >= 4 && reg <= 7){
		fpga_str_char_cpy(registerString, "a");
		fpga_str_int(registerString, reg - 4);
	}
	else if(reg >= 8 && reg <= 15){
		fpga_str_char_cpy(registerString, "t");
		fpga_str_int(registerString, reg - 8);
	}
	else if(reg >= 16 && reg <= 23){
		fpga_str_char_cpy(registerString, "s");
		fpga_str_int(registerString, reg - 16);
	}
	else if(reg >= 24 && reg <= 25){
		fpga_str_char_cpy(registerString, "t");
		fpga_str_int(registerString, reg - 16);
	}
	else if(reg >= 26 && reg <= 27){
		fpga_str_char_cpy(registerString, "k");
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
	else if(opcode == 2 || opcode == 3){
		return J_INSTRUCTION;
	}
	else if(opcode >= 8 && opcode <= 15){
		return I_INSTRUCTION;
	}
	else{
		return L_INSTRUCTION;
	}
}

void disassemble(
	unsigned char instructions[BUFFER_SIZE],
	unsigned char out[BUFFER_SIZE],
	unsigned int size_in,
	unsigned int size_out
	){

// #pragma HLS INTERFACE m_axi port=instructions  offset=slave bundle=gmem
// #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem
// #pragma HLS INTERFACE s_axilite port=in1  bundle=control
// #pragma HLS INTERFACE s_axilite port=in2  bundle=control
// #pragma HLS INTERFACE s_axilite port=out bundle=control
// #pragma HLS INTERFACE s_axilite port=size bundle=control
// #pragma HLS INTERFACE s_axilite port=return bundle=control

	// Buffer to write fpga_string to
	unsigned char inputBuffer[BUFFER_SIZE];
	unsigned char outputBuffer[BUFFER_SIZE];
	unsigned int bufferPosition = 0;

	// Variables for instruction meta data
	unsigned int instruction, opcode, rs, rt, rd, shift, funct, imm;

	// String declerations	
	fpga_string opcodeString, rsString, rtString, rdString, shiftString, functString, immString, instructionString;

	fpga_string tab, space, newline, lparen, rparen, comma;

	fpga_str_init(&tab, "\t");
	fpga_str_init(&comma, ",");
	fpga_str_init(&newline, "\n");
	fpga_str_init(&lparen, "(");
	fpga_str_init(&rparen, ")");

	disassembler : for(int i = 0; i < size_in; i += 4){
#pragma HLS pipeline

		instruction = 	(instructions[i] << 24) | 
						(instructions[i + 1] << 16)|
						(instructions[i + 2] << 8) |
						(instructions[i + 3]);

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
		getRegister(rs, &rsString);
		getRegister(rt, &rtString);
		getRegister(rd, &rdString);
		getImmediate(imm, &immString);

		// FIGURE OUT STRING FORMAT FOR INSTRUCTION
		switch(getInstructionType(opcode)){
			case R_INSTRUCTION:
				fpga_str_append(&instructionString, &opcodeString);
				fpga_str_append(&instructionString, &tab);
				fpga_str_append(&instructionString, &rsString);
				fpga_str_append(&instructionString, &comma);
				fpga_str_append(&instructionString, &rtString);
				fpga_str_append(&instructionString, &comma);
				fpga_str_append(&instructionString, &rdString);
				fpga_str_append(&instructionString, &newline);
				break;
			case J_INSTRUCTION:
				fpga_str_append(&instructionString, &opcodeString);
				fpga_str_append(&instructionString, &tab);
				fpga_str_append(&instructionString, &immString);
				fpga_str_append(&instructionString, &newline);
				break;
			case L_INSTRUCTION:
				
				fpga_str_append(&instructionString, &opcodeString);
				fpga_str_append(&instructionString, &tab);
				fpga_str_append(&instructionString, &immString);
				fpga_str_append(&instructionString, &lparen);
				fpga_str_append(&instructionString, &rsString);
				fpga_str_append(&instructionString, &rparen);
				fpga_str_append(&instructionString, &newline);
				break;
			default:
				fpga_str_append(&instructionString, &opcodeString);
				fpga_str_append(&instructionString, &tab);
				fpga_str_append(&instructionString, &rsString);
				fpga_str_append(&instructionString, &comma);
				fpga_str_append(&instructionString, &rtString);
				fpga_str_append(&instructionString, &comma);
				fpga_str_append(&instructionString, &immString);
				fpga_str_append(&instructionString, &newline);
		}

		bufferPosition += instructionString.size;

		// WRITE STRING TO BUFFER
		// USE PRAMA TO OPTIMIZE PIPELINE
		int j;
		for(j = 0; j < (instructionString.size); j++){
			#pragma HLS PIPELINE
			outputBuffer[j] = instructionString.value[j];
		}
		
		for(j = 0; j < (instructionString.size); j++){
			out[bufferPosition + j] = outputBuffer[j];
		}
	}
}
