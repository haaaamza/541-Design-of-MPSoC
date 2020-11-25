//
//  memory.hpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-21.
//
#include "define.h"
#ifndef memory_hpp
#define memory_hpp
class memory: public sc_module{
public:
    sc_port<bus_minion_if> membus;
    int a [36]  = {0,0,0,0,0,0,0,0,9,4,7,9,0,12,14,15,16,11,0,2,3,4,5,6,0,4,3,2,1,2,0,2,7,6,4,9};
    int b [36] = {0,0,0,0,0,0,0,0,9,4,7,9,0,12,14,15,16,11,0,2,3,4,5,6,0,4,3,2,1,2,0,2,7,6,4,9};
    unsigned int mem[MEM_SIZE] = {0};
    
    void mem_module();
    void mem_write_bus (unsigned int req_addr, unsigned int req_len);
    void mem_read_bus (unsigned int req_addr,unsigned int req_len);
    void mem_reset(unsigned int req_addr,unsigned int req_len);
    void mem_init();
    void mem_print();
    //LISTENS TO BUS_MINION AND OUTPUTS SOMETHING ON BUS IF CALLED
    SC_CTOR(memory){
        SC_THREAD(mem_init);
        SC_THREAD(mem_module);
    }
};
#endif /* memory_hpp */
