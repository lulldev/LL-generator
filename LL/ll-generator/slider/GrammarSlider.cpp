#include "GrammarSlider.hpp"

using namespace std;

void GrammarSlider::RunSlider(const std::string &str, Table &table)
{
    stringstream strm(str);
    
    string elem;
    size_t index = 0;
    bool isError = false;
    bool isEnd = false;
    stack<size_t> stack;
    
    while (strm >> elem)
    {
        cout << "search for " << elem << endl;
        
        TableRow& row = table.GetRowByIndex(index);
        
        do
        {
            row = table.GetRowByIndex(index);
            
            cout << index << " ";
            
            if (row.isEnd)
            {
                if (elem == "#")
                {
                    isEnd = true;
                    break;
                }
                else
                {
                    if (!stack.empty())
                    {
                        index = stack.top();
                        stack.pop();
                        continue;
                    }
                    else
                    {
                        isError = true;
                        break;
                    }
                }
            }
            
            if (row.referencingSet.find(elem) != row.referencingSet.end())
            {
                if (row.idAtStack != boost::none)
                {
                    stack.push(row.idAtStack.get());
                }
                
                if (row.next != boost::none)
                {
                    index = row.next.get();
                }
                else
                {
                    if (!stack.empty())
                    {
                        index = stack.top();
                        stack.pop();
                    }
                    else
                    {
                        isError = true;
                        break;
                    }
                }
            }
            else
            {
                if (!row.isError)
                {
                    ++index;
                }
                else
                {
                    isError = true;
                    break;
                }
            }
        } while (!row.isShift);
        
        cout << endl;
        
        if (isEnd || isError)
        {
            break;
        }
    }
    
    if (isError)
    {
        cout << "Error" << endl;
    }
    
    if (isEnd)
    {
        cout << "End" << endl;
    }
}
