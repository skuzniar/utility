/*
 Copyright (c) 2023, Slawomir Kuzniar.
 Distributed under the MIT License (http://opensource.org/licenses/MIT).
*/

#ifndef O3_UTILS_STRING_TOKENIZER_H
#define O3_UTILS_STRING_TOKENIZER_H

#include <string_view>
#include <iostream>

namespace O3::utils::string {

//----------------------------------------------------------------------------------------------------------------------
// String view buffer tokenizer
//----------------------------------------------------------------------------------------------------------------------
class tokenizer
{
public:
    using token = std::string_view;

    class iterator
    {
    private:
        iterator(const tokenizer& t, bool beg)
          : m_host(&t)
          , m_epos(m_host->m_str.size())
        {
            beg ? begin() : end();
        }

    public:
        // Iterator traits
        using iterator_category = std::input_iterator_tag;
        using value_type        = token;
        using pointer           = token*;
        using reference         = token&;
        using difference_type   = std::ptrdiff_t;

        token operator*() const
        {
            auto len = m_tend - m_tbeg;
            return m_host->m_str.substr(m_tbeg, len);
        }

        friend bool operator==(const iterator& a, const iterator& b)
        {
            return a.m_tbeg == b.m_tbeg;
        }

        friend bool operator!=(const iterator& a, const iterator& b)
        {
            return !operator==(a, b);
        }

        friend bool operator<(const iterator& a, const iterator& b)
        {
            return a.m_tbeg < b.m_tbeg;
        }

        friend bool operator>(const iterator& a, const iterator& b)
        {
            return a.m_tbeg > b.m_tbeg;
        }

        friend bool operator<=(const iterator& a, const iterator& b)
        {
            return !operator>(a, b);
        }

        friend bool operator>=(const iterator& a, const iterator& b)
        {
            return !operator<(a, b);
        }

        iterator operator++(int)
        {
            iterator i(*this);
            ++(*this);
            return i;
        }

        iterator& operator++()
        {
            increment();
            while (m_host->m_skip_empty && m_tbeg == m_tend && m_tbeg != infinity) {
                increment();
            }
            return *this;
        }

        friend iterator operator+(iterator i, unsigned a)
        {
            for (unsigned j = 0; j < a; ++j) {
                ++i;
            }
            return i;
        }

        friend iterator operator+(unsigned a, iterator i)
        {
            return i + a;
        }

    private:
        void begin()
        {
            m_tbeg = 0;
            m_tend = std::min(m_epos, m_host->m_str.find_first_of(m_host->m_sep, m_tbeg));
            while (m_host->m_skip_empty && m_tbeg == m_tend && m_tbeg != infinity) {
                increment();
            }
        }

        void end()
        {
            m_tbeg = m_tend = infinity;
        }

        void increment()
        {
            m_tbeg = m_tend == m_epos ? infinity : m_tend + 1;
            m_tend = m_tend == m_epos ? infinity : std::min(m_epos, m_host->m_str.find_first_of(m_host->m_sep, m_tbeg));
        }

        friend std::ostream& operator<<(std::ostream& os, const iterator& it)
        {
            return os << "tbeg=" << it.m_tbeg << ' ' << "tend=" << it.m_tend << ' ' << "epos=" << it.m_epos
                      << std::endl;
        }

        friend class tokenizer;

        const tokenizer*            m_host = nullptr;
        std::string_view::size_type m_tbeg = 0;
        std::string_view::size_type m_tend = 0;
        std::string_view::size_type m_epos = 0;

        static constexpr auto infinity = std::string_view::npos;
    };

    tokenizer(std::string_view str, std::string_view sep, bool skip_empty = false)
      : m_str(str)
      , m_sep(sep)
      , m_skip_empty(skip_empty)
    {
    }

    [[nodiscard]] iterator begin() const
    {
        return { *this, true };
    }

    [[nodiscard]] iterator end() const
    {
        return { *this, false };
    }

    template<template<typename...> class C, class T = std::string_view>
    auto to() const
    {
        return C<T>{ begin(), end() };
    }

private:
    std::string_view m_str;
    std::string_view m_sep;
    bool             m_skip_empty = false;
};

inline tokenizer
tokenize(std::string_view str, std::string_view sep, bool skip_empty = false)
{
    return {str, sep, skip_empty};
}

} // namespace O3::utils::string

#endif
