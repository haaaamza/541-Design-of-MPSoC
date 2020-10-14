//
//  mem_RTL.hpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-10.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//
#include "define.h"
#ifndef mem_RTL_hpp
#define mem_RTL_hpp

class MEMORY_RTL: public sc_module{
public:
    sc_in <sc_logic> Clk;
    sc_in <sc_logic> Ren, Wen;
    sc_in <int> Addr;
    sc_in <int> DataIn;
    sc_out <int> DataOut;
    sc_out <sc_logic> Ack;
    unsigned int mem[MEM_SIZE] = {0};
    
    SC_HAS_PROCESS(MEMORY_RTL);
    
    MEMORY_RTL(sc_module_name name, char* memInitFilename) :sc_module(name){
        std::ifstream outfp(memInitFilename); //ifstream tutorial from Fredosaurus, tutorialspoint.
        if (!outfp){
            cout << "Couldn't open file!\n";
            exit(1);
        }
        
        unsigned int data, i = 0;
        while(outfp >> data){
            if (i < MEM_SIZE){
                mem[i] = data;
                i++;
                
            }else {
                break;
            }
        }
        outfp.close(); //release resources
        SC_METHOD(rtl);
        sensitive << Clk.pos();
    }
    
    void rtl();
};

#endif /* mem_RTL_hpp */
