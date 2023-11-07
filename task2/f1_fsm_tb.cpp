#include "Vlfsr.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main (int argc, char **argv, char **env)
{
    int tick = 0;
    int clk = 0;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vlfsr *top = new Vlfsr;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    // init Vbuddy
    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab 3.2: f1_fsm");
    vbdSetMode(1); //Vbd flag in one shot mode

    // intialise simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simlation for 300 cycles

    for (tick = 0; tick < 300; tick++) {

        //dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2*tick+clk); // unit is in ps (periods)
            top->clk = !top->clk;
            top->eval();
        }

        //output result 
        vbdBar(top->data_out & 0xFF);

        top -> rst = (tick < 2) | (tick == 15);
        top -> en = vbdFlag();
        
        if (Verilated::gotFinish())  exit(0);
    }
}