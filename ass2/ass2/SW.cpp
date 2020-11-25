//
//  SW.cpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-23.
//

#include "SW.hpp"


void software::soft_mod(){
    
    std::cout<<"\nHI THIS SOFT_MOD WORKS\n";
    sc_time sw_s_time = sc_time_stamp();
    swbus->Request(SW_MST, IREG_ADDR, HW_RG_WRITE, 4);
    swbus->WriteData(LOOPS);
    swbus->WriteData(SIZE);
    swbus->WriteData(B_ADDR);
    swbus->WriteData(C_ADDR);
    swbus->WaitForAcknowledge(SW_MST);
    
    sc_time mul_s_time = sc_time_stamp();
    swbus->Request(SW_MST, BASE_ADDR, HW_MUL, NON_OPERATION_LEN);
    swbus->WaitForAcknowledge(SW_MST);
    mul_time = (sc_time_stamp()-mul_s_time);
    sw_time  = (sc_time_stamp()-sw_s_time);
    
    
    cout<<"\nSOFTWARE TIMING:"<<"\nMULTIPLY REQUEST: "<<mul_time<<"\nTOTAL SOFTWARE TIME:"<<sw_time;
    cout<<"\n_____________________________________\n";
    cout<<"\nMATRIX MULTIPLICATION COMPLETED\n";
    cout<<"\n_____________________________________\n";
    
    cout<<"\n°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸";
    cout<<"\n__̴ı̴̴̡̡̡ ̡͌l̡̡̡ ̡͌l̡*̡̡ ̴̡ı̴̴̡ ̡̡͡|̲̲̲͡͡͡ ̲▫̲͡ ̲̲̲͡͡π̲̲͡͡ ̲̲͡▫̲̲͡͡ ̲|̡̡̡ ̡ ̴̡ı̴̡̡ ̡͌l̡̡̡̡.___\n";
    cout<<"\n°º¤ø,¸¸,ø¤º°`°º¤ø,¸,ø¤°º¤ø,¸¸,ø¤º°`°º¤ø,¸\n";
    
    cout<<"Ƹ̵̡Ӝ̵̨̄Ʒ ♫♪.ılılıll|̲̅̅●̲̅̅|̲̅̅=̲̅̅|̲̅̅●̲̅̅|llılılı.♫♪ Ƹ̵̡Ӝ̵̨̄Ʒ\n";
    
    cout<<"\n______________FINAL OUTPUT_________________\n";
    swbus->Request(SW_MST, BASE_ADDR, MEM_PRINT, 0);
    swbus->WaitForAcknowledge(SW_MST);
    sc_stop();
    exit(0);
}

