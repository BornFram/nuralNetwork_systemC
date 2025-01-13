#include "mainController.h"

MainController::MainController(sc_module_name nm)
    :sc_module(nm),
    clk_i("clk_i"),

    // memory connection
    memory_addr("memory_addr"),
    to_memory("to_memory"),
    from_memory("from_memory"),
    wr_o("wr_o"),
    rd_o("rd_o"),

     // core connections
    done0("done0"),
    reset0("reset0"),
    wr_o0("wr_i0"),
    weights_addr0("weights_addr0"),
    weights_size0("weights_size1"),
    data_addr0("data_addr1"),
    result_addr0("result_addr1")

{
    // init out connectors
    memory_addr.initialize(0);
    to_memory.initialize( 0);
    wr_o.initialize(0);
    rd_o.initialize(0);

    // init out connectors to core0
    wr_o0.initialize(0);
    reset0.initialize(0);

    SC_THREAD(thred);
    sensitive << clk_i.pos();// << from_memory.value_changed_event();
    dont_initialize();

    //SC_METHOD(process);
    //sensitive << clk_i.pos();

    SC_METHOD(coreCount);
    sensitive << clk_i.pos();
    dont_initialize();
}

// MainController::~MainController()
// {
// }

void MainController::coreCount() {
    this->coreCounter++;
    if (this->coreCounter >= this->coresAmount) {
        this->coreCounter = 0;
    }
}

void MainController::thred()
{
    // this thread for forward processing
    // есть проблема - для понимания, что данные записались, 
    // приходится одновременно кидать запрос на чтение, 
    // чтобы получить ответ

    wr_o.write(true);
    rd_o.write(true);
    for (int i=0; i < allNNStructSize; i++)
    {
        wr_o.write(true);
        rd_o.write(true);
        cout << "wr_o = " << wr_o << endl;
        wait(from_memory.value_changed_event());
        wr_o.write(false);
        rd_o.write(false);
        cout << "wr_o = " << wr_o << endl;
        to_memory.write(allNNstruct[i]);
        memory_addr.write(memoryTop);
        memoryTop++;
        cout << "rd_o = " << rd_o << endl;
    }
    wait(from_memory.value_changed_event());
    rd_o.write(false);
    wr_o.write(false);
    cout << "end load struct" << endl;

    cout << "wr_o = " << wr_o << endl;
    cout << "rd_o = " << rd_o << endl;

    wait(1, SC_SEC);
    // ------------------------------------
    // ------------ calc begin ------------


}

/*
void MainController::process()
{   
    wr_o.write(0);
  
  // TODO: вынести каунтер памяти во внешнюю функцию
  if (!this->structSaved) {
    if (!this->layersCountSaved) {
        this->layersCountSaved = true;
        wr_o.write(1);
        to_memory.write(this->layersCount);
        memory_addr.write(0);
    } else if (this->layerSizesSavedAmount != this->layersCount) {
        wr_o.write(1);
        to_memory.write(this->layerSizes[this->layerSizesSavedAmount]);
        this->layerSizesSavedAmount++;
        memory_addr.write(this->layerSizesSavedAmount);
    } else if (this->weightsSavedAmount != this->weightCount) {
        wr_o.write(1);
        to_memory.write(this->weights[this->weightsSavedAmount]);
        this->weightsSavedAmount++;
        memory_addr.write(this->layersCount + this->weightsSavedAmount);
    } else {
        wr_o.write(0);
        this->structSaved = true;
        cout << "something saved!" << endl ;
    }
  } else if (this->dataSavedAmount != this->layerSizes[0])  {
    wr_o.write(1);
    to_memory.write(this->data[this->dataSavedAmount]);

    this->dataSavedAmount++;
    memory_addr.write(this->layersCount + this->weightCount + this->dataSavedAmount);

    if (this->dataSavedAmount == this->layerSizes[0]) {
        cout << "data saved!" << endl;

    }
  } else {
    reset0.write(false);

    if (this->inferLayer != this->layersCount) {
        switch(this->coreCounter) {
        case 0:  {
            if (done0.read() && !reset0.read()) {
                if (this->tmp > 1000) {
                    sc_stop();
                }
                reset0.write(true);
                wr_o0.write(1);
                weights_addr0.write(1 + this->layersCount);

                weights_size0.write(this->layerSizes[this->inferLayer - 1]);
                data_addr0.write(1 + this->layersCount + this->weightCount);

                cout << "result addr " << this->layersCount << " " << this->weightCount << " " << this->layersLenBeforeLayer(this->inferLayer) << " " << this->inferLayer << " " << this->resultCounter << endl;
                result_addr0.write(this->layersCount + this->weightCount + this->layersLenBeforeLayer(this->inferLayer) + this->resultCounter);
                this->tmp++;
                this->resultCounter++;
            }
            break;
        }
        }

        if (this->resultCounter == this->layerSizes[this->inferLayer - 1]) {
            this->inferLayer += 1;
            this->resultCounter = 0;
        }
    }

    // cout << "hello " << this->tmp << " ";
    // rd_o.write(1);
    // memory_addr.write(this->tmp);
    // cout << from_memory.read() << endl;

    // this->tmp--;
    // if (this->tmp < 0) {
    //     sc_stop();
    // }
  }
}

*/

/* это типа тоже загрузка в память
// ----- write layers count ----- 
    to_memory.write(layersCount);
    memory_addr.write(memoryTop);
    wr_o.write(true);
    rd_o.write(true);
    memoryTop += 1;
wait(from_memory.value_changed_event());
    wr_o.write(false);
    
    for (int i=0;i < layersCount; i++)
    {
        to_memory.write(layersStruct[i]);
        memory_addr.write(memoryTop);
        memoryTop++;
        wr_o.write(true);
        wait(from_memory.value_changed_event());
        wr_o.write(false);
    }
    wait(from_memory.value_changed_event());

    // ---- write weightCount ----- 
    to_memory.write(weightCount);
    memory_addr.write(memoryTop);
    memoryTop++;
    wait(from_memory.value_changed_event());

    // ----- write weights ----- 
    for (int i=0;i < weightCount; i++)
    {
        to_memory.write(weights[i]);
        memory_addr.write(memoryTop);
        memoryTop++;
        wr_o.write(true);
        wait(from_memory.value_changed_event());
        wr_o.write(false);
    }
    wait(from_memory.value_changed_event());
    wr_o.write(false);
    rd_o.write(false);
    // end of write neural network structure ---------
    
    // ----- write data ----- 
    rd_o.write(true);
    memory_addr.write(dataSize_addr);
    wait(from_memory.value_changed_event());
    wr_o.write(false);
    rd_o.write(false);

    for (int i=0;i < from_memory; i++)
    {
        to_memory.write(data[i]);
        memory_addr.write(memoryTop);
        memoryTop++;
        wr_o.write(true);
        wait(from_memory.value_changed_event());
        wr_o.write(false);
    }

    wr_o.write(true);
    rd_o.write(true);
    wait(from_memory.value_changed_event());
    wr_o.write(false);
    rd_o.write(false);
*/