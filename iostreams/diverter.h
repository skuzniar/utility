/*
 Copyright (c) 2023, Slawomir Kuzniar.
 Distributed under the MIT License (http://opensource.org/licenses/MIT).
*/

#ifndef O3_UTILS_IOSTREAMS_DIVERTER_H
#define O3_UTILS_IOSTREAMS_DIVERTER_H

#include <ostream>

namespace O3::utils::iostreams {

//----------------------------------------------------------------------------------------------------------------------
// Diverts one output stream to another
//----------------------------------------------------------------------------------------------------------------------
template<class CharT, class Traits = std::char_traits<CharT>>
class basic_diverter
{
public:
    basic_diverter(std::basic_ostream<CharT, Traits>& from, std::basic_ostream<CharT, Traits>& to)
      : m_from(&from)
      , m_sbuf(from.rdbuf(to.rdbuf()))
    {
    }

    ~basic_diverter()
    {
        m_from->rdbuf(m_sbuf);
    }

private:
    std::basic_ostream<CharT, Traits>*   m_from;
    std::basic_streambuf<CharT, Traits>* m_sbuf;
};

using diverter  = basic_diverter<char>;
using wdiverter = basic_diverter<wchar_t>;

} // namespace O3::utils::iostreams

#endif
