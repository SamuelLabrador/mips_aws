#include <vector>
#include <cassert>
#include <cstdlib>
#include <stdint.h>
#include <stdio.h>
#include "disassembler.h"

#define DATA_SIZE 16384

unsigned int getHalf(unsigned char* buffer, unsigned int* byte){
	unsigned int half = (buffer[*byte] << 8) | buffer[*byte + 1];
	*byte += 2;
	return half;
}

char* parseName(unsigned char* buffer, unsigned int index, unsigned int offset){
	char *name = (char*)malloc(100);
	unsigned int pos = index + offset;
	unsigned int i = 0;
	while(buffer[pos] != '\0'){
		name[i++] = buffer[pos++];
	}
	name[i] = '\0';
	return name;
}

unsigned int getWord(unsigned char* buffer, unsigned int* byte){
	unsigned int word = (buffer[*byte + 0] << 24) | 
						(buffer[*byte + 1] << 16) | 
						(buffer[*byte + 2] << 8) | 
						(buffer[*byte + 3]);
	*byte += 4;
	return word;
}

int main(int argc, char** argv){
	if (argc < 2){
		printf("Please provide path to the file name.\n");
		return 0;
	}

	// Initialize Binary File Pointer
	FILE *fPtr;

	fPtr = fopen(argv[1], "rb");
	if(!fPtr){
		printf("Cannot open file. Exiting.\n");
		return -1;
	}

	// GET SIZE OF FILE
	fseek(fPtr, 0, SEEK_END);
	size_t fSize = ftell(fPtr);
	rewind(fPtr);

	unsigned char *buffer = (unsigned char*) malloc(fSize * sizeof(char));
	if(buffer == NULL){
		printf("Error loading file into memory!");
		return -1;		
	}

	// READ ENTIRE FILE INTO MEMORY BUFFER
	printf("\n-------------------------------------------------\n-- Loading %017d bytes into memory --\n-------------------------------------------------\n\n", fSize);
	
	fread(buffer, fSize, 1, fPtr);

	// START VALIDATING THE ELF HEADER
	printf("Checking Magic Number\n");
	
	unsigned int byte = 0;
	assert(buffer[byte++] == 0x7F);
	assert(buffer[byte++] == 'E');
	assert(buffer[byte++] == 'L');
	assert(buffer[byte++] == 'F');

	printf("Checking 32bit File Class Identifier\n");

	char elfClass = buffer[byte++];
	assert(elfClass == 0x01);

	printf("Checking Data Encoding\n");

	// 0 == Invalid
	// 1 == LSB
	// 2 == MSB
	char elfData = buffer[byte++];
	assert(elfData != 0x00);

	// END OF MAGIC
	byte = 16;

	printf("Checking File Type\n");
	unsigned int fileType = getHalf(buffer, &byte);

	printf("Checking Machine Type\n");
	unsigned int machineType = getHalf(buffer, &byte);
	assert(machineType == 0x08); 	// 0x08 is MIPS RS30000

	printf("Checking ELF Version\n");
	unsigned int elfVersion = getWord(buffer, &byte);
	assert(elfVersion == 0x01);

	// The entry address holds the virtual address to which 
	// the system first transfers control

	unsigned int entryAddr = getWord(buffer, &byte);
	printf("Entry Address:\t\t0x%08x\n", entryAddr);

	unsigned int phoff = getWord(buffer, &byte);
	printf("Program Header Offset:\t0x%08x\n", phoff);

	unsigned int shoff = getWord(buffer, &byte);
	printf("Section Header Offset:\t0x%08x\n", shoff);

	unsigned int flags = getWord(buffer, &byte);
	printf("Processor Flags:\t0x%x\n", flags);

	// Size of ELF Header in Bytes
	unsigned int ehsize = getHalf(buffer, &byte);
	printf("Header Size:\t\t%d bytes\n", ehsize);
	
	// Size of each program header (in bytes)
	unsigned int phentsize = getHalf(buffer, &byte);
	printf("Program Header Size:\t%d bytes\n", phentsize);

	// Number of entries in Program Table
	unsigned int phnum = getHalf(buffer, &byte);
	printf("Number of PH Entries:\t%d\n", phnum);

	// Size of Section headers (in bytes)
	unsigned int shentsize = getHalf(buffer, &byte);
	printf("Section Header Size:\t%d bytes\n", shentsize);

	// Number of entries in Section Header Table
	unsigned int shnum = getHalf(buffer, &byte);
	printf("Number of SH Entries:\t%d\n", shnum);

	// Section Header inder of String Table
	unsigned int shstrndx = getHalf(buffer, &byte);
	printf("String Table SH Index:\t%d\n", shstrndx); 

	// Parse Section Table
	byte = shoff;
	for(int i = 0; i < shnum; i++){
		unsigned int sh_name = getWord(buffer, &byte);
		unsigned int sh_type = getWord(buffer, &byte);
		unsigned int sh_flags = getWord(buffer, &byte);
		unsigned int sh_addr = getWord(buffer, &byte);
		unsigned int sh_offset = getWord(buffer, &byte);
		unsigned int sh_size = getWord(buffer, &byte);
		unsigned int sh_link = getWord(buffer, &byte);
		unsigned int sh_info = getWord(buffer, &byte);
		unsigned int sh_addralign = getWord(buffer, &byte);
		unsigned int sh_entsize = getWord(buffer, &byte);
	
		// Get executable sections
		if((sh_flags & 0x4) != 0){
			
			int j;

			unsigned char pcieBuffer[DATA_SIZE]; 
			unsigned int offset = 0;
			unsigned int size = 0;
			for(offset = 0; offset < sh_size; offset += DATA_SIZE){
				if(offset < DATA_SIZE){
					size = DATA_SIZE - offset;
				}
				else{
					size = DATA_SIZE;
				}
				// disassemble(buffer + offset, size);
			}
		}
	}

	// byte = phoff;
	// for(int i = 0; i < phnum; i++){
	// 	unsigned int p_type = getWord(buffer, &byte);
	// 	unsigned int p_offset = getWord(buffer, &byte);
	// 	unsigned int p_vaddr = getWord(buffer, &byte);
	// 	unsigned int p_paddr = getWord(buffer, &byte);
	// 	unsigned int p_filesz = getWord(buffer, &byte);
	// 	unsigned int p_memsz = getWord(buffer, &byte);
	// 	unsigned int p_flags = getWord(buffer, &byte);
	// 	unsigned int p_align = getWord(buffer, &byte);
	// }

	fclose(fPtr);
	
	return 0;
}