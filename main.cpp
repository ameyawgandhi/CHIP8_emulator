#include "chip8class.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(){
    Chip8 chipEmulator;
    chipEmulator.opcode = 0x3A11;
    chipEmulator.mem_register[0x0A] = 0x12;
    chipEmulator.emulate_codes();

    return 0;
}