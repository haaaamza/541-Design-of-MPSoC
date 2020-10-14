//
//  main.cpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-04.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//


#include "define.h"
#include "memorySystem.h"
#include "SADcomp.h"
#include "memRead.hpp"

enum string_code {
    ertl,
    esimp,
    enull
};

string_code hashit (std::string const& inString) {
    if (inString == "simp") return esimp;
    if (inString == "rtl") return ertl;
    return enull;
}


char* mem_filename;
//char* arr;
//int set = 1;
//char use = '1';
int clk_used = 0;
int sc_main(int argc, char* argv[]) {
//    if (argc<3){
//        cout<<"Too few arguments, see README.";
//        //return(1);
//    }else if (argc>3){
//        cout<<"Too many arguments, see README.";
//        return(1);
//    }else{
//        mem_filename = argv[2];
//        arr = argv[1];
//        use = arr[0];
//    }
        saad sadboi ("sad");
        memorySystem mem("mem0", mem_filename);
        sadboi.MEMORY(mem);
        cout<<"\nRTL Activated.\n";
        sc_start();
    
    
//    memory simp("simp0", mem_filename); //instance creation.
//    sadboi.MEMORY(simp);
//    cout<<"Simple Memory Activated.";
//    clk_used=10;
//    sc_start();
    
    
    
    
    return 0;
}

