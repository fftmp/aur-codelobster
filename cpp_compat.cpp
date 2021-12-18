#include <stdarg.h>
#include <stdlib.h>
#include <stdexcept>

extern "C" void __cxa_throw_bad_array_new_length() { abort(); }
void operator delete(void* ptr, size_t size) noexcept(true) { ::operator delete(ptr); }
void operator delete[](void* ptr, size_t size) noexcept(true) { ::operator delete[](ptr); }

namespace std {

__attribute__((weak)) runtime_error::runtime_error(char const* s) : runtime_error(std::string(s)) {}
__attribute__((weak)) runtime_error::runtime_error(std::runtime_error const& o) : runtime_error(o.what()) {}

// copy-pasted from https://searchfox.org/mozilla-central/source/build/unix/stdc++compat/stdc++compat.cpp#148
void __attribute__((weak)) __throw_out_of_range_fmt(char const* fmt, ...) {
  va_list ap;
  char buf[1024];  // That should be big enough.

  va_start(ap, fmt);
  vsnprintf(buf, sizeof(buf), fmt, ap);
  buf[sizeof(buf) - 1] = 0;
  va_end(ap);

  __throw_range_error(buf);
}

}  // namespace std
