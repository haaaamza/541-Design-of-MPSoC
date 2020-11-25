//
//  HW.cpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-22.
//

#include "HW.hpp"
/*ireg[0] = LOOPS.
 ireg[1] = SIZE
 ireg[2] = B_ADDR
 ireg[3] = C_ADDR
 */
void hardware::multiply(unsigned int req_addr){
    if (ireg[0]==0 && ireg[1]==0 && ireg[2]==0 && ireg[3]==0){
        std::cout<<"WRONG SPECIFICATION OF LOOPS!";
        sc_stop();
    }
    std::cout<<"N LOOPS is "<<ireg[0];
    int count = 0;
    sc_time start_time = sc_time_stamp();
    //____________________________PREPROCESSING________________________________//
    busmast->Request(HW_MST, req_addr, MEM_READ, REG_LEN);
    for (int i = 0; i<REG_LEN; i++){
        unsigned data;
        busmast->ReadData(data);
        reg[i] = data;
        busmast->WaitForAcknowledge(HW_MST);
    }
    do{
        //__________________________MATRIX MULT PSUEDOCODE___________________________________________//
        
        //__________________________CLEAR___________________________________________//
        sc_time reset_s_time = sc_time_stamp();
        busmast->Request(HW_MST, ireg[3], MEM_WRITE, ABC_LEN);
        for (int i=0; i<ABC_LEN; i++){
            busmast->WriteData(0);
        }
        busmast->WaitForAcknowledge(HW_MST);
        reset_time += (sc_time_stamp()-reset_s_time);
        
        //__________________________MATRIX MULTIPLICATION___________________________________________//
        //        for (int k=0; k<ireg[1]; k++){ //ORIGINAL PSEUDOCODE
        //            for (int i=0;  i<ireg[1]; i++){
        //                for (int j=0; j<ireg[1]; j++){
        //                    unsigned temp;
        //                    busmast->Request(HW_MST, ireg[2]+(j*ireg[1]+i), MEM_READ, 1);
        //                    busmast->ReadData(temp);
        //                    busmast->WaitForAcknowledge(HW_MST);
        //                    mla[(k)*ireg[1]+i]+=reg[k*ireg[1]+j]*temp;
        //                }
        //            }
        //        }
        sc_time mla_s_time = sc_time_stamp();
        for (int i=0;  i<ireg[1]; i++){
            for (int j=0; j<ireg[1]; j++){
                unsigned temp;
                busmast->Request(HW_MST, ireg[2]+(j*ireg[1]+i), MEM_READ, 1);
                busmast->ReadData(temp);
                busmast->WaitForAcknowledge(HW_MST);
                for (int k=0 ; k<SIZE; k++){ //reduces amount of read requests
                    mla[(k)*ireg[1]+i]+=reg[k*ireg[1]+j]*temp;
                }
            }
        }
        
        
        //        for (int i=0; i<6; i++){
        //            for (int k=0; k<6; k++){
        //                cout<<mla[i*ireg[1]+k]<<" ";
        //
        //            }
        //            cout<<"\n";
        //        }
        
        
        busmast->Request(HW_MST, ireg[3], MEM_WRITE, ABC_LEN);
        for (int i=0; i<ABC_LEN; i++){
            busmast->WriteData(mla[i]);
            mla[i]=0;
        }
        busmast->WaitForAcknowledge(HW_MST);
        mla_time += (sc_time_stamp()-mla_s_time);
        count ++;
        cout<<"\nCOUNT: "<<count;
        
        busmast->Request(HW_MST, BASE_ADDR, MEM_PRINT, 0);
        busmast->WaitForAcknowledge(HW_MST);
    }while(count<ireg[0]);
    
    //_______________TIMING_________________________
    mul_time += (sc_time_stamp()-start_time);
    mul_time.to_default_time_units();
    
    cout<<"\nHW TIMING:";
    cout<<"\nMULTIPLY FUNC TIME: "<<mul_time;
    //    cout<<"\n"<<sc_get_default_time_unit();
    cout<<"\nRESET LOOP TIME: "<<reset_time.to_default_time_units()<<" ns";
    cout<<"\nMULTIPLY LOOP TIME: "<<std::fixed<<std::setprecision(0)<<(mla_time.to_default_time_units())<<" ns";
    //__________________POPPING waks queue__________
    busmast->Request(HW_MST, NON_OPERATION_ADDR, NON_OPERATION, NON_OPERATION_LEN);
}
void hardware::reset(unsigned int req_addr, unsigned int req_len){
    cout<<"\nCalling RESET\n";
    busmast->Request(HW_MST, req_addr, MEM_WRITE, req_len);
    for (int i=0; i <req_len; i++){
        busmast->WriteData(0);
        //cout<<"\nWRITING DATA\n";
    }
    busmast->WaitForAcknowledge(HW_MST);
    cout<<"\nDONE RESET\n";
}

