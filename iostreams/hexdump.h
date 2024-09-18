/*
 Copyright (c) 2023, Slawomir Kuzniar.
 Distributed under the MIT License (http://opensource.org/licenses/MIT).
*/

#ifndef O3_UTILS_IOSTREAMS_HEXDUMP_H
#define O3_UTILS_IOSTREAMS_HEXDUMP_H

#include <ostream>
#include <iomanip>
#include <limits>

namespace O3::utils::iostreams {

//----------------------------------------------------------------------------------------------------------------------
// Print binary data as hexadecimal numbers
//----------------------------------------------------------------------------------------------------------------------
namespace detail {

class hexdump_wrapper
{
    const void* m_buf;
    std::size_t m_len;
    std::size_t m_cpl;

    template<class CharT, class Traits>
    void print(std::basic_ostream<CharT, Traits>& os) const
    {
        const auto* cbuf = reinterpret_cast<const unsigned char*>(m_buf);

        for (std::size_t i = 0; i < m_len; ++i) {
            if (m_cpl != std::numeric_limits<std::size_t>::max() && i % m_cpl == 0) {
                os << (i == 0 ? "" : "\n") << std::setw(6) << std::setfill('0') << i << std::dec << ' ';
            }

            int c = cbuf[i];
            if (std::isgraph(c) != 0) {
                os << std::setw(3) << std::setfill(' ') << cbuf[i] << ' ';
            } else if (std::iscntrl(c) != 0) {
                switch (c) {
                    case '\t':
                        os << std::setw(3) << std::setfill(' ') << "\\t" << ' ';
                        break;
                    case '\n':
                        os << std::setw(3) << std::setfill(' ') << "\\n" << ' ';
                        break;
                    case '\v':
                        os << std::setw(3) << std::setfill(' ') << "\\v" << ' ';
                        break;
                    case '\f':
                        os << std::setw(3) << std::setfill(' ') << "\\f" << ' ';
                        break;
                    case '\r':
                        os << std::setw(3) << std::setfill(' ') << "\\r" << ' ';
                        break;
                    case 0x7f:
                        os << std::setw(3) << std::setfill(' ') << "\\b" << ' ';
                        break;
                    default:
                        os << 'x' << std::setw(2) << std::setfill('0') << std::hex << c << std::dec << ' ';
                        break;
                }
            } else if (cbuf[i] == ' ') {
                os << std::setw(3) << "' '" << ' ';
            } else {
                os << 'x' << std::setw(2) << std::setfill('0') << std::hex << c << std::dec << ' ';
            }
        }
    }

public:
    hexdump_wrapper(const void* buf,
                    std::size_t len,
                    std::size_t chars_per_line = std::numeric_limits<std::size_t>::max())
      : m_buf(buf)
      , m_len(len)
      , m_cpl(chars_per_line)
    {
    }

    template<class CharT, class Traits>
    friend std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os,
                                                         const hexdump_wrapper&             x)
    {
        x.print(os);
        return os;
    }
};

} // namespace detail

inline detail::hexdump_wrapper
hexdump(const void* buf, std::size_t len, std::size_t chars_per_line = std::numeric_limits<std::size_t>::max())
{
    return { buf, len, chars_per_line };
}

} // namespace O3::utils::iostreams

#endif
