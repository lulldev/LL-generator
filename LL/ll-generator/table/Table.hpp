#pragma once

#include "TableRow.h"

class Table
{
public:
    void AddRow(const TableRow&);
    size_t RowsCount() const;
    TableRow& GetRowByIndex(size_t index);
    TableRow GetRowByIndex(size_t index) const;
    
private:
    std::vector<TableRow> m_rows;
};
