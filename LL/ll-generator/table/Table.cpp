#include "Table.hpp"

void Table::AddRow(const TableRow& row)
{
    m_rows.emplace_back(row);
}

size_t Table::RowsCount() const
{
    return m_rows.size();
}

TableRow& Table::GetRowByIndex(size_t index)
{
    return m_rows.at(index);
}

TableRow Table::GetRowByIndex(size_t index) const
{
    return m_rows.at(index);
}
