#include "bit-spigot.hh"
#include <immintrin.h>

#ifndef __RDRND__
#error "Bit spigot requires CPU rand number support!"
// we could use a cheap-o linear congruent generator instead, as many
// dsp programs do to generate their white noise. that falls outside
// the spirit of the turing machine (which uses physical random
// sources) but we could always consider doing it if it becomes a trouble
#endif

bit_spigot::bit_spigot(): m_data(0), m_taps(0) {
  reset();
}

void bit_spigot::reset() {
  unsigned int x;
  _rdrand32_step(&x);
  
  m_data = x;
  m_taps = sizeof(unsigned int) * 8;
}

bool bit_spigot::next() {
  if (m_taps == 0) reset();
  bool result = m_data & 0x1;
  m_data >>= 1;
  m_taps--;
  return result;
}
