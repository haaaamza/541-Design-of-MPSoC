//
//  mem_RTL.cpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-10.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//

#include "mem_RTL.hpp"

/*
 If the Ren input is asserted, the memory will output the data within the location specified by the input Addr on the output DataOut, if the provided location is valid.
 If the Wen input is asserted, the memory will write the data provided by the input DataIn to the location specified by the input Addr, if the provided location is valid.
 If the specified location is a valid location within the memory, the Ack output should be asserted, otherwise the Ack should remain 0.
 We put ACK into unknown state sc_logic_X if Ren and Wen are not asserted.
 */
void MEMORY_RTL:: rtl(){
    
    int address = static_cast<unsigned int>(Addr.read());
    //std:: cout << address;
    if (address>=MEM_SIZE){
        (Ack.write(sc_logic_0));
        cout<<"not written";
        return;
    }
    
    if (Ren.read() == sc_logic_1){ //READ function
        DataOut.write(mem[Addr.read()]);
        Ack.write(sc_logic_1);
    }
    
    if (Wen.read() == sc_logic_1){ //WRITE function
        mem[Addr.read()] = DataIn.read();
        Ack.write(sc_logic_1);
    }
    
    if (Wen.read()==sc_logic_0 && Ren.read()==sc_logic_0){
        Ack.write(sc_logic_X); //not in use
        return;
    }
    
}
