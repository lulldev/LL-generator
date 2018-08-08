//
//  main.cpp
//  LL
//
//  Created by Ivan Kalagin on 08.08.2018.
//  Copyright © 2018 Ivan Kalagin. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include <boost/algorithm/string/regex.hpp>
#include <boost/optional.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char * argv[]) {
    
    if (argc != 2) {
        cout << "Invalid arguments count\n"
        << "Usage: program <input file>\n";
        return 1;
    }
    
    ifstream inputFile(argv[1]);
    
    if (!inputFile.is_open()) {
        cout << "Error reading file " << argv[1] << endl;
        return 1;
    }
    
    return 0;
}
