//
//  define.h
//  541ass1
//
//  Created by Hamza Mian on 2020-10-07.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//
#include "systemc.h"
#include <systemc>
#include <iostream>
#include <fstream>


/*___________________________SADcomp_______________________________________________________________________*/
//is this 2^x or real numbers=x??
#define NUM_BLOCKS 64
#define BLOCK_SIZE 64 //should ideally equal DATA_WIDTH
#define INPUT1_ADDR 0
#define INPUT2_ADDR 16384
#define SAD_OUTPUT_ADDR 32768
#define CKCYCLE 10

/*___________________________memRead________________________________________________________________________*/

#define MEM_SIZE        BLOCK_SIZE * NUM_BLOCKS * 500

#ifndef define_h
#define define_h


#endif /* define_h */
