#include "turing-module.hh"

#include <cmath>
#include <algorithm>
// const double SEMITONE = 1.0 / 12.0;

void turing_module::process(const ProcessArgs &args) {
   double mode;
   if (inputs[I_MODE].isConnected())
      mode = inputs[I_MODE].getVoltage();
   else
      mode = params[P_MODE].getValue();

   bool hot = m_sequence & 0x1;
   outputs[O_GATE].setVoltage(hot ? 10.0 : 0.0);
   outputs[O_PULSE].value =
		std::min(static_cast<double>(outputs[O_GATE].value * inputs[I_CLOCK].getVoltage()), 10.0);

   // check for clock advance
   auto was_high = m_clock_trigger.isHigh();
   m_clock_trigger.process(inputs[I_CLOCK].getVoltage());
   if (!was_high && was_high != m_clock_trigger.isHigh()) {
     // clock was advanced

     // write knob always zeroes our input
     if (params[P_WRITE].getValue() > 0.9) hot = false;
     else if (mode > 0.9) {
	 // leave hot alone
      } else if (mode > 0.55) {
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
      } else if (mode > 0.10) {
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
	   i < params[P_LENGTH].getValue();
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

      uint8_t signal_d = m_sequence & 0xFF;
      double signal_a = (((double)signal_d) / 255.0);
      outputs[O_VOLTAGE].value =
	(signal_a * params[P_SCALE].getValue()) // signal scaled by scale knob
	- (5.0 * params[P_POLE].getValue());    // shift to bi-polar on request

      // expander is always 10v unipolar
      outputs[O_EXPANSION].setVoltage((((double)m_sequence) / 65535.0) * 10.0);

      for (size_t i = 0;
	   i < 8;
	   i++)
      {
	 lights[L_LIGHT8-i].value = ((m_sequence & (1 << i)) > 0) ? 1.0 : 0.0;
      }
   }
}

turing_module::turing_module() : m_sequence(0) {
	this->Module::config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
}

turing_module::~turing_module() {
}

json_t* turing_module::dataToJson() {
   auto map = json_object();

   json_object_set_new(map, "sequence", json_integer(m_sequence));

   return map;
}

void turing_module::dataFromJson(json_t *root) {
   if (!root) return;

   auto seqo = json_object_get(root, "sequence");
   if (json_is_number(seqo)) {
      m_sequence = (uint16_t)json_integer_value(seqo);
   }
}

void turing_module::onReset() {
  Module::onReset();
  m_sequence = 0;
}

void turing_module::onRandomize() {
  Module::onRandomize();
  m_sequence = 0;
  for (size_t i = 0;
       i < 16;
       i++)
  {
     m_sequence += m_spigot.next() << i;
  }
}
