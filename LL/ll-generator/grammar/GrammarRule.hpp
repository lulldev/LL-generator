#pragma once

#include <iostream>
#include <unordered_set>
#include <vector>

struct GrammarRule
{
    struct RightPart
    {
        using Items = std::vector<std::string>;
        using Guides = std::unordered_set<std::string>;
        
        Items items;
        Guides guides;
    };
    
    using RightParts = std::vector<RightPart>;
    
    std::string leftPart;
    RightParts rightParts;
};
