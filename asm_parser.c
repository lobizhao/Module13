/***************************************************************************
 * file name   : asm_parser.c                                              *
 * author      : tjf & you                                                 *
 * description : the functions are declared in asm_parser.h                *
 *               The intention of this library is to parse a .ASM file     *
 *			        										               *
 *                                                                         *
 ***************************************************************************
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_parser.h"



/* to do - implement all the functions in asm_parser.h */
//program1
int read_asm_file (char* filename, char program [ROWS][COLS] ){

    FILE *asm_file;
    asm_file = fopen(filename ,"r");     //open file

    //if no file
    if (asm_file == NULL){
        printf("error2: read_asm_file() failed \n");
        return 2;
    }

    int i=0;
    //new a 2darray
    while(fgets(program[i], COLS, asm_file)){
        int newline = strlen(program[i]) -1 ;

        //remove "newline" characters at the end of the lines
        if(program[i][newline] == '\n'){
            program[i][newline] = '\0';

        }

        //cradit 1 ignore comment(behand the ";") in the asm file
        char *comment = strchr(program[i],';');
        if(comment != NULL){
            *comment = '\0';
        }

        //print 2D array test
        //puts(program[i]);
        i++;
    }
    //end
    program[i][0] = '\0';
    return 0;
}


//program3 cover register address r1-r7
int parse_reg(char reg_num, char *instr_bin_str) {
    switch (reg_num) {
        case '0':
            strcat(instr_bin_str, "000");
            break;
        case '1':
            strcat(instr_bin_str, "001");
            break;
        case '2':
            strcat(instr_bin_str, "010");
            break;
        case '3':
            strcat(instr_bin_str, "011");
            break;
        case '4':
            strcat(instr_bin_str, "100");
            break;
        case '5':
            strcat(instr_bin_str, "101");
            break;
        case '6':
            strcat(instr_bin_str, "110");
            break;
        case '7':
            strcat(instr_bin_str, "111");
            break;
        default:
            //if not return 5
            printf("error5: parse_reg() failed");
            return 5;
    }
    return 0;
}

//check register token
int continue_parsing_reg(char *instr_bin_str) {

    char *token = strtok(NULL, " ,");
    parse_reg(token[1], instr_bin_str);
    return 0;
}

//if add instruction write opcode and sub-opcode in string
int parse_add(char *instr, char *instr_bin_str) {
    strcpy(instr_bin_str, "0001");
    continue_parsing_reg(instr_bin_str);
    continue_parsing_reg(instr_bin_str);
    strcat(instr_bin_str, "000");
    continue_parsing_reg(instr_bin_str);
    return 0;
}

//if mul instruction write opcode and sub-opcode in string
int parse_mul(char *instr, char *instr_bin_str) {
    strcpy(instr_bin_str, "0001");
    continue_parsing_reg(instr_bin_str);
    continue_parsing_reg(instr_bin_str);
    strcat(instr_bin_str, "001");
    continue_parsing_reg(instr_bin_str);
    return 0;
}

//if sub instruction write opcode and sub-opcode in string
int parse_sub(char *instr, char *instr_bin_str) {
    strcpy(instr_bin_str, "0001");
    continue_parsing_reg(instr_bin_str);
    continue_parsing_reg(instr_bin_str);
    strcat(instr_bin_str, "010");
    continue_parsing_reg(instr_bin_str);

    return 0;
}

//if div instruction write opcode and sub-opcode in string
int parse_div(char *instr, char *instr_bin_str) {
    strcpy(instr_bin_str, "0001");
    continue_parsing_reg(instr_bin_str);
    continue_parsing_reg(instr_bin_str);
    strcat(instr_bin_str, "011");
    continue_parsing_reg(instr_bin_str);
    return 0;
}

//if and instruction write opcode and sub-opcode in string
int parse_and(char *instr, char *instr_bin_str) {
    strcpy(instr_bin_str, "0101");
    continue_parsing_reg(instr_bin_str);
    continue_parsing_reg(instr_bin_str);
    strcat(instr_bin_str, "000");
    continue_parsing_reg(instr_bin_str);
    return 0;
}

//if or instruction write opcode and sub-opcode in string
int parse_or(char *instr, char *instr_bin_str) {
    strcpy(instr_bin_str, "0101");
    continue_parsing_reg(instr_bin_str);
    continue_parsing_reg(instr_bin_str);
    strcat(instr_bin_str, "010");
    continue_parsing_reg(instr_bin_str);
    return 0;
}

//if xor instruction write opcode and sub-opcode in string
int parse_xor(char *instr, char *instr_bin_str) {
    strcpy(instr_bin_str, "0101");
    continue_parsing_reg(instr_bin_str);
    continue_parsing_reg(instr_bin_str);
    strcat(instr_bin_str, "011");
    continue_parsing_reg(instr_bin_str);
    return 0;
}

// problem2 parse_instruction
int parse_instruction(char *instr, char *instr_bin_str) {
    // check instruction
    char *token = strtok(instr, " ,");

    // cover to binary opcode
    if (strcmp(token, "ADD") == 0) {
        parse_add(instr, instr_bin_str);
    } else if (strcmp(token, "MUL") == 0) {
        parse_mul(instr, instr_bin_str);
    } else if (strcmp(token, "SUB") == 0) {
        parse_sub(instr, instr_bin_str);
    } else if (strcmp(token, "DIV") == 0) {
        parse_div(instr, instr_bin_str);
    } else if (strcmp(token, "AND") == 0) {
        parse_and(instr, instr_bin_str);
    } else if (strcmp(token, "OR") == 0) {
        parse_or(instr, instr_bin_str);
    } else if (strcmp(token, "XOR") == 0) {
        parse_xor(instr, instr_bin_str);
    } else {
        //if not the return 3
        printf(" error3: parse_instruction() failed.");
        return 3;
    }
    return 0;
}

//problem4 change element type
unsigned short int str_to_bin (char* instr_bin_str) {
    unsigned short int ret;
    //find binary elements
    ret = strtol(instr_bin_str, NULL, 2);
    return ret;
}

//swap endianness
unsigned short endianness(unsigned  short value){
    return (value<<8) |(value >>8);
}

//program5
int write_obj_file (char* filename, unsigned short int program_bin[ROWS] ) {
    //set head
    unsigned short head = endianness(0xCADE);
    //address
    unsigned short address = endianness(0x0000);
    //calculate <n>
    unsigned short n = 0;
    while (program_bin[n]){
        n++;
    }

    for (int i = 0; i<n ; i++){
        program_bin[i]= endianness(program_bin[i]);
    }
    //keep n counter, new m
    unsigned short m = endianness(n);
    //n = endianness(n);

    //open .obj file
    FILE *theFile = fopen(filename, "wb");
    //if not return 7
    if(filename == NULL){ return 7;}

    //write 3 head letter
    fwrite(&head, 2, 1,theFile);
    fwrite(&address, 2, 1,theFile);
    fwrite(&m, 2, 1,theFile);
    //write instruction code

    fwrite(program_bin, sizeof(unsigned short int), n,theFile);

    //done close file
    fclose(theFile);
    return 0;
}