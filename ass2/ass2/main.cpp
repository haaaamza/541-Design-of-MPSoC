//
//  main.cpp
//  ass2
//
//  Created by Hamza Mian on 2020-10-21.
//
#include "SW.hpp"
#include "HW.hpp"
#include "memory.hpp"
#include "bus.hpp"


int sc_main(int argc, char* argv[]) {// Total Cycles: 8193437

   //add preprocessing here, meaning a,b arrays in memory.
    //software sw;
    sc_set_time_resolution(1,SC_NS);
    bus schoolbus("homework");
//
    software soft("sw0");
    soft.swbus(schoolbus);
    

    hardware hard("floppydisk");
    hard.busmast(schoolbus);
    hard.busmin(schoolbus);
////
    memory amnesia("food");
    amnesia.membus(schoolbus);
//
    sc_start();
    
    return 0;
}
