//
//  bus.cpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-21.
//

#include "bus.hpp"

void bus ::Request(unsigned int mst_id, unsigned int addr, unsigned int op, unsigned int len){
    /*The bus Request() should provide all information necessary to indicate what transaction is requested on the bus. During the Request(), sufficient information should be provided such that any minion component listening to the bus will receive the required information for responding (or determining if they should respond) to the request.*/
    sc_time request_s_time = sc_time_stamp();
    const char* operation = "";
    switch (op) {
        case 0:
            operation= "MEM_PRINT";
            break;
        case 1:
            operation="MEM_READ";
            break;
        case 2:
            operation = "MEM_WRITE";
            break;
        case 3:
            operation= "HW_MUL";
            break;
        case 4:
            operation="HW_RST";
            break;
        case 5:
            operation= "HW_RG_WRITE";
            break;
        case 6:
            operation="HW_RG_READ";
            break;
        default:
            break;
    }
    if (mst_id ==SW_MST /*||(mst_id==HW_MST && op==NON_OPERATION)*/){cout<<"\nINPUT BUS is OP: "<<operation<<" LEN: "<<len<< " addr: "<< addr<< " MST: " << mst_id;}
    
    if(op==NON_OPERATION){//meaning we ended MUL (only time this is called here!)
        cout<<"\n_____________________________________\n";
        cout<<"\nTIMING:";
        cout<<"\nREQUEST: "<<request_time;
        cout<<"\nREAD: "<<readtime;
        cout<<"\nWRITE: "<<writetime;
        cout<<"\nACK: "<< ack_time;
        cout<<"\n_____________________________________\n";
    }
    
    bus_mst data_1;
    data_1.mst_id = mst_id;
    data_1.op = op;
    data_1.addr = addr;
    data_1.len = len;
    data_1.operation = operation;
    que.push(data_1);
    while (que.front().mst_id != mst_id && que.front().op != op && que.front().addr != addr && que.front().len !=len){
        wait(1.11, SC_NS);
    }//ensure synchronization of request for R/W
    
    request_time += (sc_time_stamp()-request_s_time);
    
}
void bus:: WriteData(unsigned int data){
    sc_time write_s_time = sc_time_stamp();
    if (sc_fifo.size() < que.front().len){ //MARK: Check is not valid since we push/pop the sc_fifo
        sc_fifo.push(data); //next len in queue is next node len +1
    }
    writetime += (sc_time_stamp()-write_s_time);
}
void bus :: ReadData(unsigned int& data){
    sc_time read_s_time = sc_time_stamp();
    if (sc_fifo.size() <= que.front().len){
        while(sc_fifo.empty()){
            wait(1.11, SC_NS);
        }
        data = sc_fifo.front();
        sc_fifo.pop();
        sent_count ++;
    }
    readtime += (sc_time_stamp() - read_s_time);
}

void bus:: Listen(unsigned int &req_addr, unsigned int &req_op, unsigned int &req_len){
    req_op = que.front().op;
    req_len = que.front().len;
    req_addr = que.front().addr;
}
void bus:: SendReadData(unsigned int data){
    if (sc_fifo.size() < que.front().len){
        sc_fifo.push(data);
    }
}
bool bus::WaitForAcknowledge(unsigned int mst_id){
    while (!state.is_01() || mst_id != que.front().mst_id){ //state=false OR mst_id!=cur_id
        wait(1.11, SC_NS);
//        cout<<"\nSTUCK IN W***\n";
//        cout<<"\nBUS is OP: "<<que.front().op<<" LEN: "<<que.front().len<< " addr: "<< que.front().addr<< " MST: " << que.front().mst_id<<"\n";
    }
    state = SC_LOGIC_Z; //false i.e. not in use
    if (que.front().len == NON_OPERATION_LEN){
        waks.push(que.front());
        que.pop();
        int count = 0;
        while (waks.front().len ==NON_OPERATION_LEN) {
            count ++;
            wait(1.11, SC_NS);
            if (que.front().op ==NON_OPERATION){
                waks.pop();
                que.pop();
                return true;
            }
        }
    }
    if(que.front().len==sent_count && que.front().op != NON_OPERATION){
        sent_count=0;
        que.pop();
    }
    return true;
}
void bus::Acknowledge(){
    sc_time ack_s_time = sc_time_stamp();
    do{
        wait(1.11, SC_NS);
    }while(state.is_01()); //1 CK for ACK. //I.E: We always run once before check.
    state = SC_LOGIC_1; //= true
    ack_time += (sc_time_stamp()-ack_s_time);
}
void bus:: ReceiveWriteData(unsigned int &data){
    if (sc_fifo.size() <= que.front().len){
        while (sc_fifo.empty()){
        }
        data = sc_fifo.front();
        sc_fifo.pop();
        sent_count++;
    }
}

