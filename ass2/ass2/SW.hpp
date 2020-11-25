//
//  SW.hpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-23.
//
#include "define.h"
#ifndef SW_hpp
#define SW_hpp

#include <stdio.h>
class software: public sc_module{
public:
    //LOOPS and Execution.
    sc_port<bus_master_if> swbus;
    void soft_mod();
    SC_CTOR(software){
        SC_THREAD(soft_mod);
        std::cout<<"\nRUNNING SOFTMOD\n";
    }
private:
//    sc_set_time_resolution(1,SC_NS);
    sc_time mul_time, sw_time;
};
//MARK: Connects directly to the bus_master only.
#endif /* SW_hpp */
