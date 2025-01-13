#include "memory.h"

Memory::Memory(sc_module_name nm)
    :sc_module(nm),

    clk_i("clk_i"),
    addr_in_mc( "addr_in_mc"),
    data_in_mc( "data_in_mc"),
    data_out_mc("data_out_mc"),
    wr_i_mc("wr_i_mc"), 
    rd_i_mc("rd_i_mc"),

    addr_w_in_c0("addr_w_in_c0"),
    addr_r_in_c0("addr_r_in_c0"),
    data_in_c0("data_in_c0"),
    data_out_c0("data_out_c0"),
    wr_i_c0("wr_i_c0"),
    rd_i_c0("rd_i_c0")

    //  addr_in_c1("addr_in_c1"),
    //  data_in_c1("data_in_c1"),
    // data_out_c1("data_out_c1"),
    //     wr_i_c1("wr_i_c1"),
    //     rd_i_c1("rd_i_c1"),

    //  addr_in_c2("addr_in_c2"),
    //  data_in_c2("data_in_c2"),
    // data_out_c2("data_out_c2"),
    //     wr_i_c2("wr_i_c2"),
    //     rd_i_c2("rd_i_c2"),

    //  addr_in_c3("addr_in_c3"),
    //  data_in_c3("data_in_c3"),
    // data_out_c3("data_out_c3"),
    //     wr_i_c3("wr_i_c3"),
    //     rd_i_c3("rd_i_c3")
{
    // init out signals
    data_out_mc.initialize(0);
    data_out_c0.initialize(Pair(0,0));
    // data_out_c1.initialize(0);
    // data_out_c2.initialize(0);
    // data_out_c3.initialize(0);
    
    SC_METHOD(write_to_mem);
    sensitive << clk_i.pos();
    dont_initialize();

    SC_METHOD(read_mem);
    sensitive << clk_i.pos();
    dont_initialize();

}

Memory::~Memory()
{
}

void Memory::write_to_mem()
{
    //std::cout << "" << endl;
    std::cout << sc_time_stamp() << "   ";
    if(wr_i_mc.read()) {
        cout << "(mc) write to " <<  addr_in_mc.read() << " value " << data_in_mc.read();
        mem[addr_in_mc.read()] = data_in_mc.read();
    }
    if(wr_i_c0.read()) {
        cout << "(c0) write to " <<  addr_w_in_c0.read() << " value " << data_in_c0.read();
        mem[addr_w_in_c0.read()] = data_in_c0.read();
    }
    else cout << endl;
    // if(                           wr_i_c1.read()) {
    //     mem[                    addr_in_c1.read()] = 
    //                             data_in_c1.read();
    //     cout << "write to " <<  addr_in_c1.read() 
    //             << " value " << data_in_c1.read() << endl;
    // }
    // if(                           wr_i_c2.read()) {
    //     mem[                    addr_in_c2.read()] = 
    //                             data_in_c2.read();
    //     cout << "write to " <<  addr_in_c2.read() 
    //             << " value " << data_in_c2.read() << endl;
    // }
    // if(                           wr_i_c3.read()) {
    //     mem[                    addr_in_c3.read()] = 
    //                             data_in_c3.read();
    //     cout << "write to " <<  addr_in_c3.read() 
    //             << " value " << data_in_c3.read() << endl;
    // }

}

void Memory::dump_mem(int len) {
    cout << "Memory: " << endl;
    
    for (int i = 0; i < len; i++) {
        if (i % 10 == 0) {
            cout << endl << i << "   ";
        }
        cout << mem[i] << " ";
    }

    cout << endl << "stop";
} 

void Memory::read_mem()
{
    //std::cout << sc_time_stamp() << "   ";
    if(rd_i_mc.read()) 
    {
        //cout << "(mc) read " <<  addr_in_mc.read() << " value " << data_in_mc.read();
        data_out_mc.write(mem[addr_in_mc.read()]);
    }
    
    if(rd_i_c0.read()) 
    {
        //cout << "(c0) read data from " << addr_r_in_c0.read().string() << endl;
        data_out_c0.write(
            Pair( 
                mem[(int)addr_r_in_c0.read().left], 
                mem[(int)addr_r_in_c0.read().right]) 
                );
    }

    // for (int i = 0; i < 100; i++) {
    //     cout << mem[i];
    // }
    // cout << endl;
}
