#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "main.h"

int main ()
{
//    ifstream file("/home/maths/Downloads/stepic_dataset.txt");
    ifstream file("/home/maths/Downloads/Salmonella_enterica.fasta");
    if (file.is_open())
    {
        string line, pattern("CTTGATCAT"), temp;
        vector<string> lines;
        int k, d, t;
        string DNA;
        // getline(file, DNA);
        // file >> k;
        // vector<map<char,double> > profile;
        // map<char,double> tempMap;
        // vector<char> alphabet;
        // char tempChar;
        
        // file>>tempChar;
        // alphabet.push_back(tempChar);
        // file>>tempChar;
        // alphabet.push_back(tempChar);
        // file>>tempChar;
        // alphabet.push_back(tempChar);
        // file>>tempChar;
        // alphabet.push_back(tempChar);
        // for (int i = 0; i < k; i++)
        // {
        //     tempMap.clear();
        //     file >> tempMap[alphabet[0]];
        //     file >> tempMap[alphabet[1]];
        //     file >> tempMap[alphabet[2]];
        //     file >> tempMap[alphabet[3]];
        //     profile.push_back(tempMap);
        // }
        
        // cout<< "k = "<<k<<endl;
//        file >> d;
//        cout <<"k = "<<k<<" d = "<<d<<endl;
        // file >> k;
        // file >> t;
        // for (int i = 0; i < t; i++)
        // {
        string total_line;
        while( !file.eof() ) {
            getline(file,line);
            if (line.length() > 1)
            {
                total_line.append(line);
                // lines.push_back(line);
                // cout << line<<endl;
            }
        }
        cout<<"size = "<<total_line.length()<<endl;
        vector<int> minponts;
        skew_min(total_line, minponts,1);
        cout<<"min_points.size = "<<minponts.size()<<endl;
        int N = 500;
        vector<string> maxPat;
        for (int i = 0; i < minponts.size(); i++)
        {
            string curDNAWindow(total_line, minponts[i]-100, N);
            cout<<"minpoints[i] = "<<minponts[i]<<" "<<curDNAWindow<<endl;
            maxPat.clear();
            freq_words_with_mism(curDNAWindow, 9, 2, maxPat);
            cout <<"i = "<< i<<" maxPat.size() = "<< maxPat.size()<<endl;
            for (int j = 0; j < maxPat.size(); j++)
            {
                cout<<maxPat[j]<<" "<<minponts[i] + curDNAWindow.find("AAAAG")<<endl;
            }
            
        }
        
        // vector<int> random_ind;
        // for (int i = 0; i < t; i++)
        // {
        //     int temp_ind;
        //     file >> temp_ind;
        //     random_ind.push_back(temp_ind);
        // }
        
        // cout<<"k = "<<k<<" t = "<<t<<" lines.size() = "<<lines.size()<<endl;
        // RandomizedMotifSearch(lines, k, t, random_ind);
        // vector< map<char, double> > tempM;
        // GreedyMotifSearch(lines,  k, t);
//        score_motif(lines);
//        cout<<"best pattern = "<<MedianString(lines, k)<<endl;
//        cout<<"best pattern = "<<ProfileMostProbableKMerProblem(DNA, k, profile)<<endl;
        cout<<"in main\n";
        file.close();
    }
    else
    {
        cout<<"Error opening file"<<endl;
    }
    return 0;
}
