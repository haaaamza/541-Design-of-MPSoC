//
//  define.h
//  ass2
//
//  Created by Hamza Mian on 2020-10-21.
//


#include "systemc.h"
#include <systemc>
#include "stdio.h"
#include "simple_bus.h"
#include <iostream>
#include <queue>

#define LOOPS 1000
#define SIZE 6

//MEM INTERNALS
#define ABC_LEN SIZE*SIZE
#define MEM_LEN 3*ABC_LEN
//MEM ADDRESS ACCESS
#define BASE_ADDR 0
#define A_ADDR BASE_ADDR
#define B_ADDR A_ADDR + ABC_LEN
#define C_ADDR B_ADDR + ABC_LEN

//REGISTERS
#define INFO_REG 6 //We have 6 info registers (from 0-5)
#define IREG_B_ADDR 0
#define IREG_E_ADDR INFO_REG
#define REG_LEN SIZE*SIZE  //TOTAL SIZE = 6^2 = 36
#define MLA_LEN SIZE*SIZE

//HW ADDRESS ACCESS
#define IREG_ADDR MEM_LEN
#define REG_ADDR IREG_ADDR + INFO_REG
#define MLA_ADDR REG_ADDR + REG_LEN
#define REG_END_ADDR MLA_ADDR + MLA_LEN
//MST ID'S
#define SW_MST 1
#define HW_MST 2
#define MEM_MST 3

//MEMORY OP
#define MEM_PRINT 0 
#define MEM_READ 1
#define MEM_WRITE 2
#define MEM_RESET 21
//#define MEM_OP MEM_READ && MEM_WRITE

//HW OP
#define HW_MUL 3
#define HW_RST 4
#define HW_RG_WRITE 5
#define HW_RG_READ 6
#define BUS_CHECK 10

//HW NON-READ or WRITE OPERATION LOGISTICS
#define NON_OPERATION_LEN 15
#define NON_OPERATION 15
#define NON_OPERATION_ADDR 0

//MEM Metrics
#define MEM_START_ADDR 0
#define MEM_END_ADDR MEM_LEN
#define MEM_SIZE 500 + MEM_LEN + INFO_REG

#ifndef define_h
#define define_h
//bool mem_done = false;

#endif /* define_h */
