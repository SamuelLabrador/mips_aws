#ifndef __DISASSEMBLER_H__
#define __DISASSEMBLER_H__

#include <string.h>
#include <stdio.h>

#include "defs.h"
#include "fpga_string.h"

#define BUFFER_SIZE 4096

void getOpcode(unsigned int, unsigned int, fpga_string *);

void getRegister(unsigned int, fpga_string *);

void getImmediate(int, fpga_string* );

instruction_type getInstructionType(unsigned int);

void disassemble(unsigned char*, unsigned int);

#endif