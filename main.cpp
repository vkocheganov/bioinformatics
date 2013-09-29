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
    ifstream file("/home/maths/Downloads/stepic_dataset.txt");
    // ifstream file("/home/maths/Downloads/Vibrio_cholerae.txt");
     // ifstream file("/home/maths/Downloads/E-coli.txt");
    // ifstream file("/home/maths/Downloads/Thermotoga-petrophila.txt");
    // ifstream file("/home/maths/Downloads/Salmonella_enterica.fasta");
    // ifstream file("/home/maths/Documents/bioinf/rand_gene.txt");
    if (file.is_open())
    {
        string line, pattern("CTTGATCAT"), temp;
        // while( !file.eof() ) {
        //     temp =file.get();
        //     line.append(temp);
        // }
        // cout <<"length = "<< line.length()<<endl;
//        cout<<line;
//        getline(file,line);
//        getline(file,pattern);
//        pattern = "VKLFPWFNGY";
        int d, k;
        // file>>k;
        // cout <<sizeof(int)+1<<endl;
        // file >> k;
        // file>>d;
//        int k= 9,L = 500, t = 3;
        // file>>k;
        // file>>L;
        // file>>t;
        map<string,int> clumps;
        vector<int> positions;
        vector<string> maxPat;
//        pattern_matching(pattern, line, positions);
//        clump_finding(line,k,L,t, clumps);

        // skew_min(line,positions,0);
        // for (int i = 0; i < positions.size(); i++)
        // {
        //     cout << positions[i] << " ";
        // }

        // approximate_pattern_matching(pattern, line,d, positions);
        // cout <<"positions = "<<endl;
        // for (vector<int>::iterator it = positions.begin(); it != positions.end(); it++)
        // {
        //     cout<< *it<<endl;
        // }
        // freq_words_with_mism(line,k,d, maxPat);
        // for (vector<string>::iterator it = maxPat.begin(); it != maxPat.end(); it++)
        // {
        //     cout<<*it<<endl;
        // }
        // string outputString;
        // protein_translation(line, outputString);
        // cout<<outputString<<endl;
        // for (map<string,int>::iterator it = clumps.begin(); it != clumps.end(); it++)
        // {
        //     cout<<it->first<<" ";
        // }
        // cout<<endl;
//        cout<<positions<<endl;
        // vector<string> substrings;
        // peptide_encoding(line,pattern,substrings);
        // cout <<"being "<<endl;
        // for (vector<string>::iterator it = substrings.begin(); it != substrings.end(); it++)
        // {
        //     cout<<*it<<" ";
        // }
        // vector<int> spectrum;
        // generating_theoretical_spectrum(line,spectrum);
        // std::sort (spectrum.begin(), spectrum.end());
        // for (vector<int>::iterator it = spectrum.begin(); it != spectrum.end(); it++)
        // {
        //     cout<< *it<<" ";
        // }
//        int mass = 2000;
        int mass = 8457;
        counting_peptides(mass);
        file.close();
    }
    else
    {
        cout<<"Error opening file"<<endl;
    }
}
