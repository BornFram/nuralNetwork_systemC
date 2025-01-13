#include "coreController.h"

CoreController::CoreController(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),

    // main controller connection
    done("done_ch"),
    reset("reset"),
    wr_i("rd_i"), // wr_i0
    weights_addr("weights_addr"), 
    weights_size("weights_size"), 
    data_addr("data_addr"),
    result_addr("result_addr"),

    // memory connection
    memAddr_for_r("memAddr_for_r"), // addr_r_in_c0
    from_memory("from_memory"), // data_out_c0
    to_memory("to_memory"), // data_in_c0
    to_memory_addr("to_memory_addr"), // addr_w_in_c0
    wr_o("wr_o"),
    rd_o("rd_o")
{
    to_memory.initialize(0);
    done.initialize(true);
    wr_o.initialize(0);
    rd_o.initialize(0);
    
    SC_METHOD(process);
    sensitive << clk_i.pos();
    dont_initialize();
    
    SC_METHOD(stageCounter);
    sensitive << clk_i.pos();
    dont_initialize();
}

CoreController::~CoreController()
{
}

float CoreController::sigma(float value) {
        // return 1.f / (1.f + std::pow(2.718281828459045, -value));
        // todo: временно для тестов выводим просто число
        return value;
    }

void CoreController::stageCounter()
{
    if (reset.read()) {
        cout << "reset!" << endl;
        stage = 1;
    } else {
        if (this->processing) {
            this->stage += 1;
        }
    }
}

void CoreController::process()
{
    Pair values;

    switch (this->stage)
    {
    case 0:
        // processing is off
        done.write(true);
        memAddr_for_r.write(Pair(0,0));
        to_memory_addr.write(0);
        to_memory.write(0);
        wr_o.write(false);
        rd_o.write(1);
        memAddr_for_r.write(Pair(weights_addr.read(), data_addr.read()));
        this->processing = false;
        break;
    
    case 1:
        {
            // noop: waiting for answer
            this->processing=true;  
            done.write(false);
            rd_o.write(1);
            memAddr_for_r.write(Pair(weights_addr.read(), data_addr.read()));
            values = from_memory.read();
            cout << "stage " << this->stage <<  ". values weight " << values.left << ", data " << values.right << " " << Pair(weights_addr.read(), data_addr.read()) << endl;
            // rd_o.write(0);
            break;
        }
        case 2: {
            this->processing=true;  
            done.write(false);
            rd_o.write(1);
            memAddr_for_r.write(Pair(weights_addr.read() + 1, data_addr.read() + 1)); 
            break;
        }
    default:
        {
            // send request to memory for first elements
            // cout << "stage 1. request data " << weights_addr.read() << " " << data_addr.read() << endl;

            this->processing=true;  
            done.write(false);
            values = from_memory.read();
            cout << "stage "<< this->stage <<  ". values weight " << values.left << ", data " << values.right << endl;
            this->value += values.left * values.right;
            
            this->countedNeuronsAmount++;

            cout << "weights size " << weights_size.read() << endl;
            if (this->countedNeuronsAmount >= weights_size.read()) {
                rd_o.write(0);

                wr_o.write(1);
                to_memory_addr.write(result_addr.read());
                to_memory.write(this->sigma(this->value));
                this->processing = false;
                done.write(true);

                cout << "processing done" << endl;
                this->stage = 0;
            } else {
                rd_o.write(1);

                memAddr_for_r.write(Pair(weights_addr.read() + 1 + this->countedNeuronsAmount, data_addr.read() + 1 + this->countedNeuronsAmount));
            }
            break;
        }
    }
    // if (!this->processing) {
    //     if (this->wr_i.read()) {
    //         this->processing = true;
    //         done.write(false);
    //         cout << "done = false, and processing started" << endl;
    //     } else {
    //         this->processing = false;
    //         done.write(true);
    //     }
    // } else {
    //     if (!this->gotFromMemory) {
    //             cout << "no data in memory. request data " << weights_addr.read() << " " << data_addr.read() << endl;
    //             rd_o.write(1);
    //             memAddr_for_r.write(Pair(weights_addr.read(), data_addr.read()));

    //             this->gotFromMemory = true;
    //         } else {
                
    //         }
    //     }
}

