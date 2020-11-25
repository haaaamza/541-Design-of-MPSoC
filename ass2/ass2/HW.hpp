//
//  HW.hpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-22.
//
#include "define.h"
#ifndef HW_hpp
#define HW_hpp
class hardware: public sc_module{
public:
    sc_port<bus_master_if> busmast;
    sc_port<bus_minion_if> busmin;
    //    void hw_module();
    //    void hw_write_bus (unsigned int adrr,unsigned int op, unsigned int len); //minion functions
    //    void hw_read_bus (unsigned int adrr,unsigned int op, unsigned int len);
    //    void matrix_mult();
    void reset(unsigned int req_addr, unsigned int req_len);
    void multiply (unsigned int req_addr);
    void operation();
    unsigned int ireg[6] = {};
    //MEMORY ACCESS? OR JUST LEAVE THAT TO THE MEMORY AND MULTIPLICATION
    SC_CTOR(hardware){
        SC_THREAD(operation);
    }
private:
    
    unsigned int reg[REG_LEN] = {};
    unsigned int mla [MLA_LEN] ={};
//    sc_set_default_time_unit(SC_NS);
    sc_time mul_time, reset_time, mla_time;
};
#endif /* HW_hpp */
