#ifndef _CoreController_H
#define _CoreController_H

#include "systemc.h"
#include "dto.h"


SC_MODULE(CoreController)
{
    sc_in<bool>  clk_i;

    // main controller connection
    sc_in<bool> reset;
    sc_in<bool> wr_i;
    sc_in<int> weights_addr;
    sc_in<int> weights_size;
    sc_in<int> data_addr;
    sc_in<int> result_addr;
    sc_out<bool> done;

    // memory connection
    sc_in<Pair>   from_memory;
    sc_out<Pair>   memAddr_for_r;
    sc_out<int>  to_memory_addr;
    sc_out<int>  to_memory;
    sc_out<bool>  wr_o;
    sc_out<bool>  rd_o;
    
    SC_HAS_PROCESS(CoreController);
    
    CoreController(sc_module_name nm);
    ~CoreController();
    
    void process();
    void stageCounter();

    void init();

    float sigma(float value);

private:

    bool processing = false;
    bool gotFromMemory = false;
    int countedNeuronsAmount = 0;
    int stage = 0;

    float value = 0;

};


#endif
