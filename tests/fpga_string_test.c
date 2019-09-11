#include <stdio.h>
#include "fpga_string.h"

int main(){
	// Decleration
	fpga_string reg1, reg2, opcode, imm, instruction, space;
	
	unsigned int size;
	
	// Initialization
	fpga_str_init(&space, " ");
	fpga_str_init(&reg1, "reg1");
	fpga_str_init(&reg2, "reg2");
	fpga_str_init(&opcode, "opcode");
	fpga_str_init(&imm, "123456");
	fpga_str_init(&instruction, "");

	// TEST
	printf("instruction: %s -- %d\n", instruction.value, size);

	size = fpga_str_append(&instruction, &opcode);
	
	printf("instruction: %s -- %d\n", instruction.value, size);

	size = fpga_str_append(&instruction, &space);
	size = fpga_str_append(&instruction, &reg1);
	
	printf("instruction: %s -- %d\n", instruction.value, size);

	size = fpga_str_append(&instruction, &space);
	size = fpga_str_int(&instruction, 125);	

	printf("instruction: %s -- %d\n", instruction.value, size);


	return 0;
}