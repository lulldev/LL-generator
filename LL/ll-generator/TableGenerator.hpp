#pragma once
#include "TableGenerator.hpp"
#include "grammar/Grammar.hpp"
#include "table/Table.hpp"

#include <boost/algorithm/string/regex.hpp>
#include <boost/optional.hpp>
#include <boost/regex.hpp>


class TableGenerator
{
public:
    void Generate(const std::vector<Rule>& grammar);
    Table Get() const;
    
private:
    void Initialize(const std::vector<Rule>& grammar);
    void Fill();
    
    void AddReferences(const std::string& leftPart, size_t currentRowNumber);
    void AddGuides(const std::string& leftPart, const Rule::RightPart::Items& items, const Rule::RightPart::Guides& guides);
    
    bool IsTerminal(const std::string& symbol);
    void ProcessTerminal(TableRow& row, const std::string& item, const Rule::RightPart::Items& items, size_t currentRowNumber);
    void ProcessNonTerminal(TableRow& row, const std::string& item, const Rule::RightPart::Items& items, size_t currentRowNumber);
    
    Table m_table;
    
    std::vector<std::pair<std::string, Rule::RightPart::Items>> m_unresolvedNextIds;
    std::map<std::string, std::vector<size_t>> m_tableReferences;
    std::map<std::string, Rule::RightPart::Guides> m_guidesSet;
};
