//
//  bus.hpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-21.
//
#include "define.h"
#include "simple_bus.h"
#ifndef bus_hpp
#define bus_hpp

class bus: public bus_master_if, public bus_minion_if, public sc_module{
    
public:
    virtual void Request(unsigned int mst_id, unsigned int addr, unsigned int op, unsigned int len);
    virtual bool WaitForAcknowledge(unsigned int mst_id);
    virtual void ReadData(unsigned int &data);
    virtual void WriteData(unsigned int data);
    virtual void Listen(unsigned int &req_addr, unsigned int &req_op, unsigned int &req_len);
    virtual void Acknowledge();
    virtual void SendReadData(unsigned int data);
    virtual void ReceiveWriteData(unsigned int &data);
    unsigned int sent_count = 0;
    SC_CTOR(bus){
        std::cout<<"BUS ON";
    }

    //MARK: ALL LISTEN TO BUS.
private:
    sc_logic state = SC_LOGIC_Z;
    sc_mutex maybe;
    
    struct bus_mst {
        unsigned int mst_id, op, addr, len;//, data;
        const char * operation;
    };

    int data_recv;
    std :: queue<bus_mst> que, waks;
    std :: queue<int> sc_fifo;
    
//    sc_set_time_resolution(1,SC_NS);
    sc_time readtime, writetime, ack_time, request_time;
};

#endif /* bus_hpp */