void hardware::operation(){
    unsigned req_addr, req_op, req_len;
    while(true){
        wait(6.66, SC_NS);
        busmin->Listen(req_addr, req_op, req_len);
        
        if ((req_op != MEM_WRITE && req_op != MEM_READ && req_op !=MEM_PRINT && req_op!= MEM_RESET) &&(req_addr>=MEM_START_ADDR && req_addr<REG_END_ADDR)){
            cout<<"\nHW LISTEN is OP:"<<req_op<<" LEN: "<<req_len<< " addr "<< req_addr<<"\n";
            //cout<<"\nHW LISTEN is OP:"<<req_op<<" LEN: "<<req_len<< " addr "<< req_addr;
            //if (MEM_START_ADDR<req_addr && req_addr<MEM_END_ADDR){ //MARK: Is this check required for HW?
            switch (req_op) {
                case HW_RG_WRITE:
                    req_addr = req_addr - IREG_ADDR;
                    cout << "\nREQ!!!: "<< req_addr;
                    if (req_addr>=IREG_B_ADDR &&(req_addr)<IREG_E_ADDR){
                        if ((req_addr+req_len)>IREG_E_ADDR){ //bound check
                            cout<<"HW: BAD ACCESS";
                            sc_stop();
                        }
                        for (int i = 0; i < req_len; i++) {
                            busmin->ReceiveWriteData(ireg[req_addr+i]);
                        }
                        busmin->Acknowledge();
                    }
                    break;
                case HW_RG_READ:
                    req_addr = req_addr - IREG_ADDR;
                    if (req_addr>=IREG_B_ADDR&&(req_addr)<IREG_E_ADDR){
                        if ((req_addr+req_len)>IREG_E_ADDR){ //bound check
                            cout<<"HW: BAD ACCESS";
                            sc_stop();
                        }
                        for (int i = 0; i < req_len; i++) {
                            busmin->SendReadData(ireg[req_addr + i]);
                        }
                        
                        cout<<"Called REG_READ";
                        busmin->Acknowledge();
                    }
                    break;
                case HW_RST: //the only function was to call this operation, so we call acknowledge here.
                    busmin->Acknowledge();
                    reset(req_addr, req_len);
                    break;
                case HW_MUL: //same reasoning as above.
                    if (req_addr < MEM_END_ADDR){
                        busmin->Acknowledge();
                        multiply(req_addr);
                    }else{
                        cout<<"WRONG MEMORY ACCESS";
                        sc_stop();
                    }
                    break;
                case BUS_CHECK:
                    busmin->Acknowledge();
                    std::cout << "\nTHIS BUS WORKS\n";
                    break;
                case NON_OPERATION:
                    busmin->Acknowledge();
                    break;
                default:
                    std::cout<<"WRONG HARDWARE OPERATION PASSED";
                    sc_stop();
                    break;
            }
            
        }
        
    }
}
