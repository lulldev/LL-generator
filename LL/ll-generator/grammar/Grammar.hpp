#pragma once
#include <vector>
#include "GrammarRule.hpp"
#include <boost/algorithm/string/regex.hpp>
#include <boost/optional.hpp>
#include <boost/regex.hpp>

class Grammar
{
public:
    Grammar();
    
    void ReadAndParseGrammar(std::istream& input);
    std::vector<Rule> GetGrammar() const;
    
private:
    void ParseLine(const std::string& line, std::vector<std::string>& splitResult) const;
    long GetRuleIndex(const std::string& leftGrammarPart) const;
    bool AreEquals(Rule::RightParts rightParts, size_t currPos) const;
    void ConvertRule(Rule& rule, const Rule::RightParts& equals, unsigned counter);
    Rule::RightPart GetEqualRightPart(const Rule::RightParts& equals) const;
    Rule::RightParts GetDifferentRingtParts(const Rule::RightParts& equals, size_t equalsLength);
    size_t GetMinSize(const Rule::RightParts& equals) const;
    
    std::vector<Rule> m_grammar;
    boost::regex m_lineSplitRegex;
};
