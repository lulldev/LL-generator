#pragma once

#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>

#include "../table/Table.hpp"


class GrammarSlider
{
public:
    void RunSlider(const std::string& str, Table& table);
};
