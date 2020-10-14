//
//  memory.cpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-10.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//

#include "memRead.hpp"

bool memory:: Write(unsigned int addr, unsigned int data){
    if (addr > MEM_SIZE){
        return false;
    }
   // std::cout<< "\nThe address is:"<< addr;
    mem[addr] = data;
    return true;
}

bool memory :: Read(unsigned int addr, unsigned int& data){
    
    if (addr > MEM_SIZE){
        return false;
    }
//    std::cout<< "\nThe address is:"<< addr;
    data = static_cast<unsigned int>(mem[addr]);
    return true;
}

