#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include "main.h"
using namespace std;

char nucl[] = { 'A', 'G', 'T', 'C'};
char nucl_rev[] = {'T', 'C', 'A', 'G'};

void freq_words_with_mism(string inputString, int inputK, int inputD, vector<string>& outputMaxPat)
{
    int errcount = 0;
    map<string,int> pattern_ar;
    string temp;
    string comp_temp;

    vector<int> comb;
    generate_comb(inputK,inputD,comb);

    for (int i = 0; i < inputString.length() - inputK + 1; i++)
    {
        string pattern = string(inputString, i, inputK);
        string comp_pattern = pattern;
        reverse_complement(pattern,comp_pattern);
        set<string> temp_set;
        set<string> temp_set_comp;
        for (vector<int>::iterator it = comb.begin(); it != comb.end(); it++ )
        {
            for (unsigned l = 0; l < 1<<(2*inputD); l++)
            {
                temp = pattern;
                comp_temp = comp_pattern;
                errcount = 0;
                for (int j = 0; j < inputK;j++)
                {
                    if (*it & (1<<j))
                    {
                        temp[j] = comp_temp[j] = nucl[((3 <<(2*errcount)) & l) >>(2*errcount)];
                        errcount++;
                    }
                }
                temp_set.insert(temp);
                temp_set_comp.insert(comp_temp);
            }
        }
            
        set<string>::iterator it_set = temp_set.begin();
        for (it_set = temp_set.begin(); it_set != temp_set.end(); it_set++)
        {
            if(pattern_ar.count(*it_set) == 0)
            {
                pattern_ar.insert(pair<string,int>(*it_set,1));
            }
            else
            {
                pattern_ar[*it_set]++;
            }
        }
            
        for (it_set = temp_set_comp.begin(); it_set != temp_set_comp.end(); it_set++)
        {
            if(pattern_ar.count(*it_set) == 0)
            {
                pattern_ar.insert(pair<string,int>(*it_set,1));
            }
            else
            {
                pattern_ar[*it_set]++;
            }
        }
    }
    map<string,int>::iterator it1= pattern_ar.begin();
    int max = 0;
    for (it1 = pattern_ar.begin(); it1 != pattern_ar.end(); it1++)
    {
        if( it1->second > max)
            max = it1->second;
    }
    for (it1 = pattern_ar.begin(); it1 != pattern_ar.end(); it1++)
    {
        if( it1->second == max)
            outputMaxPat.push_back(it1->first);
    }        
}
