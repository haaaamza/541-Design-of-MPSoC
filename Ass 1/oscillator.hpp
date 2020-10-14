//
//  oscillator.hpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-11.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//
#include "define.h"

#ifndef oscillator_hpp
#define oscillator_hpp

SC_MODULE (oscillator) {
    void func();
    
    sc_out <sc_logic> out_clk;

    SC_CTOR(oscillator){
        SC_THREAD(func);
    }
    
};

#endif /* oscillator_hpp */
