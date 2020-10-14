//
//  SADcomp.h
//  541ass1
//
//  Created by Hamza Mian on 2020-10-06.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//

//________________________________INCLUDES AND DEFINES_____________________________________________________

#include "define.h"
#include "simple_mem_if.hpp"

#ifndef SADcomp_h
#define SADcomp_h


//________________________________MODULE_____________________________________________________

SC_MODULE(saad){

    int i,v;
    unsigned int block, sad;
    sc_time start_time, end_time;

    sc_port<simple_mem_if> MEMORY;

    void func();
     
    SC_CTOR (saad) {
        SC_THREAD(func); //done on init
    }
};

#endif
