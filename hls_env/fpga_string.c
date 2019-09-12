#include "fpga_string.h"

void fpga_str_init(fpga_string *target, char *value){
	int i = 0;
	while(value[i] != '\0'){
		target->value[i] = value[i];
		i++;
	}
	target->value[i] = '\0';
	target->size = i;
}

unsigned int fpga_strcpy(fpga_string *target, fpga_string *source){
	int i;
	// COPY THE NULL BYTE
	for(i = 0; i <= source->size; i++){
// #pragma HLS unroll
		target->value[i] = source->value[i];
	}
	target->size = source->size;
	return i;
}

unsigned int fpga_str_char_cpy(fpga_string *target, char *source){
	unsigned int i = 0;

	while(source[i] != '\0'){
#pragma HLS pipeline
		target->value[i] = source[i];

		i++;
	}
	target->value[i] = '\0';
	return i;

}


unsigned int fpga_str_insert(fpga_string * target, fpga_string *source, unsigned int index){
	int i = index;
	int j = 0;
	// COPY THE NULL BYTE
	for(j = 0; j <= source->size; j++){
#pragma HLS pipeline
		target->value[i] = source->value[j];
		i++;
	}
	target->size = i-1;
	return i - 1;
}

unsigned int fpga_str_append(fpga_string* target, fpga_string *rhs){
	return fpga_str_insert(target, rhs, target->size);
}

// Appends integer in string representation to the end of the string
unsigned int fpga_str_int(fpga_string *target, int source){
	
	int i = target->size;

	int mod = 1;
	while(source > (mod * 10)){	// Get upper bound of mod.
#pragma HLS pipeline
		mod *= 10;
	}

	while(mod != 0){
#pragma HLS pipeline
		target->value[i] = '0' + (source / mod);
		
		source = source % mod;
		mod /= 10;
		i++;
	}

	target->value[i] = '\0';

	return i;
}
