/*
 Copyright (c) 2023, Slawomir Kuzniar.
 Distributed under the MIT License (http://opensource.org/licenses/MIT).
*/

#ifndef O3_UTILS_STRING_TRIM_H
#define O3_UTILS_STRING_TRIM_H

#include <string_view>

namespace O3::utils::string {

inline std::string_view
ltrim(std::string_view str, std::string_view what = " \t\n\r\f\v")
{
    const auto pos = str.find_first_not_of(what);
    str.remove_prefix(std::min(pos, str.size()));
    return str;
}

inline std::string_view
rtrim(std::string_view str, std::string_view what = " \t\n\r\f\v")
{
    const auto pos = str.find_last_not_of(what);
    str.remove_suffix(std::min(str.size() - pos - 1, str.size()));
    return str;
}

inline std::string_view
trim(std::string_view str, std::string_view what = " \t\n\r\f\v")
{
    return rtrim(ltrim(str, what), what);
}

inline bool
ends_with(std::string_view str, std::string_view suffix)
{
    return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

inline bool
starts_with(std::string_view str, std::string_view prefix)
{
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

} // namespace O3::utils::string

#endif
