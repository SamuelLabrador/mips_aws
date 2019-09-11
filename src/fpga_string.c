#include "fpga_string.h"

void fpga_copy(fpga_string *target, fpga_string *source){
	
	unsigned int i;

	// "FRAME DATA" COPY
	// STRING SIZE IS DEFINED IN fpga_string.h

	// EVERY ELEMENT IS COPIED TO MAXIMIZE THE 
	// BENEFIT FROM THE "#pragma HLS unroll"
	for(i = 0; i < STRING_SIZE; i++){
		// #pragma HLS unroll factor=STRING_SIZE
		target->value[i] = source->value[i];
	}
}