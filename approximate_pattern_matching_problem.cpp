#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const char nucl[] = {'A', 'C', 'G', 'T'};

void generate_comb(int n, int k, vector<int>& combinations)
{
    unsigned int singleCombination = 0;
    int cur_ind;
    unsigned  mask = 1;
    int count = 0;

    for (int i = 0; i < k; i ++)
    {
        singleCombination |= mask;
        cout <<mask<<endl;
        mask<<=1;
    }
        
    while (1)
    {
        combinations.push_back(singleCombination);
        count++;
        cur_ind = n - 1;
        while ( singleCombination & (1<<cur_ind))
        {
            singleCombination = singleCombination & ~(1<<cur_ind);
            cur_ind--;
        }
        
        if (cur_ind < n - k)
            break;
        int pos = cur_ind;
        while ((~singleCombination) & (1<<pos))
        {
            pos--;
        }
        singleCombination &= ~(1<<pos);
        for (int i = pos + 1; i < pos + 1 + n - cur_ind; i++)
            singleCombination |= 1<<i;
    }
}

void approximate_pattern_matching(string inputPattern, string inputString, int inputD, vector<int>& outputPoss)
{
    if (inputPattern.length() > 15)
    {
        cout<<"Error: pattern should be of length <= 15"<<endl;
        return ;
    }

    vector<int> comb;
    generate_comb(inputPattern.length(),inputD,comb);
    string temp;
    set<string> pattern_ar;
    int errcount;
    
    for (vector<int>::iterator it = comb.begin(); it != comb.end(); it++ )
    {
        for (unsigned i = 0; i <(unsigned) 1<<(2*inputD); i++)
        {
            temp = inputPattern;
            errcount = 0;
            for (unsigned j = 0; j < inputPattern.length();j++)
            {
                if (*it & (1<<j))
                {
                    temp[j] = nucl[((3 <<(2*errcount)) & i) >>(2*errcount)];
                    errcount++;
                }
            }
            pattern_ar.insert(temp);
        }
    }
    set <string>::iterator it = pattern_ar.begin();
    for (unsigned i = 0; i < inputString.length() - inputPattern.length() + 1; i++)
    {
        for (it = pattern_ar.begin(); it !=  pattern_ar.end(); it++)
        {
            temp = *it;
            if (inputString.compare(i,temp.length(),temp) == 0)
            {
                cout<<i<<endl;
                outputPoss.push_back(i);
            }

        }
    }
}    


// void approximate_pattern_matching1(string inputPattern, string inputString, int inputD, vector<int>& outputPoss)
// {
//     vector<int> comb;
//     generate_comb(10,7,comb);
//     int* indices = new int[inputD];
//     int* indices_1 = new int[inputD];
//     string temp;
//     set<string> pattern_ar;
//     for (int j = 0; j < inputD; j++)
//     {
//         indices[j] = j;
//     }

//     while (1)
//     {
//         unsigned cur_ind = inputD - 1;
//         for (int j = 0; j < inputD; j++)
//         {
//             indices_1[j] = 0;
//         }

//         while (1)
//         {
//             temp = inputPattern;
//             for (int i = 0; i <inputD;i++)
//             {
//                 temp[indices[i]] = nucl[indices_1[i]];
//             }
//             pattern_ar.insert(temp);
//             cur_ind = inputD - 1;
//             while( cur_ind >=0 && (indices_1[cur_ind] == 3) )
//             {
//                 cur_ind--;
//             }
//             if (cur_ind < 0)
//                 break;
//             indices_1[cur_ind]++;
//             cur_ind++;
//             for (int i = cur_ind; i < inputD; i++)
//                 indices_1[i] = 0;
//         }
            
//         cur_ind = inputD - 1;
//         while ( (indices[cur_ind] == inputPattern.length() -1 + cur_ind - inputD + 1 ) && (cur_ind >= 0))
//         {
//             cur_ind--;
//         }
//         if (cur_ind < 0)
//             break;
//         indices[cur_ind]++;
//         cur_ind++;
//         while (cur_ind < inputD)
//         {
//             indices[cur_ind] = indices[cur_ind - 1] + 1;
//             cur_ind++;
//         }
//     }
//     set <string,int>::iterator it = pattern_ar.begin();
//     cout << "pat count = " << pattern_ar.size()<<endl;
//     for (int i = 0; i < inputString.length() - inputPattern.length() + 1; i++)
//     {
//         for (it = pattern_ar.begin(); it !=  pattern_ar.end(); it++)
//         {
//             temp = *it;
//             if (inputString.compare(i,temp.length(),temp) == 0)
//             {
//                 outputPoss.push_back(i);
//             }

//         }
//     }
// }    
