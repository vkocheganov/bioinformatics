#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

void freq_words(string inputString, int inputPatternSize, map<string,int>& OutputKMers)
{
    char *buffer = new char[inputPatternSize+1];
   map<string,int> words;
    for (int i = 0; i < inputString.length() - inputPatternSize + 1; i++)
    {
        inputString.copy(buffer,inputPatternSize,i);
        buffer[inputPatternSize] = '\0';
//            cout<< "trying: "<< buffer<< endl;
        if (words.count(buffer) == 0)
        {
            words.insert(std::pair<string,int>(buffer,1));
        }
        else
        {
            words[buffer] += 1;
        }
    }
    std::map<string,int>::iterator it = words.begin();
    int max = 0;
    for (it = words.begin(); it != words.end(); ++it)
    {
        if (it->second >= max)
            max = it->second;
//            cout << it->first << " => " << it->second << endl;
    }
    for (it = words.begin(); it != words.end(); ++it)
    {
        if (it->second == max)
        {
            OutputKMers.insert(*it);
            cout << it->first << " => "<<it->second << endl;
        }
        
    }
}

