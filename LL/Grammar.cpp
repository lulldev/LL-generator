#include <stdio.h>
#include "Grammar.hpp"
#include <boost/algorithm/string/regex.hpp>
#include <boost/optional.hpp>
#include <boost/regex.hpp>

using namespace std;

namespace
{
    const std::string LINE_SPLIT_PATTERN = "->|( +)";
    const std::string GUIDE_SET_SYMBOL = "/";
} // namespace

CGrammar::CGrammar()
: m_lineSplitRegex(boost::regex(LINE_SPLIT_PATTERN))
{
}

void CGrammar::ReadAndParseGrammar(std::istream& input)
{
    std::string line;
    std::string leftGrammarPart;
    
    std::vector<std::string> parsedLine;
    while (getline(input, line))
    {
        ParseLine(line, parsedLine);
        leftGrammarPart = parsedLine.at(0);
        parsedLine.erase(parsedLine.begin());
        
        Rule::RightPart::Items items;
        Rule::RightPart::Guides guides;
        
        bool isItems = true;
        for (const auto& parsedElement : parsedLine)
        {
            if (parsedElement == GUIDE_SET_SYMBOL)
            {
                isItems = false;
                continue;
            }
            
            if (isItems)
            {
                items.emplace_back(parsedElement);
            }
            else
            {
                guides.emplace(parsedElement);
            }
        }
        
        Rule::RightPart rightPart;
        rightPart.items = items;
        rightPart.guides = guides;
        
        size_t pos = GetRuleIndex(leftGrammarPart);
        if (pos == -1)
        {
            Rule newRule;
            newRule.leftPart = leftGrammarPart;
            newRule.rightParts = Rule::RightParts(1, rightPart);
            
            m_grammar.push_back(newRule);
        }
        else
        {
            m_grammar.at(pos).rightParts.emplace_back(rightPart);
        }
    }
}


CGrammar::Grammar CGrammar::GetGrammar() const
{
    return m_grammar;
}

void CGrammar::ParseLine(const std::string& line, std::vector<std::string>& splitResult) const
{
    boost::algorithm::split_regex(splitResult, line, m_lineSplitRegex);
}

/* return index of first rule with leftGrammarPart or -1 if rule not exist */
long CGrammar::GetRuleIndex(const std::string& leftGrammarPart) const
{
    auto comparator = [&leftGrammarPart](const Rule& rule) {
        return rule.leftPart == leftGrammarPart;
    };
    auto result = std::find_if(m_grammar.begin(), m_grammar.end(), comparator);
    
    return (result != m_grammar.end()) ? std::distance(m_grammar.begin(), result) : -1;
}


Rule::RightParts CGrammar::GetDifferentRingtParts(const Rule::RightParts& equals, size_t equalsLength)
{
    Rule::RightParts differentRightParts;
    
    /*for (auto equal : equals)
     {
     if (equal.size() == equalsLength)
     {
     differentRightParts.emplace_back(Rule::RightPart(1, ""));
     }
     if (equal.size() > equalsLength)
     {
     Rule::RightPart tmpRightPart;
     for (size_t i = equalsLength; i < equal.size(); ++i)
     {
     tmpRightPart.emplace_back(equal.at(i));
     }
     differentRightParts.push_back(tmpRightPart);
     }
     }*/
    
    return differentRightParts;
}

