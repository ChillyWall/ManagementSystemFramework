#ifndef PMS_TYPES_HPP
#define PMS_TYPES_HPP

#include <cstdint>
#include <string>

namespace pms {
using std::string;
using Integer = std::int64_t;
using std::size_t;

// the c-style string type
using c_string = const char*;

} // namespace pms

#endif
