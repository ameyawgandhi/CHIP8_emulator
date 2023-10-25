#include "chip8class.h"
using namespace std;


void Chip8::initialize(){
    program_counter = 0x200;
    delay_timer = 0;
    sound_timer = 0;
    opcode = 0;
    stack_pointer = 0;
    index_register = 0;
    for (int i = 0; i < 64*32; ++i){
        gfx[i] = 0;
    }
    for (int i = 0; i < 16; ++i){
        mem_register[i] = 0;
        stack_routines[i] = 0;
        keypad[i] = 0;
    }
}

void Chip8::fetch_opcode(){
    opcode = memory[program_counter] << 8 || memory[program_counter + 1];
}

void Chip8::emulate_codes(){
    switch(opcode & 0xF000){
        case 0x1000:
            program_counter = opcode & 0x0FFF;
            break;
        case 0x2000:
            stack_routines[stack_pointer] = program_counter;
            stack_pointer++;
            program_counter = opcode & 0x0FFF;
            break;
            
        case 0x3000:
            if (mem_register[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)){
                program_counter += 2;
            }
            program_counter += 2;
            break;
        case 0x4000:
            if (mem_register[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)){
                program_counter += 2;
            }
            program_counter += 2;
            break;
        case 0x5000:
            if (mem_register[(opcode & 0x0F00) >> 8] != mem_register[(opcode & 0x00F0) >> 4]){
                program_counter += 2;
            }
            program_counter += 2;
            break;
        case 0x6000:
            mem_register[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);
            program_counter += 2;
            break;
        case 0x7000:
            mem_register[(opcode & 0x0F00) >> 8] =  mem_register[(opcode & 0x0F00) >> 8] + opcode & 0x00FF;
            program_counter += 2;
            break;
        case 0x8000:
            switch(opcode & 0x000F){
                case 0x0000:
                    mem_register[(opcode & 0x0F00) >> 8] = mem_register[(opcode & 0x00F0) >> 4];
                    program_counter += 2;
                    break;
                case 0x0001:
                    mem_register[(opcode & 0x0F00) >> 8] = mem_register[(opcode & 0x0F00) >> 8] | mem_register[(opcode & 0x00F0)>>4];
                    program_counter += 2;
                    break;
                case 0x0002:
                    mem_register[(opcode & 0x0F00)>>8] = mem_register[(opcode & 0x0F00)>>8] & mem_register[(opcode & 0x00F0)>>4];
                    program_counter += 2;
                    break;
                case 0x0003:
                    mem_register[(opcode & 0x0F00)>>8] = mem_register[(opcode & 0x0F00)>>8] ^ mem_register[(opcode & 0x00F0)>>4];
                    program_counter += 2;
                    break;
                case 0x0004:
                    mem_register[(opcode & 0x0F00) >> 8] = mem_register[(opcode & 0x0F00)] + mem_register[(opcode & 0x00F0)>>4];
                    if (mem_register[(opcode & 0x00F0)>>4] > (0xFF - mem_register[(opcode & 0x0F00) >> 8])){
                        mem_register[0xF] = 1;
                    }
                    else{
                        mem_register[0xF] = 0;
                    }
                    program_counter += 2;
                    break;
                case 0x0005:
                    mem_register[(opcode & 0x0F00) >> 8] = mem_register[(opcode & 0x0F00)] - mem_register[(opcode & 0x00F0)>>4];
                    if (mem_register[(opcode & 0x0F00) >> 8]> mem_register[(opcode & 0x00F0)>>4]){
                        mem_register[0xF] = 1;
                    }
                    else{
                        mem_register[0xF] = 0;
                    }
                    program_counter += 2;
                    break;
                case 0x0006:
                    if ((mem_register[(opcode & 0x0F00) >> 8] & 0x000F) == 1){
                        mem_register[0xF] = 1;
                    }
                    else{
                        mem_register[0xF] = 0;
                    }
                    mem_register[(opcode & 0x0F00) >> 8] >>= 1;
                    program_counter += 2;
                    break;
                case 0x0007:
                    mem_register[(opcode & 0x0F00) >> 8] = mem_register[(opcode & 0x00F0)>>4]-mem_register[(opcode & 0x0F00)];
                    if (mem_register[(opcode & 0x00F0)>>4] > mem_register[(opcode & 0x0F00) >> 8] ){
                        mem_register[0xF] = 1;
                    }
                    else{
                        mem_register[0xF] = 0;
                    }
                    program_counter += 2;
                    break;
                case 0x000E:
                    if ((mem_register[(opcode & 0x0F00) >> 8] & 0xF000) == 1){
                        mem_register[0xF] = 1;
                    }
                    else{
                        mem_register[0xF] = 0;
                    }
                    mem_register[(opcode & 0x0F00) >> 8] <<= 1;
                    program_counter += 2;
                    break;
            }
            case 0x9000:
                if (mem_register[(opcode & 0x0F00) >> 8] !=  mem_register[(opcode & 0x00F0) >> 4]){
                    program_counter += 2;
                }
                program_counter+=2;
                break;
            case 0xA000:
                index_register = (opcode & 0x0FFF);
                
    }
};
