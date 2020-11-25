//
//  bus.h
//  ass2
//
//  Created by Hamza Mian on 2020-10-21.
//
#ifndef simple_bus_h
#define simple_bus_h
// Bus Master Interface
class bus_master_if : virtual public sc_interface
{
public:
    virtual void Request(unsigned int mst_id, unsigned int addr, unsigned int op, unsigned int len) = 0;
    virtual bool WaitForAcknowledge(unsigned int mst_id) = 0;
    virtual void ReadData(unsigned int &data) = 0;
    virtual void WriteData(unsigned int data) = 0;
};


// Bus Minion Interface
class bus_minion_if : virtual public sc_interface
{
public:
    virtual void Listen(unsigned int &req_addr, unsigned int &req_op, unsigned int &req_len) = 0;
    virtual void Acknowledge() = 0;
    virtual void SendReadData(unsigned int data) = 0;
    virtual void ReceiveWriteData(unsigned int &data) = 0;
};

#endif /* bus_h */
