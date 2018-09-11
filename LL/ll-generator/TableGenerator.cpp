#include "TableGenerator.hpp"

using namespace std;

const std::string EMPTY_SYMBOL = "<>";
const std::string EOF_SYMBOL = "#";


void TableGenerator::Generate(const std::vector<GrammarRule>& grammar)
{
    Initialize(grammar);
    Fill();
}

void TableGenerator::PrintTable() {
    cout << setw(4) << left << "id"
    << "| "
    << setw(30) << "Guide set"
    << "| "
    << setw(7) << "Next"
    << "| "
    << setw(9) << "Is shift"
    << "| "
    << setw(11) << "Is id in Stack"
    << "| "
    << setw(9) << "Error"
    << "| "
    << setw(7) << "End"
    << "| " << endl;
    
    cout << string(90, '-') << endl;
    
    for (size_t i = 0; i < m_table.RowsCount(); ++i)
    {
        TableRow currentRow = m_table.GetRowByIndex(i);
        string set = "{ ";
        size_t counter = 0;
        for (const auto& reference : currentRow.referencingSet)
        {
            set.append(reference).append(" ");
            ++counter;
        }
        set.append("}");
        
        cout << setw(4) << left << (" " + to_string(i)) << "| "
        << setw(30) << set << "| "
        << setw(7) << (currentRow.next == boost::none ? "-" : to_string(currentRow.next.get())) << "| "
        << setw(9) << (currentRow.isShift ? "+" : "-") << "| "
        << setw(14) << (currentRow.idAtStack == boost::none ? "-" : to_string(currentRow.idAtStack.get())) << "| "
        << setw(9) << (currentRow.isError ? "+" : "-") << "| "
        << setw(7) << (currentRow.isEnd ? "+" : "-") << "| "
        << endl;
    }
}

void TableGenerator::Initialize(const std::vector<GrammarRule>& grammar)
{
    size_t currentRowNumber = 0;
    for (auto& rule : grammar)
    {
        const GrammarRule::RightParts& rightParts = rule.rightParts;
        
        for (const auto& part : rightParts)
        {
            TableRow row;
            
            row.referencingSet = part.guides;
            if (&part != &rightParts.back())
            {
                row.isError = false;
            }
            
            m_unresolvedNextIds.emplace_back(rule.leftPart, part.items);
            AddReferences(rule.leftPart, currentRowNumber);
            AddGuides(rule.leftPart, part.items, part.guides);
            
            m_table.AddRow(row);
            ++currentRowNumber;
        }
    }
}

Table TableGenerator::GetTable() {
    return m_table;
}

void TableGenerator::Fill()
{
    size_t nextUnresolvedIndex = 0;
    size_t currentRowNumber = m_table.RowsCount();
    
    for (const auto& unresolvedNextId : m_unresolvedNextIds)
    {
        m_table.GetRowByIndex(nextUnresolvedIndex).next = currentRowNumber;
        
        if (unresolvedNextId.second.empty())
        {
            ++currentRowNumber;
            TableRow row;
            row.referencingSet = m_guidesSet.at(EMPTY_SYMBOL + unresolvedNextId.first);
            m_table.AddRow(row);
        }
        
        for (const auto& item : unresolvedNextId.second)
        {
            ++currentRowNumber;
            TableRow row;
            
            if (IsTerminal(item))
            {
                ProcessTerminal(row, item, unresolvedNextId.second, currentRowNumber);
            }
            else
            {
                ProcessNonTerminal(row, item, unresolvedNextId.second, currentRowNumber);
            }
            
            m_table.AddRow(row);
        }
        
        ++nextUnresolvedIndex;
    }
}

bool TableGenerator::IsTerminal(const std::string& symbol)
{
    if (symbol.empty())
    {
        return false;
    }
    
    return symbol.front() != '<' && symbol.back() != '>';
}

void TableGenerator::ProcessTerminal(TableRow& row, const std::string& item, const GrammarRule::RightPart::Items& items, size_t currentRowNumber)
{
    row.referencingSet = GrammarRule::RightPart::Guides({ item });
    
    if (&item != &items.back())
    {
        row.next = currentRowNumber;
    }
    
    if (item == EOF_SYMBOL)
    {
        row.isEnd = true;
    }
    else
    {
        row.isShift = true;
    }
}

void TableGenerator::ProcessNonTerminal(TableRow& row, const std::string& item, const GrammarRule::RightPart::Items& items, size_t currentRowNumber)
{
    row.referencingSet = m_guidesSet.at(item);
    
    row.next = m_tableReferences.at(item).front();
    
    if (&item != &items.back())
    {
        row.idAtStack = currentRowNumber;
    }
}

void TableGenerator::AddReferences(const std::string& leftPart, size_t currentRowNumber)
{
    auto reference = m_tableReferences.find(leftPart);
    if (reference == m_tableReferences.end())
    {
        m_tableReferences.emplace(leftPart, std::vector<size_t>(1, currentRowNumber));
    }
    else
    {
        reference->second.emplace_back(currentRowNumber);
    }
}

void TableGenerator::AddGuides(const std::string& leftPart, const GrammarRule::RightPart::Items& items,
                               const GrammarRule::RightPart::Guides& guides)
{
    auto guidesPos = m_guidesSet.find(leftPart);
    if (guidesPos == m_guidesSet.end())
    {
        m_guidesSet.emplace(leftPart, guides);
    }
    else
    {
        guidesPos->second.insert(guides.cbegin(), guides.cend());
    }
    
    if (items.empty())
    {
        auto guidesPos1 = m_guidesSet.find(EMPTY_SYMBOL + leftPart);
        if (guidesPos1 == m_guidesSet.end())
        {
            m_guidesSet.emplace(EMPTY_SYMBOL + leftPart, guides);
        }
        else
        {
            guidesPos1->second.insert(guides.cbegin(), guides.cend());
        }
    }
}
