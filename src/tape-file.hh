#pragma once

#include "skylights.hh"
#include <string>
#include <thread>

class tape_file {
public:
   static const int BITRATE = 16;
   static const size_t TRACKS = 8;
protected:
   bool m_open;			// whether tape is recording
   std::fstream m_fstream;	// stream to wav file
   DoubleRingBuffer<Frame<TRACKS>, (1 << 15)> m_buffer;
   std::thread m_worker_thread;	// handle to worker thread

   void write_riff_header();
   void update_riff_counters(uint32_t samples);

   static void worker_function(tape_file* root);
public:
   tape_file();
   explicit tape_file(tape_file& other); // XXX optional; only for heavy classes
   virtual ~tape_file();

   // generates a filename suitable for throwing blindly in to a
   // recording bin and probably not overwriting anything
   static const std::string& generate_name();

   inline bool is_open() const { return m_open; }

   // sends a frame down to the tape
   inline void feed(Frame<TRACKS>& x) {
      if (m_open) m_buffer.push(x);
   }

   void open();
   void close();
};
