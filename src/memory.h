#ifndef _MEMORY_H
#define _MEMORY_H

#include "systemc.h"
#include "dto.h"

SC_MODULE(Memory)
{
    
    sc_in<bool>  clk_i;

    // main controller connection
    sc_in<int>   addr_in_mc;
    sc_in<int>   data_in_mc;
    sc_out<int>  data_out_mc;
    sc_in<bool>  wr_i_mc;
    sc_in<bool>  rd_i_mc;
    
    // core0 connection
    sc_in<int> addr_w_in_c0;
    sc_in<Pair> addr_r_in_c0;
    sc_in<int>   data_in_c0;
    sc_out<Pair> data_out_c0;
    sc_in<bool>     wr_i_c0;
    sc_in<bool>     rd_i_c0;

    // // core1 connection
    // sc_in<int>   addr_in_c1;
    // sc_in<int>   data_in_c1;
    // sc_out<int> data_out_c1;
    // sc_in<bool>     wr_i_c1;
    // sc_in<bool>     rd_i_c1;

    // // core2 connection
    // sc_in<int>   addr_in_c2;
    // sc_in<int>   data_in_c2;
    // sc_out<int> data_out_c2;
    // sc_in<bool>     wr_i_c2;
    // sc_in<bool>     rd_i_c2;

    // // core3 connection
    // sc_in<int>   addr_in_c3;
    // sc_in<int>   data_in_c3;
    // sc_out<int> data_out_c3;
    // sc_in<bool>     wr_i_c3;
    // sc_in<bool>     rd_i_c3;

    SC_HAS_PROCESS(Memory);
    
    Memory(sc_module_name nm);
    ~Memory();
    
    void write_to_mem();
    void read_mem();

public:
    void dump_mem(int len);
    
private: 
    int mem[100000];
};


#endif
