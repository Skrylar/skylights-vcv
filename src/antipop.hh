#pragma once

// allows you to turn off signal chains while smoothing over any DC
// offsets that would result in popping. does this by treating the
// gate status as a moving average and processing signals until the
// average is fully closed (zero.)
struct antipop_t {
  double integrator;
  double gate;

  antipop_t() : integrator(0.0), gate(0.0) {}

  antipop_t(double samplerate) : gate(0.0) { change_sample_rate(samplerate); }

  void change_sample_rate(double samplerate) {
    // based on Stephen Nahmias
    integrator = 2.0 / ((samplerate * 0.05) + 1.0);
  }

  inline bool is_open() {
    // NB I suspect "zero" is one of the few numbers that floats
    // actually CAN store reliably. Feel free to be mad when I'm
    // wrong and this bites someone in the ass.
    return gate > 0.0;
  }

  inline double step(double passthrough, double signal) {
    // update gate EWMA
    gate = (integrator * passthrough) + ((1.0 - integrator) * gate);
    // filter signal
    return signal * gate;
  }
};
