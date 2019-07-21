// Copyright (c) 2019 by Joshua Cearley
// Creative Commons: CC-BY-SA

#pragma once

#include <cassert>
#include <cmath>

struct vtl5c3 {
  double m_up_eta;
  double m_down_eta;
  double m_value;

  vtl5c3() : m_up_eta(0.0), m_down_eta(0.0), m_value(0.0) {}

  // if you don't set the sample rate, you are going to have a bad time
  void set_samplerate(double rate) {
    assert(rate >= 8000.0);

    double inverse = 1.0 / rate;
    double a = 209.616712;
    double b = 0.000880319056;
    double c = 48113.5069;

    m_down_eta = (pow(inverse, 2) * c) + (inverse * a) + b;

    a = 2746.38887;
    b = 0.000319227063;
    c = -3665711.27;

    m_up_eta = (pow(inverse, 2) * c) + (inverse * a) + b;
  }

  // emulates the response curve of the VTL5C3; was derived by curve
  // fitting against the spec sheet provided by the manufacturer
  inline double curve(double x) {
    static const double a = 19977.0579;
    static const double b = 4.72586603;
    static const double c = 22.9420751;
    double resistance = (a * (std::pow(2.71828, (-b * x)))) + c;
    return (1.0 - (resistance / 20000.0));
  }

  // input is within [0, 1] instead of miliamps
  double step(double input) {
    // figure out which ramp we're using
    if (input > m_value) {
      double np = 1.0 - m_up_eta;
      m_value = (m_up_eta * input) + (np * m_value);
    } else {
      double np = 1.0 - m_down_eta;
      m_value = (m_down_eta * input) + (np * m_value);
    }
    return curve(m_value);
  }
};
