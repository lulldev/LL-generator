//
//  main.cpp
//  LL
//
//  Created by Ivan Kalagin on 08.08.2018.
//  Copyright © 2018 Ivan Kalagin. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iomanip>

#include "Grammar.hpp"
#include "Table.hpp"
#include "TableGenerator.hpp"

using namespace std;

void PrintTable(const CTable& table);

int main(int argc, char * argv[]) {
    
//    if (argc != 2) {
//        cout << "Invalid arguments count\n"
//        << "Usage: program <input file>\n";
//        return 1;
//    }
    
    ifstream inputFile("/Users/lulldev/Documents/GitHub/LL-generator/LL/input.txt");
    
//    if (!inputFile.is_open()) {
//        cout << "Error reading file " << argv[1] << endl;
//        return 1;
//    }
    
    CGrammar grammar;
    grammar.ReadAndParseGrammar(inputFile);
    
    CTableGenerator tableGenerator;
    tableGenerator.Generate(grammar.GetGrammar());
    
    CTable table = tableGenerator.Get();
    PrintTable(table);
    
    return 0;
}

void PrintTable(const CTable& table)
{
    cout << setw(4) << left << "id"
    << "| "
    << setw(30) << "guides set"
    << "| "
    << setw(7) << "next"
    << "| "
    << setw(9) << "isShift"
    << "| "
    << setw(11) << "idAtStack"
    << "| "
    << setw(9) << "isError"
    << "| "
    << setw(7) << "isEnd"
    << "| " << endl;
    
    cout << string(90, '-') << endl;
    
    for (size_t i = 0; i < table.Size(); ++i)
    {
        TableRow currentRow = table.Get(i);
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
        << setw(11) << (currentRow.idAtStack == boost::none ? "-" : to_string(currentRow.idAtStack.get())) << "| "
        << setw(9) << (currentRow.isError ? "+" : "-") << "| "
        << setw(7) << (currentRow.isEnd ? "+" : "-") << "| "
        << endl;
    }
}
