all: src/defs.h src/mips.c
	gcc src/mips.c -o disassembler

test: disassembler
	./disassembler mips_binaries/test