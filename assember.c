/***************************************************************************
 * file name   : assembler.c                                               *
 * author      : tjf & you                                                 *
 * description : This program will assemble a .ASM file into a .OBJ file   *
 *               This program will use the "asm_parser" library to achieve *
 *			     its functionality.										   *
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"

int main(int argc, char** argv) {

    char* filename = NULL ;					// name of ASM file
    char  program [ROWS][COLS] ; 			// ASM file line-by-line
    char  program_bin_str [ROWS][17] ; 		// instructions converted to a binary string
    unsigned short int program_bin [ROWS] ; // instructions in binary (HEX)


    filename = "test1.asm";
    read_asm_file(filename, program);//call read_asm_file function

    // problem2 parse_instruction
    int i = 0;
    while(program[i][0] != '\0'){
        printf("assemble instruction is = %s\n", program[i]);
        parse_instruction (program[i], program_bin_str[i]);
        printf("binary instruction is   = %s\n", program_bin_str[i]);
        //problem3 cover to unsigned short int
        program_bin[i] = str_to_bin(program_bin_str[i]);
        printf("hex instruction is      = 0x%X\n",program_bin[i]);
        i++;
    }

    program_bin[i] = 0;
//    printf("what?\n");

    //problem5
    char objname[100];
    strcpy(objname, filename);
    int length = strlen(objname);
    strcpy(&objname[length-3],"obj");

    printf("%s\n",objname);

    write_obj_file(objname,program_bin);

    return (0) ;
}
