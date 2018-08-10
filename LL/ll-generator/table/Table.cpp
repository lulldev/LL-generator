#include <stdio.h>
#include "Table.hpp"

void Table::Add(const TableRow& row)
{
    m_rows.emplace_back(row);
}

size_t Table::Size() const
{
    return m_rows.size();
}

TableRow& Table::Get(size_t index)
{
    return m_rows.at(index);
}

TableRow Table::Get(size_t index) const
{
    return m_rows.at(index);
}
