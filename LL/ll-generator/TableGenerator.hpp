#pragma once

#include <boost/algorithm/string/regex.hpp>
#include <boost/optional.hpp>
#include <boost/regex.hpp>
#include <iomanip>
#include <iostream>

#include "TableGenerator.hpp"
#include "grammar/GrammarParser.hpp"
#include "table/Table.hpp"


class TableGenerator
{
public:
    void Generate(const std::vector<GrammarRule>& grammar);
    void PrintTable();
    
private:
    Table m_table;
    std::vector<std::pair<std::string, GrammarRule::RightPart::Items>> m_unresolvedNextIds;
    std::map<std::string, std::vector<size_t>> m_tableReferences;
    std::map<std::string, GrammarRule::RightPart::Guides> m_guidesSet;

    void Initialize(const std::vector<GrammarRule>& grammar);
    void Fill();
    
    void AddReferences(const std::string& leftPart, size_t currentRowNumber);
    void AddGuides(const std::string& leftPart, const GrammarRule::RightPart::Items& items, const GrammarRule::RightPart::Guides& guides);
    
    bool IsTerminal(const std::string& symbol);
    void ProcessTerminal(TableRow& row, const std::string& item, const GrammarRule::RightPart::Items& items, size_t currentRowNumber);
    void ProcessNonTerminal(TableRow& row, const std::string& item, const GrammarRule::RightPart::Items& items, size_t currentRowNumber);
};
