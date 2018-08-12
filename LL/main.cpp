//
//  main.cpp
//  LL
//
//  Created by Ivan Kalagin on 02.08.2018.
//  Copyright © 2018 Ivan Kalagin. All rights reserved.
//

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "ll-generator/grammar/GrammarParser.hpp"
#include "ll-generator/table/Table.hpp"
#include "ll-generator/TableGenerator.hpp"

using namespace std;


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
    
    GrammarParser grammarParser;
    auto grammar = grammarParser.Parse(inputFile);
    TableGenerator tableGenerator;
    tableGenerator.Generate(grammar);
    tableGenerator.PrintTable();
    
    return 0;
}
