#pragma once

#include <stdio.h>
#include <vector>
#include <boost/algorithm/string/regex.hpp>
#include <boost/optional.hpp>
#include <boost/regex.hpp>

#include "GrammarRule.hpp"


class GrammarParser
{
public:
    std::vector<GrammarRule> Parse(std::istream& input);
private:
    void ParseLine(const std::string& line, std::vector<std::string>& splitResult) const;
    long GetRuleIndex(const std::string& leftGrammarPart, std::vector<GrammarRule>& grammar) const;
};
