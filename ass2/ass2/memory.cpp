//
//  memory.cpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-21.
//

#include "memory.hpp"
void memory::mem_init(){
    cout<<"\nRUNNING MEM INIT ";
    for (int i = 0; i<(ABC_LEN); i++){
        mem[A_ADDR+i] = a[i];
        mem[B_ADDR+i] = b[i];
    }
    cout<<"\n";
    for (int i=0; i<6; i++){
        for (int j=0; j<6; j++){
            cout<<mem[B_ADDR+i*SIZE+j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n\n\n";
}
void memory::mem_reset(unsigned int req_addr, unsigned int req_len){
    for (int i = 0; i<(req_len); i++){
        mem[req_addr+i] = 0;
    }
    cout<<"\nDONE MEM_RESET";
}
void memory::mem_module(){
    unsigned int req_addr, req_op, req_len;
    while (true){
        wait(6.66, SC_NS);
        membus->Listen(req_addr, req_op, req_len);
        if (req_op == MEM_WRITE || req_op == MEM_READ || req_op ==MEM_PRINT || req_op== MEM_RESET){
            //            cout<<"\nMEM GOT: OP"<<req_op<<", ADDR:"<<req_addr<<" REQ_LEN:"<<req_len<<"\n";
            if (MEM_START_ADDR<=req_addr && (req_addr)<MEM_END_ADDR){
                //                cout<<"\nWE ARE IN\n";
                if ((req_addr+req_len)>MEM_END_ADDR){
                    cout<<"MEM: BAD ACCESS";
                    sc_stop();
                }
                if (req_op == MEM_READ){
                    mem_read_bus (req_addr, req_len);
                }else if (req_op == MEM_WRITE){
                    //cout<<"\nCALLED MEM WRITE\n";
                    mem_write_bus(req_addr, req_len);
                }else if (req_op == MEM_PRINT){
                    cout<<"\nCALLED MEM_PRINT\n";
                    mem_print();
                }else if (req_op==MEM_RESET) {
                    mem_reset(req_addr, req_len);
                }else {
                    std::cout<<"\nWRONG MEMORY OPERATION PASSED\n";
                    sc_stop();
                }
                membus->Acknowledge();
            }
        }
    }
}
void memory::mem_read_bus(unsigned int req_addr, unsigned int req_len){
    for (int i = 0; i < req_len; i++) {
        membus->SendReadData(mem[req_addr + i]);
    }
}

void memory:: mem_write_bus(unsigned int req_addr, unsigned int req_len){
    //    cout<<"MEM WRITE!!!!";
    unsigned count =0;
    for (int i = 0; i < req_len; i++) {
        unsigned data;
        membus->ReceiveWriteData(data);
        mem[req_addr+i]=data;
        count ++;
    }
}

void memory::mem_print(){
    for (int i=0; i<6; i++){
        for (int k=0; k<6; k++){
            cout<<mem[i*SIZE+k+C_ADDR]<<" ";
            
        }
        cout<<"\n";
    }
}

