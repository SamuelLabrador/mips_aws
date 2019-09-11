
c: obj/host.o obj/disassembler.o
	g++ -o bin/disassembler obj/*

# Host obj file generation
h: include/defs.h src/host.cpp
	g++ -Iinclude -c -o obj/host.o src/host.cpp -w

# Disassembler obj file generation
d: src/disassembler.c ./include/defs.h ./include/disassembler.h
	g++ -Iinclude -c -o obj/disassembler.o src/disassembler.c -w

test: bin/disassembler mips_binaries/bash
	./bin/disassembler mips_binaries/bash	

clean:
	rm obj/*
	rm bin/*	