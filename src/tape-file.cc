#include "tape-file.hh"
#include <chrono>
#include <sstream>

static
void worker_function(tape_file* root) {
   while (root->m_open) {
      // reduce heat of this loop
      std::this_thread::sleep_for(std::chrono::milliseconds(10));

      while (!x.empty()) {
	 auto frame = root->m_buffer.pop();
	 // TODO write frame to output file
      }
   }
}

const std::string& tape_file::generate_name() const {
   auto time_now = std::chrono::system_clock::to_time_t
      (std::chrono::system_clock::now());

   std::istringstream buffer;
   buffer << std::put_time(std::localtime(&time_now), "%F %T") << ".wav";
   return buffer.str();
}

void tape_file::open() {
   if (m_open) close();

   // TODO prep file handle

   m_worker_thread = std::thread(worker_function, this);
}

void tape_file::close() {
   if (!m_open) return;

   m_open = false;		// signal worker thread to quit
   m_worker_thread.join();	// wait for it to terminate

   // TODO flush file handle
}
