//
//  memRead.cpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-05.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//

//system takes care of RTL and simple memory access
#include "memorySystem.h"

bool memorySystem:: Write(unsigned int addr, unsigned int data)  {
    while (ack_sig.read().is_01()){ //if we write something wait until free
        wait(CKCYCLE, SC_NS); //1 CS, equal to 10 NS. Since rtl is sensitive to Clk.pos, it takes 1 CS/10NS for ack status to change.
    }
    
    ren_sig.write(sc_logic_0);
    wen_sig.write(sc_logic_1);
    addr_sig.write(static_cast<int> (addr));
    dataIn_sig.write(static_cast<int>(data)); //send data for RTL to write.
    
    while (!ack_sig.read().is_01()){ //wait for assertion.
        wait(CKCYCLE, SC_NS); //1 CS, Since rtl is sensitive to Clk.pos, it takes 1 CS/10NS for ack status to change.
    }
    wen_sig.write(sc_logic_0); //done op
    
    return ack_sig.read().to_bool();
    
}

bool memorySystem:: Read(unsigned int addr, unsigned int& data) {
    
    while (ack_sig.read().is_01()){ //if we write something wait until free
        wait(10, SC_NS); //1 CS, Since rtl is sensitive to Clk.pos, it takes 1 CS/10NS for ack status to change.
    }
    wen_sig.write(sc_logic_0);
    ren_sig.write(sc_logic_1);
    addr_sig.write(addr);
    
    while (!ack_sig.read().is_01()){ //wait for assertion.
        wait(10, SC_NS); //1 CS, Since rtl is sensitive to Clk.pos, it takes 1 CS/10NS for ack status to change.
    }
    data = static_cast<unsigned int> (dataOut_sig.read()); //write data value for pointer.
    ren_sig.write(sc_logic_0);
    
    // std::cout << "\nWE GOT: " <<ack_sig.read().to_bool();
    return ack_sig.read().to_bool();
}

