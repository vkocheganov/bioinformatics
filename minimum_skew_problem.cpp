#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void skew_min(string inputString, vector<int>& outputMinPoints, bool needOutputFile)
{
    int min = 0;
    int func = 0;
    ofstream file;

    if (needOutputFile)
    {
        file.open("/home/maths/Documents/bioinf/skew_out.txt");
    }
    
    for (int i = 0; i < inputString.length(); i++)
    {
        if (inputString[i] == 'C' || inputString[i] == 'c')
            func--;
        else if (inputString[i] == 'G' || inputString[i] == 'g')
            func++;
        if (needOutputFile)
        {
            if (i%10000 == 0)
            {
                file<<func<<" ";
            }
        }
        
        if (func == min)
        {
            outputMinPoints.push_back(i);
        }
        if (func < min)
        {
            outputMinPoints.erase(outputMinPoints.begin(), outputMinPoints.end());
            min = func;
            outputMinPoints.push_back(i);
        }
    }
    if (needOutputFile)
        file<<endl;
}
