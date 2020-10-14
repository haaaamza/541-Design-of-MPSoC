//
//  oscillator.cpp
//  541ass1
//
//  Created by Hamza Mian on 2020-10-11.
//  Copyright © 2020 Hamza Mian. All rights reserved.
//

#include "oscillator.hpp"

void oscillator:: func() {
   while(true) {
      out_clk.write(sc_logic_0);
      wait(5, SC_NS);
      out_clk.write(sc_logic_1);
      wait(5, SC_NS);
   }
}
