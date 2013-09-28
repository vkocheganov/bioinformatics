#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <string.h>

using namespace std;

void clump_finding(string inputString, int inputK, int inputL, int inputT, map<string,int>& outputClumps)
{
    string cur_line;
        
    char *cur_line_c;
    char *line_c = new char[inputString.length() + 1];
    inputString.copy(line_c,inputString.length());
    line_c[inputString.length()] = '\0';
    char *buffer;
    map <string,int> words;
    cur_line_c = line_c;
    char prev_letter = '\0';

    for (int i = 0; i < inputL - inputK + 1; i++)
    {
        buffer = cur_line_c + i;
        prev_letter = buffer[inputK];
        buffer[inputK] = '\0';
        if (words.count(buffer) == 0)
        {
            words[buffer] = 1;
        }
        else
        {
            words[buffer] += 1;
        }
        buffer[inputK] = prev_letter;
    }
    std::map<string,int>::iterator it = words.begin();
    for (it = words.begin(); it != words.end(); ++it)
    {
        if (it->second >= inputT)
        {
            if (outputClumps.count(it->first) == 0)
            {
                outputClumps[it->first] = it->second;
            }
        }
    }

    for (unsigned j = 1; j < inputString.length() - inputL + 1; j++)
    {
        cur_line_c = line_c + j;
        buffer = cur_line_c - 1;
        prev_letter = buffer[inputK];
        buffer[inputK] = '\0';
        it = words.find(buffer);
        if (it->second == 1)
        {
            words.erase(it);
        }
        else
        {
            it->second -= 1;
        }

        if (it->second >= inputT)
        {
            if (outputClumps.count(it->first) == 0)
                outputClumps[it->first] = it->second;
        }

        buffer[inputK] = prev_letter;
        buffer = cur_line_c + inputL-inputK;
        prev_letter = buffer[inputK];
              
        buffer[inputK] = '\0';
        it = words.find(buffer);
        if (it == words.end())
        {
            words[buffer] = 1;
        }
        else
        {
            it->second += 1;
        }

        if (it->second >= inputT)
        {
            outputClumps[buffer] = words[buffer];
        }
        buffer[inputK] = prev_letter;
    }
    delete []line_c;
}
