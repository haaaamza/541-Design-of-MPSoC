//
//  memorySystem.h
//  541ass1
//
//  Created by Hamza Mian on 2020-10-10.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//
#include "define.h"
#include "simple_mem_if.hpp"
#include "mem_RTL.hpp"
#include "oscillator.hpp"

#ifndef memorySystem_h
#define memorySystem_h

class memorySystem: public simple_mem_if, public sc_module{
    
public:
    virtual bool Write(unsigned int addr, unsigned int data);
    virtual bool Read(unsigned int addr, unsigned int& data);
    
    MEMORY_RTL* memrtl_0;
    oscillator* osc_0;

    sc_signal <sc_logic> clk_sig; //we can use sc_clock, but we have oscillator
    sc_signal <sc_logic> ren_sig, wen_sig;
    sc_signal <int> addr_sig;
    sc_signal <int> dataIn_sig;
    sc_signal <int> dataOut_sig;
    sc_signal <sc_logic> ack_sig;
    
    memorySystem(sc_module_name name, char* filename) :sc_module(name) { //reused from Part 2!
        memrtl_0 = new MEMORY_RTL("memrtl_0", filename);
        osc_0 = new oscillator("osc_0");

        memrtl_0->Clk(clk_sig);
        memrtl_0->Ren(ren_sig);
        memrtl_0->Wen(wen_sig);
        memrtl_0->Ack(ack_sig);
        memrtl_0->Addr(addr_sig);
        memrtl_0->DataIn(dataIn_sig);
        memrtl_0->DataOut(dataOut_sig);
        //
        ren_sig.write(sc_logic_0);
        wen_sig.write(sc_logic_0);
        ack_sig.write(sc_logic_X); //X signifies unknown, IEEE 1666-2011
        //
        osc_0->out_clk(clk_sig);
        
    }
    ~memorySystem() {
        delete memrtl_0;
        delete osc_0;
    }
};

#endif /* memorySystem_h */
