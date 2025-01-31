#!/bin/sh

# cleanup
rm -rf obj_dir
rm -f counter.vcd

# run Verilator to translate Veriliog to C++, including C++ testbench
verilator -Wall --cc --trace lfsr.sv --exe lfsr_tb.cpp

# build C++ project via make automatically generated by Verilator
make -j -C obj_dir -f Vlfsr.mk Vlfsr

#run executable simulation file
obj_dir/Vlfsr