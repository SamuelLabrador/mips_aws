#define STRING_SIZE 32

typedef struct{
	char value[32];		// ARRAY SIZE NEEDS TO BE PREDIFNED FOR HLS
	unsigned int size;	
} fpga_string;

void fpga_copy(fpga_string *target, fpga_string *source);

