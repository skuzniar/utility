/*
 Copyright (c) 2023, Slawomir Kuzniar.
 Distributed under the MIT License (http://opensource.org/licenses/MIT).
*/

#ifndef O3_UTILS_STREAMLOG_LOG_H
#define O3_UTILS_STREAMLOG_LOG_H

#include <ostream>
#include <type_traits>

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
    return (static_cast<unsigned>(t) & static_cast<unsigned>(l)) != 0;
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

template<typename O>
struct byval
{
    O m_o;

    explicit byval(O o)
      : m_o(std::move(o))
    {
    }
};

template<typename O>
struct byref
{
    const O& m_o;

    explicit byref(const O& o)
      : m_o(o)
    {
    }
};

} // namespace detail

namespace detail {

template<typename O, level L>
class logval : byval<O>
{
public:
    explicit logval(O o)
      : byval<O>(std::move(o))
    {
    }

    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const logval& x)
    {
        if (detail::get_threshold(os) & L) {
            os << x.m_o;
        }
        return os;
    }
};

template<typename O, level L>
class logref : byref<O>
{
public:
    explicit logref(const O& o)
      : byref<O>(o)
    {
    }

    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const logref& x)
    {
        if (detail::get_threshold(os) & L) {
            os << x.m_o;
        }
        return os;
    }
};

} // namespace detail

namespace log {

// clang-format off
template<typename O> auto debug(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::logref<O, level::debug>(o);} else {return detail::logval<O, level::debug>(std::forward<O>(o));}}
template<typename O> auto  info(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::logref<O,  level::info>(o);} else {return detail::logval<O,  level::info>(std::forward<O>(o));}}
template<typename O> auto  warn(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::logref<O,  level::warn>(o);} else {return detail::logval<O,  level::warn>(std::forward<O>(o));}}
template<typename O> auto error(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::logref<O, level::error>(o);} else {return detail::logval<O, level::error>(std::forward<O>(o));}}
template<typename O> auto fatal(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::logref<O, level::fatal>(o);} else {return detail::logval<O, level::fatal>(std::forward<O>(o));}}
// clang-format on

} // namespace log

namespace detail {

template<typename O>
class paintval : byval<O>
{
    const char* m_c;
public:
    paintval(O o, const char* c)
      : byval<O>(std::move(o))
      , m_c(c)
    {
    }

    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const paintval& x)
    {
        return os << char(033) << '[' << x.m_c << 'm' << x.m_o << char(033) << '[' << '0' << 'm';
    }
};

template<typename O>
class paintref : byref<O>
{
    const char* m_c;

public:
    paintref(const O& o, const char* c)
      : byref<O>(o)
      , m_c(c)
    {
    }

    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const paintref& x)
    {
        return os << char(033) << '[' << x.m_c << 'm' << x.m_o << char(033) << '[' << '0' << 'm';
    }
};

} // namespace detail

namespace log {

// clang-format off
template<typename O> auto     red(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::paintref(o, "31");} else {return detail::paintval(std::forward<O>(o), "31");}}
template<typename O> auto   green(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::paintref(o, "32");} else {return detail::paintval(std::forward<O>(o), "32");}}
template<typename O> auto  yellow(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::paintref(o, "33");} else {return detail::paintval(std::forward<O>(o), "33");}}
template<typename O> auto    blue(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::paintref(o, "34");} else {return detail::paintval(std::forward<O>(o), "34");}}
template<typename O> auto magenta(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::paintref(o, "35");} else {return detail::paintval(std::forward<O>(o), "35");}}
template<typename O> auto    cyan(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::paintref(o, "36");} else {return detail::paintval(std::forward<O>(o), "36");}}
template<typename O> auto   white(O&& o) {if constexpr (std::is_lvalue_reference_v<O>) {return detail::paintref(o, "37");} else {return detail::paintval(std::forward<O>(o), "37");}}

// clang-format on

} // namespace log

} // namespace O3::utils::streamlog

#endif
