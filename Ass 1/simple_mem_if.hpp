//
//  simple_mem_if.hpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-07.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//

#include "define.h"


#ifndef simple_mem_if_hpp
#define simple_mem_if_hpp


class simple_mem_if : virtual public sc_interface
{
    public:
        virtual bool Write(unsigned int addr, unsigned int data) = 0;
        virtual bool Read(unsigned int addr, unsigned int& data) = 0;
};

#endif /* simple_mem_if_hpp */
