/*

MIT License

Copyright (c) 2022-2023 Arduino SA

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "Arduino.h"

#if 0

// TODO: check if gdb is able to unwind the call stack even without this

/* 
test code:

int illegal_instruction_execution(void) {
  int (*bad_instruction)(void) = (int (*)())0xE0000000;
  return bad_instruction();
}
*/
#endif

void Stacktrace_Handler(void) {
    asm("MOV     r0, lr");                  /* get lr */
    asm("MOV     r1, sp");                  /* get stack pointer (current is MSP) */
    asm("BL      cm_backtrace_fault");
    while(1);
}