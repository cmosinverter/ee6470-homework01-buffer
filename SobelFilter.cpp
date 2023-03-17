#include <cmath>
#include <vector>
#include "SobelFilter.h"

SobelFilter::SobelFilter(sc_module_name n) : sc_module(n) {
  SC_THREAD(do_filter);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}




void SobelFilter::do_filter() {

  std::vector<int> reds, greens, blues;
  unsigned char flag;
  int counter = 0;

  while (true) {

    flag = i_col_check.read();

    // Median filter
    int center_r, center_g, center_b;
    int sum_r = 0;
    int sum_g = 0;
    int sum_b = 0;

    if (flag == 1) {
      
      reds.clear();
      greens.clear();
      blues.clear();

      for (unsigned int v = 0; v < MASK_Y; ++v) {
        for (unsigned int u = 0; u < MASK_X; ++u) {
          reds.push_back(i_r.read());
          greens.push_back(i_g.read());
          blues.push_back(i_b.read());
        }
      }
      counter = 0;
    } else {

      reds[0 + (counter % 3)] = i_r.read();
      reds[3 + (counter % 3)] = i_r.read();
      reds[6 + (counter % 3)] = i_r.read();
      greens[0 + (counter % 3)] = i_g.read();
      greens[3 + (counter % 3)] = i_g.read();
      greens[6 + (counter % 3)] = i_g.read();
      blues[0 + (counter % 3)] = i_b.read();
      blues[3 + (counter % 3)] = i_b.read();
      blues[6 + (counter % 3)] = i_b.read();
      counter = counter + 1;

    }

    if (counter == 0) {
      center_r = reds[reds.size() / 2];
      center_g = greens[greens.size() / 2];
      center_b = blues[blues.size() / 2];
    } else {
      if ((counter % 3) == 1) {
        center_r = reds[5];
        center_g = greens[5];
        center_b = blues[5];
      }
      else if ((counter % 3) == 2) {
        center_r = reds[3];
        center_g = greens[3];
        center_b = blues[3];
      }
      else if ((counter % 3) == 0) {
        center_r = reds[4];
        center_g = greens[4];
        center_b = blues[4];
      }
    }

    std::sort(reds.begin(), reds.end());
    std::sort(greens.begin(), greens.end());
    std::sort(blues.begin(), blues.end());
    
    
    // Mean filter
    for (auto x: reds) {
        sum_r += x;
    }
    for (auto x: greens) {
        sum_g += x;
    }
    for (auto x: blues) {
        sum_b += x;
    }
    o_r.write(round((sum_r - center_r + 2 * reds[reds.size() / 2]) / 10));
    o_g.write(round((sum_g - center_g + 2 * greens[greens.size() / 2]) / 10));
    o_b.write(round((sum_b - center_b + 2 * blues[blues.size() / 2]) / 10));

    // o_r.write(reds[reds.size() / 2]);
    // o_g.write(greens[greens.size() / 2]);
    // o_b.write(blues[blues.size() / 2]);



    wait(10); //emulate module delay
  }
}
