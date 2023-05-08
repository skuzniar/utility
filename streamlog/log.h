/*
 Copyright (c) 2023, Slawomir Kuzniar.
 Distributed under the MIT License (http://opensource.org/licenses/MIT).
*/

#ifndef O3_UTILS_STREAMLOG_LOG_H
#define O3_UTILS_STREAMLOG_LOG_H

#include <ostream>

namespace O3::utils::streamlog {

namespace detail {

// Helper functions to manage log level globally
inline int
loglevelidx()
{
    static int i = std::ios_base::xalloc();
    return i;
}

enum class threshold : int
{
    debug = 0b00000001,
    info  = 0b00000010,
    warn  = 0b00000100,
    error = 0b00001000,
    fatal = 0b00010000
};

enum class level : int
{
    debug = 0b00000001,
    info  = 0b00000011,
    warn  = 0b00000111,
    error = 0b00001111,
    fatal = 0b00011111
};

inline bool
operator&(threshold t, level l)
{
    return static_cast<int>(t) & static_cast<int>(l);
}

inline bool
operator&(level l, threshold t)
{
    return t & l;
}

template<class CharT, class Traits>
threshold
get_threshold(std::basic_ostream<CharT, Traits>& os)
{
    return static_cast<threshold>(os.iword(detail::loglevelidx()));
}

template<class CharT, class Traits>
threshold
set_threshold(std::basic_ostream<CharT, Traits>& os, threshold t)
{
    auto r                          = static_cast<threshold>(os.iword(detail::loglevelidx()));
    os.iword(detail::loglevelidx()) = static_cast<int>(t);
    return r;
}

} // namespace detail

namespace log {

using threshold = detail::threshold;
using level     = detail::level;

template<class CharT, class Traits>
threshold
set(std::basic_ostream<CharT, Traits>& os, threshold t)
{
    return detail::set_threshold(os, t);
}

inline const char*
name(threshold t)
{
    switch (t) {
        case threshold::debug:
            return "debug";
        case threshold::info:
            return "info";
        case threshold::warn:
            return "warn";
        case threshold::error:
            return "error";
        case threshold::fatal:
            return "fatal";
    }
    return "invalid";
}

inline const char*
name(level t)
{
    switch (t) {
        case level::debug:
            return "debug";
        case level::info:
            return "info";
        case level::warn:
            return "warn";
        case level::error:
            return "error";
        case level::fatal:
            return "fatal";
    }
    return "invalid";
}

} // namespace log

namespace detail {

template<typename O, level L>
class logat
{
    const O& m_o;

    template<class CharT, class Traits>
    void print(std::basic_ostream<CharT, Traits>& os) const
    {
        if (detail::get_threshold(os) & L) {
            os << m_o;
        }
    }

public:
    explicit logat(const O& o)
      : m_o(o)
    {
    }

    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const logat& x)
    {
        x.print(os);
        return os;
    }
};

} // namespace detail

namespace log {

// clang-format off
template<typename O> auto debug(const O& o) { return detail::logat<O, level::debug>(o); }
template<typename O> auto  info(const O& o) { return detail::logat<O, level::info> (o); }
template<typename O> auto  warn(const O& o) { return detail::logat<O, level::warn> (o); }
template<typename O> auto error(const O& o) { return detail::logat<O, level::error>(o); }
template<typename O> auto fatal(const O& o) { return detail::logat<O, level::fatal>(o); }
// clang-format on

} // namespace log

} // namespace O3::utils::streamlog

#endif
