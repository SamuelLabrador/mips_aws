#include "mips.c"

#include <vector>
#define DATA_SIZE 16384

int main(int argc, char** argv){
	if (argc < 2){
		printf("Please provide path to the file name.\n");
		return 0;
	}

	size_t vector_size_bytes = sizeof(char) * DATA_SIZE;
	// 0001 0001 0000 0000 0000 0000 0000 0101
	// disassemble(0xAAAAAAAA);
	disassemble(0x03E0F83F);
	// printf("%s\n", argv[1]);
	return 0;

}