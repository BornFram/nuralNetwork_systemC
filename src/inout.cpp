#include "inout.h"
#include "TEST_DATA.h"

// using namespace std;

// InOut::InOut(sc_module_name nm)
//     :sc_module(nm),
//     clk_i("clk_i"),
//     data_in("data_in"),
//     data_in_flag("data_in_flag"),
//     data_out("data_out"),
//     struct_write_enable("structLoad")
// {
//     data_in.initialize(0);
//     data_out.initialize(0);
//     struct_write_enable.initialize(0);
    
//     SC_CTHREAD(mainThread, clk_i.pos());
    
// }

// InOut::~InOut() {}


// void InOut::mainThread()
// {
//     receive(true, structSize);
//     for (int i = 0; i < 3; i++) receive(true, layers[i]);
//     for (int i = 0; i < 832; i++) receive(true, weights[i]);
    
//     wait();
//     for(int i = 0; i < 49; i++) receive(false, check_data[i]);

//     wait();

//     if (data_in_flag) 
//     {
//         wait();
//         send(data_in);
//     }

//     sc_stop();

// }

// void InOut::send(float data_out)
// {
//     wait();
//     cout << "-> inout: send to debug:" << endl;
//     cout << "  -> data: " << hex << data_out << endl;
// }

// float InOut::receive(bool structLoad, float data_in)
// {
//     bool flag = false;
//     float received = 0.0;
//     wait();
//     cout << "<- inout: receive " << endl;
//     struct_write_enable.write(flag);
//     data_out.write(received);
//     wait();
    

// }

// int s =0;
// int nexto()
// {
//     if (s < 885) return TESTO_DATO[s];
// }