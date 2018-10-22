#include "GrammarSlider.hpp"

using namespace std;

void GrammarSlider::RunSlider(const std::string &str, Table &table)
{
    std::istringstream strm(str);
    std::stack<size_t> stack;
    std::string lex;
    bool isError = false;
    size_t index = 0u;
    
    strm >> lex;
    std::cout << lex << std::endl;
    
    while (true)
    {
        TableRow& state = table.GetRowByIndex(index);
        
        if (state.referencingSet.find(lex) == state.referencingSet.end())
        {
            if (!state.isError)
            {
                ++index;
                continue;
            }
            else
            {
                isError = true;
                break;
            }
        }
        
        if (state.isEnd)
        {
            assert(stack.empty());
            isError = false;
            break;
        }
        
        if (state.idAtStack != boost::none)
        {
            stack.push(index + 1);
        }
        
        if (state.isShift)
        {
            strm >> lex;
        }
        
        if (state.next != boost::none)
        {
            index = *state.next;
        }
        else
        {
            assert(!stack.empty());
            index = stack.top();
            stack.pop();
        }
    }
    
    cout << std::boolalpha << !isError << endl;
}
