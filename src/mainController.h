#ifndef _MainController_H
#define _MainController_H

#include "systemc.h"


SC_MODULE(MainController)
{
    sc_in<bool>  clk_i;
    
    // memory connection
    sc_in<int>   from_memory;
    sc_out<int>  to_memory;
    sc_out<int>   memory_addr;
    sc_out<bool>  wr_o;
    sc_out<bool>  rd_o;

    // core connections
    sc_in<bool> done0;
    sc_out<bool> reset0;
    sc_out<bool> wr_o0;
    sc_out<int> weights_addr0;
    sc_out<int> weights_size0;
    sc_out<int> data_addr0;
    sc_out<int> result_addr0;
    
    SC_HAS_PROCESS(MainController);
    
    MainController(sc_module_name nm);
    ~MainController() = default;
    
    void thred();
    void process();
    void coreCount();

    void init();

private:

// 3 5 4 3 1 2 3 4 5 6 7 8 9 10 0 0 0 .... 5 10 20 30 
// 3 3 2 2 1 2 3 4 5 6 7 8 9 20 5 10 20 
    int layersCount = 3; // use
    int layersStruct[3] = {3, 2, 2}; // use

    int allNNStructSize = 18;
    int allNNstruct[18] = {
        3,
        3,2,2,
        10,
        1,2,3,4,5,6,7,8,9,10,
        33,22,11};

    int weightCount = 3 * 2 + 2 * 2; // use 
    int layerSizes[3] = {3, 2, 2};
    float weights[10000] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 20}; // use
    float data[49] = {5, 10, 20}; // use

    bool layersCountSaved = 0; 
    int layerSizesSavedAmount = 0;
    int weightsSavedAmount = 0;
    bool structSaved = 0;
    int dataSavedAmount = 0;
    
    int outLayerAdr = 2000; 
    int memoryTop = 10; // use
    int dataSize_addr = memoryTop + 1; // use

    int tmp = 0;
    int inferLayer = 1;
    int coresAmount = 1;
    int inferNeuron = 0;
    int coreCounter = 0;
    int resultCounter = 0;

    int layersLenBeforeLayer(int layer) {
        int res = 0;
        for (int i = 0; i < layer; i++) {
            res += this->layerSizes[i];
        }

        return res; 
    }
};


#endif
