#pragma once

#include <cmath>
#include <cassert>

struct vtl5c3 {
   double m_up_eta;
   double m_down_eta;
   double m_value;

   vtl5c3():
      m_up_eta(0.0),
      m_down_eta(0.0),
      m_value(0.0)
   {
   }

   // if you don't set the sample rate, you are going to have a bad time
   void set_samplerate(double rate) {
      // TODO haven't figured out how the EWMA weight responds to rate change
      assert(rate == 44100.0);

      m_down_eta = 0.501578579;
      m_up_eta   = 0.314291241;
   }

   // emulates the response curve of the VTL51C; was derived by curve
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
