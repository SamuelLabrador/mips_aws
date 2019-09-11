/*
	Samuel Labrador
	slabr003@ucr.edu
*/

#ifndef __fpga_string_h__
#define __fpga_string_h__

#define STRING_SIZE 32

typedef struct{
	char value[STRING_SIZE];		// ARRAY SIZE NEEDS TO BE PREDIFNED FOR HLS
	unsigned int size;	
} fpga_string;

void fpga_str_init(fpga_string *target, char *value);

unsigned int fpga_str_char_cpy(fpga_string *target, char *source);

// Copies the source string to the target string 
// starting at index 0. It returns the size of the new string.
unsigned int fpga_str_cpy(fpga_string *target, char *source);

// Copies the source string to the target string starting at the 
// index specified. It returns the size of the new string.
unsigned int fpga_str_insert(fpga_string *target, fpga_string *source, unsigned int index);

// Concatenates the lhs string and rhs string. The concatenated result 
// is stored in the target fpga_string. It returns the size of the new string.
unsigned int fpga_str_append(fpga_string *target, fpga_string *rhs);

// Coverts the source integer to a string. Returns size of new string.
unsigned int fpga_str_int(fpga_string * target, int source);

#endif