
c: obj/host.o obj/disassembler.o
	g++ -o bin/disassembler obj/*

# Host obj file generation
h: include/defs.h src/host.cpp
	g++ -Iinclude -c -o obj/host.o src/host.cpp -w

s: include/fpga_string.h src/fpga_string.c
	gcc -Iinclude -c -o obj/fpga_string.o src/fpga_string.c 

# Disassembler obj file generation
d: src/disassembler.c ./include/defs.h ./include/disassembler.h
	g++ -Iinclude -c -o obj/disassembler.o src/disassembler.c -w

test_string: 
	gcc -Iinclude -o bin/test_string tests/fpga_string_test.c obj/fpga_string.o
	./bin/test_string

test: bin/disassembler mips_binaries/bash
	./bin/disassembler mips_binaries/bash 	

clean:
	rm obj/*
	rm bin/*	