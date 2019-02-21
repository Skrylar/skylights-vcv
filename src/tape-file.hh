#include <string>

class tape_file {
public:
   static const size_t TRACKS = 8;
protected:
   bool m_open;
   DoubleRingBuffer<Frame<TRACKS>, (1 << 15)> m_buffer;
   std::thread m_worker_thread;
public:
   tape_file();
   explicit tape_file(tape_file& other); // XXX optional; only for heavy classes
   virtual ~tape_file();

   // generates a filename suitable for throwing blindly in to a
   // recording bin and probably not overwriting anything
   static const std::string& generate_name() const;

   inline bool is_open() const { return m_open; }

   // sends a frame down to the tape
   inline void feed(Frame<TRACKS>& x) {
      if (m_open) m_buffer.push(x);
   }

   void open();
   void close();
};
