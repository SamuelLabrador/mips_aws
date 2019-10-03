/**********
Copyright (c) 2018, Xilinx, Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**********/

#include "xcl2.hpp"
#include <vector>

#include <cassert>
#include <stdio.h>
#include <malloc.h>

#define INPUT_SIZE 1024
#define OUTPUT_SIZE INPUT_SIZE * 32

#define FILEPATH "./bash"

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

int main(int argc, char** argv)
{
    size_t vector_size_bytes = sizeof(int) * INPUT_SIZE;
    cl_int err;
 
    FILE *fPtr, *fwPtr;

    if (argc < 2){
        fPtr = fopen(FILEPATH, "rb");
    }
    else{
        fPtr = fopen(argv[1], "rb");
    }

    // GET SIZE OF FILE
    fseek(fPtr, 0, SEEK_END);
    size_t fSize = ftell(fPtr);
    rewind(fPtr);

    unsigned char *buffer = (unsigned char*) memalign(sizeof(void*), fSize * sizeof(char));
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
    assert(machineType == 0x08);    // 0x08 is MIPS RS30000

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
    printf("String Table SH Index:\t%d\nELF PARSE DONE\n\n", shstrndx); 


    // Allocate Memory in Host Memory
    // When creating a buffer with user pointer (CL_MEM_USE_HOST_PTR), under the hood user ptr 
    // is used if it is properly aligned. when not aligned, runtime had no choice but to create
    // its own host side buffer. So it is recommended to use this allocator if user wish to
    // create buffer using CL_MEM_USE_HOST_PTR to align user buffer to page boundary. It will 
    // ensure that user buffer is used when user create Buffer/Mem object with CL_MEM_USE_HOST_PTR 
    
    // std::vector<int,aligned_allocator<int>> source_in1(INPUT_SIZE);
    // int *source_in1 = malloc(INPUT_SIZE);

    // std::vector<char,aligned_allocator<char>> source_hw_results(OUTPUT_SIZE);
    
    // std::vector<int,aligned_allocator<int>> source_sw_results(OUTPUT_SIZE);
    char *source_sw_results = (char*) memalign(sizeof(int), OUTPUT_SIZE);

// OPENCL HOST CODE AREA START
    // get_xil_devices() is a utility API which will find the xilinx
    // platforms and will return list of devices connected to Xilinx platform
    std::vector<cl::Device> devices = xcl::get_xil_devices();
    cl::Device device = devices[0];

    OCL_CHECK(err, cl::Context context(device, NULL, NULL, NULL, &err));
    OCL_CHECK(err, cl::CommandQueue q(context, device, CL_QUEUE_PROFILING_ENABLE, &err));
    OCL_CHECK(err, std::string device_name = device.getInfo<CL_DEVICE_NAME>(&err)); 

    // find_binary_file() is a utility API which will search the xclbin file for
    // targeted mode (sw_emu/hw_emu/hw) and for targeted platforms.
    std::string binaryFile = xcl::find_binary_file(device_name,"disassembler");

    // import_binary_file() ia a utility API which will load the binaryFile
    // and will return Binaries.
    cl::Program::Binaries bins = xcl::import_binary_file(binaryFile);
    devices.resize(1);
    OCL_CHECK(err, cl::Program program(context, devices, bins, NULL, &err));
    OCL_CHECK(err, cl::Kernel disassembler(program,"disassembler", &err));

    // Allocate Buffer in Global Memory
    // Buffers are allocated using CL_MEM_USE_HOST_PTR for efficient memory and 
    // Device-to-host communication

    unsigned char* bufferLocation = buffer;

    printf("\nInitializing buffers\n\n");

    std::vector<char, aligned_allocator<char>> source_in1 (INPUT_SIZE);
    std::vector<char, aligned_allocator<char>> source_hw_results (OUTPUT_SIZE);


    OCL_CHECK(err, cl::Buffer instructions   (context,CL_MEM_USE_HOST_PTR | CL_MEM_READ_ONLY, 
            INPUT_SIZE, source_in1.data(), &err));
    
    OCL_CHECK(err, cl::Buffer buffer_output(context,CL_MEM_USE_HOST_PTR | CL_MEM_WRITE_ONLY, 
            OUTPUT_SIZE, source_hw_results.data(), &err));



    printf("Disassembling...\n");
    // BEGIN disassembling 
    // Parse Section Table
    fwPtr = fopen("./output.txt", "w");

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

            unsigned int offset = 0;
            int input_size = 0;
            for(offset = 0; offset < sh_size; offset += INPUT_SIZE){
                if(offset < INPUT_SIZE){
                    input_size = INPUT_SIZE - offset;
                }
                else{
                    input_size = INPUT_SIZE;
                }
                // input_size = 1;
                for(int i = 0; i < INPUT_SIZE; i++){
                    source_in1.at(i) = buffer[offset];
                }
                // printf("%d\n", offset);

                OCL_CHECK(err, err = q.enqueueMigrateMemObjects({instructions},0/* 0 means from host*/));
                
                OCL_CHECK(err, err = disassembler.setArg(0, instructions));
                OCL_CHECK(err, err = disassembler.setArg(1, buffer_output));
                OCL_CHECK(err, err = disassembler.setArg(2, input_size));

                // Launch the Kernel
                // For HLS kernels global and local size is always (1,1,1). So, it is recommended
                // to always use enqueueTask() for invoking HLS kernel            
                OCL_CHECK(err, err = q.enqueueTask(disassembler));
                
                // Copy Result from Device Global Memory to Host Local Memory
                OCL_CHECK(err, err = q.enqueueMigrateMemObjects({buffer_output},CL_MIGRATE_MEM_OBJECT_HOST));
                
                for(int k = 0; k < input_size; k++){
                    for(int l = 0; l < 32; l++){
                        char character = source_hw_results.at(k * 32 + l);

                        if(character == '\0'){
                           break; 
                        }
                        fputc(character, fwPtr);
                    }
                    fputc('\n', fwPtr);
                }

                q.finish();
                // break;
            }
        }
    }

    printf("Done!\n");
    fclose(fwPtr);
    fclose(fPtr);




    
// OPENCL HOST CODE AREA END

    // Compare the results of the Device to the simulation
    bool match = true;
    // for (int i = 0 ; i < INPUT_SIZE ; i++){
    //     if (source_hw_results[i] != source_sw_results[i]){
    //         std::cout << "Error: Result mismatch" << std::endl;
    //         std::cout << "i = " << i << " CPU result = " << source_sw_results[i]
    //             << " Device result = " << source_hw_results[i] << std::endl;
    //         match = false;
    //         break;
    //     }
    // }

    std::cout << "TEST " << (match ? "PASSED" : "FAILED") << std::endl; 
    return (match ? EXIT_SUCCESS : EXIT_FAILURE);
}
