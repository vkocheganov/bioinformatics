#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void pattern_matching(string inputPattern, string inputString, vector<int>& outputPoss)
{
    for (int i = 0; i < inputString.length() - inputPattern.length() + 1; i++)
    {
        if (inputString.compare(i,inputPattern.length(),inputPattern) == 0)
        {
            outputPoss.push_back(i);
        }
    }
}
