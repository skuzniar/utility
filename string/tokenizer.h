/*
 Copyright (c) 2023, Slawomir Kuzniar.
 Distributed under the MIT License (http://opensource.org/licenses/MIT).
*/

#ifndef O3_UTILS_STRING_TOKENIZER_H
#define O3_UTILS_STRING_TOKENIZER_H

#include <string_view>
#include <iostream>
#include <utility>

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
          : m_tokenizer(&t)
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
            return m_tokenizer->m_str.substr(m_tok_beg, m_tok_end - m_tok_beg);
        }

        friend bool operator==(const iterator& a, const iterator& b)
        {
            return a.m_tok_beg == b.m_tok_beg;
        }

        friend bool operator!=(const iterator& a, const iterator& b)
        {
            return !operator==(a, b);
        }

        friend bool operator<(const iterator& a, const iterator& b)
        {
            return a.m_tok_beg < b.m_tok_beg;
        }

        friend bool operator>(const iterator& a, const iterator& b)
        {
            return a.m_tok_beg > b.m_tok_beg;
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
            return *this;
        }

        friend iterator operator+(iterator i, unsigned a)
        {
            for (unsigned j = 0; j < a; ++j)
                ++i;
            return i;
        }

        friend iterator operator+(unsigned a, iterator i)
        {
            return i + a;
        }

    private:
        void begin()
        {
            m_tok_beg = 0;
            m_tok_end = m_tokenizer->m_str.find(m_tokenizer->m_sep, m_tok_beg);
        }

        void end()
        {
            m_tok_beg = m_tok_end = infinity;
        }

        void increment()
        {
            m_tok_beg = m_tok_end == infinity ? m_tok_end : m_tok_end + 1;
            m_tok_end = m_tok_beg == infinity ? m_tok_beg : m_tokenizer->m_str.find(m_tokenizer->m_sep, m_tok_beg);
        }

        friend std::ostream& operator<<(std::ostream& os, const iterator& it)
        {
            return os << "bpos=" << it.m_tok_beg << ' ' << "epos=" << it.m_tok_end;
        }

        friend class tokenizer;

        const tokenizer*            m_tokenizer = nullptr;

        std::string_view::size_type m_tok_beg   = 0;
        std::string_view::size_type m_tok_end   = 0;

        static constexpr auto       infinity    = std::string_view::npos;
    };

    tokenizer(std::string_view str, char sep)
      : m_str(str)
      , m_sep(sep)
    {
    }

    tokenizer(std::string val, char sep)
      : m_val(std::move(val))
      , m_str(m_val)
      , m_sep(sep)
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

private:
    std::string      m_val;

    std::string_view m_str;
    char             m_sep;
};

} // namespace O3::utils::string

#endif
