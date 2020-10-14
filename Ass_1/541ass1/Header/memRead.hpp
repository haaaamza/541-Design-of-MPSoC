//
//  memRead.hpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-07.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//

//Simple Memory
#include "define.h"
#include "simple_mem_if.hpp"

#ifndef memRead_h
#define memRead_h
class memory: public simple_mem_if, public sc_module{
    
public:
    virtual bool Write(unsigned int addr, unsigned int data);
    virtual bool Read(unsigned int addr, unsigned int& data);
    
    memory(sc_module_name name, char* filename) :sc_module(name) { //reused from Part 2!
        std::ifstream outfp("Input.txt"); //ifstream tutorial from Fredosaurus, tutorialspoint.
        if (!outfp){
            cout << "Couldn't open file!\n";
            exit(1);
        }
        
        unsigned int data, i = 0;
        while(outfp >> data){
            if (i < MEM_SIZE){
                mem[i] = data;
                i++;
                
            }else {
                break;
            }
        }
        outfp.close(); //release resources
    }
    
    
    //-----------Internal variables-------------------
    unsigned int mem [MEM_SIZE] = {0}; //Prof Brett's Idea!
    
};

#endif /*memRead_hpp*/
