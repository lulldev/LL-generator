#include "GrammarParser.hpp"


std::vector<GrammarRule> GrammarParser::Parse(std::istream& input)
{
    std::vector<GrammarRule> grammar = std::vector<GrammarRule>();
    std::string line;
    std::string leftGrammarPart;
    
    std::vector<std::string> parsedLine;
    while (getline(input, line))
    {
        ParseLine(line, parsedLine);
        leftGrammarPart = parsedLine.at(0);
        parsedLine.erase(parsedLine.begin());
        
        GrammarRule::RightPart::Items items;
        GrammarRule::RightPart::Guides guides;
        
        bool isItems = true;
        for (const auto& parsedElement : parsedLine)
        {
            if (parsedElement == "/")
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
        
        GrammarRule::RightPart rightPart;
        rightPart.items = items;
        rightPart.guides = guides;
        
        size_t pos = GetRuleIndex(leftGrammarPart, grammar);
        if (pos == -1)
        {
            GrammarRule newRule;
            newRule.leftPart = leftGrammarPart;
            newRule.rightParts = GrammarRule::RightParts(1, rightPart);
            
            grammar.push_back(newRule);
        }
        else
        {
            grammar.at(pos).rightParts.emplace_back(rightPart);
        }
    }
    
    return grammar;
}

void GrammarParser::ParseLine(const std::string& line, std::vector<std::string>& splitResult) const
{
    boost::algorithm::split_regex(splitResult, line, boost::regex("->|( +)"));
}

long GrammarParser::GetRuleIndex(const std::string& leftGrammarPart, std::vector<GrammarRule>& grammar) const
{
    auto result = std::find_if(grammar.begin(), grammar.end(), [&leftGrammarPart](const GrammarRule& rule) {
        return rule.leftPart == leftGrammarPart;
    });
    return (result != grammar.end()) ? std::distance(grammar.begin(), result) : -1;
}
