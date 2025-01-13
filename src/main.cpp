#include "mainController.h"
#include "memory.h"
#include "coreController.h"
// #include "inout.h"

int sc_main(int argc, char* argv[])
{
    // init modules
    MainController mainCon("cpu");
    Memory memory("memory");
    CoreController core0("core_0");
    // InOut inOut("InOut");

    cout << "neuro procecor starto" << endl;
    cout << "~~~~~el neuro-procesador empezó a contar~~~~~" << endl;
    
    sc_clock clk("clk", sc_time(10, SC_NS));
    sc_signal<int> mc_mem_addr;
    sc_signal<int> mc_w_mem_data;
    sc_signal<int> mem_w_mc_data;
    sc_signal<bool> wr;
    sc_signal<bool> rd;

    // ---- signals -----
    // done cores connection to MainCon
    sc_signal<bool> core0_done;
    sc_signal<bool> core0_reset;

    // for each cores:

    // --- core0
    // core0 - mainCon
    sc_signal<bool> core0_wr_i;
    sc_signal<int> weights_addr0;
    sc_signal<int> weights_size0;
    sc_signal<int> data_addr0;
    sc_signal<int> result_addr0;
    // core0 - memory 
    sc_signal<Pair>   core0_r_mem_addr_P;
    sc_signal<Pair>   mem_w_core0_data_P;
    sc_signal<int>  core0_w_mem_data;
    sc_signal<int>  core0_w_mem_addr;
    sc_signal<bool>  core0_w_mem;
    sc_signal<bool>  core0_r_mem;

    // --- core1
    // core - mainCon

    // core - memory 


    // ---- signals ----- //

    // ----- modules connections -----
    // connect modules
    core0.clk_i(clk);
    core0.done(core0_done);
    core0.reset(core0_reset);
    core0.wr_i(core0_wr_i);
    core0.weights_addr(weights_addr0);
    core0.weights_size(weights_size0);
    core0.data_addr(data_addr0);
    core0.result_addr(result_addr0);
    
    core0.memAddr_for_r(core0_r_mem_addr_P); // addr_r_in_c0
    core0.from_memory(mem_w_core0_data_P); // data_out_c0
    core0.to_memory(core0_w_mem_data); // data_in_c0
    core0.to_memory_addr(core0_w_mem_addr); // addr_w_in_c0
    core0.wr_o(core0_w_mem); // wr_i_c0
    core0.rd_o(core0_r_mem); // rd_i_c0

    // main controller
    mainCon.clk_i(clk);
    mainCon.memory_addr(mc_mem_addr);
    mainCon.from_memory(mem_w_mc_data);
    mainCon.to_memory(mc_w_mem_data);
    mainCon.wr_o(wr);
    mainCon.rd_o(rd);
    // mainCon with core0
    mainCon.done0(core0_done);
    mainCon.reset0(core0_reset);
    mainCon.wr_o0(core0_wr_i);
    mainCon.weights_addr0(weights_addr0);
    mainCon.weights_size0(weights_size0);
    mainCon.data_addr0(data_addr0);
    mainCon.result_addr0(result_addr0);

    // memory with mainCon
    memory.clk_i(clk);
    memory.addr_in_mc(mc_mem_addr);
    memory.data_in_mc(mc_w_mem_data);
    memory.data_out_mc(mem_w_mc_data);
    memory.wr_i_mc(wr);
    memory.rd_i_mc(rd);
    // memory with core0
    memory.addr_w_in_c0(core0_w_mem_addr);
    memory.addr_r_in_c0(core0_r_mem_addr_P);
    memory.data_in_c0(core0_w_mem_data);
    memory.data_out_c0(mem_w_core0_data_P);
    memory.wr_i_c0(core0_w_mem);
    memory.rd_i_c0(core0_r_mem);
    // ----- modules connections ----- //


    
    // sc_trace_file *wf = sc_create_vcd_trace_file("wave");
    // sc_trace(wf, clk, "clk");
    // sc_trace(wf, mc_mem_addr, "addr_bo");
    // sc_trace(wf, data_cpu_bi, "data_bi");
    // sc_trace(wf, data_cpu_bo, "data_bo");
    // sc_trace(wf, wr, "wr");
    // sc_trace(wf, rd, "rd");

    //sc_start();
    sc_start(1, SC_SEC);

    memory.dump_mem(100);

 
    // sc_close_vcd_trace_file(wf);
    
    return(0);
}
