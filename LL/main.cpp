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
#include <stack>

#include "ll-generator/grammar/GrammarParser.hpp"
#include "ll-generator/table/Table.hpp"
#include "ll-generator/slider/GrammarSlider.hpp"
#include "ll-generator/TableGenerator.hpp"


using namespace std;

int main(int argc, char * argv[]) {
    
    ifstream inputFile("/Users/lulldev/Documents/GitHub/LL-generator/LL/input.txt");
    
    GrammarParser grammarParser;
    auto grammar = grammarParser.Parse(inputFile);
    TableGenerator tableGenerator;
    tableGenerator.Generate(grammar);
    tableGenerator.PrintTable();
    
    string checkingString;
    cout << "\nEnter something for slider check:\n";
    getline(cin, checkingString);
    cout << endl;
    Table table = tableGenerator.GetTable();
    GrammarSlider slider;
    slider.RunSlider(checkingString, table);
    
    return 0;
}


