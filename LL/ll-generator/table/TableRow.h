#pragma once

#include <stdio.h>
#include <boost/algorithm/string/regex.hpp>
#include <boost/optional.hpp>
#include <boost/regex.hpp>
#include <unordered_set>

struct TableRow
{
    explicit TableRow()
        : next(boost::none)
        , idAtStack(boost::none)
        , isError(true)
        , isEnd(false)
        , isShift(false)
        {
        }
    std::unordered_set<std::string> referencingSet;
    
    boost::optional<size_t> next;
    boost::optional<size_t> idAtStack;
    
    bool isEnd;
    bool isError;
    bool isShift;
};
