//
//  SADcomp.cpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-05.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//


#include "SADcomp.h"

void saad::func(){
    start_time = sc_time_stamp();
    for (block=0; block<NUM_BLOCKS; block++){
        
        sad = 0;
        wait(10,SC_NS);
        for (i=0; i<BLOCK_SIZE; i++){
            
            unsigned int v1, v2; //intermediates
            MEMORY -> Read(static_cast<unsigned int>(INPUT1_ADDR+(block*BLOCK_SIZE)+i), v1);
            cout << "IS V1:"<<v1;
            MEMORY -> Read(static_cast<unsigned int>(INPUT2_ADDR+(block*BLOCK_SIZE)+i), v2);
            cout << "IS V2:"<<v2;
            v = v1 - v2; //+10ns: Subtract
            std :: cout << "\nV1: " <<v1 << "\nV2: " << v2 <<"\nSubtract: "<< v;

            if( v < 0 ) v = -v; //+10ns: Compare
            sad += v; //+10ns: Addition
            
            wait(40,SC_NS); //one time wait
        }

        MEMORY->Write(static_cast<unsigned int>(SAD_OUTPUT_ADDR+block),sad);
        
        std:: cout << "\nSAD" << sad; //Print statement
    }
    end_time= sc_time_stamp();
    sc_time totaltime = (end_time-start_time);
    cout << "\nTotal time taken is: " << totaltime;
    sc_stop();
}




