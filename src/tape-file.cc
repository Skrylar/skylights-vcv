#include "tape-file.hh"
#include <chrono>
#include <iostream>
#include <sstream>
#include <cmath>

void tape_file::worker_function(tape_file* root) {
   root->m_fstream.open(assetGlobal(tape_file::generate_name()));
   root->write_riff_header();

   uint32_t samples_written = 0;
   while (root->m_open) {
      // reduce heat of this loop
      std::this_thread::sleep_for(std::chrono::milliseconds(10));

      while (!x.empty()) {
	 auto frame = root->m_buffer.pop();

	 for (size_t i = 0;
	      i < TRACKS;
	      i++)
	 {
	    int16_t sample =
	       floor(32767.0 *			    // 16-bit signed limit
		     (min(max(frame[i], -5.0), 5.0) // hard clip to valid CVs
		      / 10.0));	// counter rack's built-in gain
	    root->m_fstream << sample;
	 }

	 samples_written++;
      }
   }

   update_riff_counters(samples_written);   
   root->m_fstream.flush();
   root->m_fstream.close();
}

void tape_file::write_riff_header() {
   // riff chunk descriptor
   m_fstream << 'R' << 'I' << 'F' << 'F'; // mark as a riff file
   m_fstream << ((uint32_t)36);		  // size of entire riff chunk
   // XXX we have to seek back and update this either when we're done,
   // or periodically.
   m_fstream << 'W' << 'A' << 'V' << 'E'; // mark as a wav file

   // fmt chunk
   m_fstream << 'f' << 'm' << 't' << ' '
	     << (uint32_t)16	 // PCM subchunk size
	     << (uint16_t)1	 // PCM (uncompressed) audio
	     << (uint16_t)TRACKS // how many tracks we will be writing
	     << (uint32_t)44100  // TODO sync sample rate to rack
	     << (uint32_t)44100 * TRACKS * (BITRATE / 8) // byte rate
	     << (uint16_t)TRACKS * (BITRATE / 8) // block alignment
	     << (uint16_t)BITRATE;		 // 16 bits per sample
   
   // data chunk
   m_fstream << 'd' << 'a' << 't' << 'a'
	     << (uint32_t)0;	// samples * channels * (bitrate/8)
   // XXX we also have to seek and update this particular byte when we
   // are done or periodically
}

void tape_file::update_riff_counters(uint32_t samples) {
   uint32_t subchunk2_size = (TRACKS * (BITRATE / 8) * samples);
   m_fstream.seekp(4, std::ios_base::beg); // riff chunk size
   m_fstream << ((uint32_t)36 + subchunk2_size);
   m_fstream.seekp(40, std::ios_base::beg); // data chunk size
   m_fstream << ((uint32_t)subchunk2_size);
   m_fstream.seekp(0, std::ios_base::end);
}

static const std::string tape_file::generate_name() {
   auto time_now = std::chrono::system_clock::to_time_t
      (std::chrono::system_clock::now());

   std::istringstream buffer;
   buffer << std::put_time(std::localtime(&time_now), "%F %T") << ".wav";
   return buffer.str();
}

void tape_file::open() {
   if (m_open) close();

   // NB worker thread opens and manages the file handle
   m_worker_thread = std::thread(worker_function, this);
}

void tape_file::close() {
   if (!m_open) return;

   // NB worker thread will flush and close the file handle
   m_open = false;		// signal worker thread to quit
   m_worker_thread.join();	// wait for it to terminate
}
