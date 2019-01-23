#include "turing-module.hh"

#include <cmath>

const double SEMITONE = 1.0 / 12.0;

void turing_module::step() {
   double mode;
   if (inputs[I_MODE].active)
      mode = inputs[I_MODE].value;
   else
      mode = params[P_MODE].value;
   
   // check for clock advance
   auto was_high = m_clock_trigger.isHigh();
   m_clock_trigger.process(inputs[I_CLOCK].value);
   if (!was_high && was_high != m_clock_trigger.isHigh()) {
      // clock was advanced
      bool hot = m_sequence & 0x1;

      // write knob always zeroes our input
      if (params[P_WRITE].value > 0.9) hot = false;
      else if (mode > 0.66) {
	 // inverts about 13% of the time
	 const size_t TRIES = 3;
	 bool should_flip = true;
	 for (size_t i = 0;
	      i <= TRIES;
	      i++)
	 {
	    should_flip = (should_flip == m_spigot.next());
	    if (!should_flip) break;
	 }
	 hot = should_flip ? !hot : hot;
      } else if (mode > 0.33) {
	 // 50/50 invert
	 bool should_invert = m_spigot.next();
	 hot = should_invert ? !hot : hot;
      } else {
	 // always invert
	 hot = !hot;
      }

      // compute an advance mask based on step length, [2, 16)
      uint16_t mask = 0;
      size_t steps = 0;
      for (double i = 0;
	   i < params[P_LENGTH].value;
	   i += 1)
      {
	 mask <<= 1;
	 mask |= 0x1;
	 steps++;
      }

      uint16_t seq = m_sequence & mask;
      seq >>= 1;
      seq |= (hot ? 1 : 0) << (steps - 1);
      m_sequence &= ~mask;
      m_sequence += seq;
   }
}

turing_module::turing_module() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS), m_sequence(0) {
}

turing_module::~turing_module() {
}

json_t* turing_module::toJson() {
   // TODO sequencer state goes here
   return NULL;
}

void turing_module::fromJson(json_t *root) {
   // TODO
}
