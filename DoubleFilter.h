#ifndef DOUBLE_FILTER_H_
#define DOUBLE_FILTER_H_
#include <systemc>
using namespace sc_core;

#include "filter_def.h"

class DoubleFilter : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<unsigned char> i_r;
  sc_fifo_in<unsigned char> i_g;
  sc_fifo_in<unsigned char> i_b;
  sc_fifo_out<unsigned char> o_r;
  sc_fifo_out<unsigned char> o_g;
  sc_fifo_out<unsigned char> o_b;
  sc_fifo_in<unsigned char> i_col_check;

  SC_HAS_PROCESS(DoubleFilter);
  DoubleFilter(sc_module_name n);
  ~DoubleFilter() = default;

private:
  void do_filter();
};
#endif
