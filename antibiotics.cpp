#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <set>
#include "main.h"

using namespace std;

void dna_rna_transcribe(string inputString, string& outputString)
{
    outputString.clear();
    for (unsigned i = 0; i < inputString.length(); i++)
    {
        if (inputString[i] == 'T')
        {
            outputString.append(1,'U');
        }
        else
        {
            outputString.append(1, inputString[i]);
        }
    }
}

void rna_amino_translate(string inputString, string& outputString)
{
    outputString = "";
    if (inputString.length() % 3 != 0)
    {
        cout <<"Error: length should devide 3\n";
        exit(1);
    }
    char buf[4];
    map<string,char> amino_map;
    amino_map["AUU"] = 'I';
    amino_map["AUC"] = 'I';
    amino_map["AUA"] = 'I';
    amino_map["AUG"] = 'M';
    amino_map["ACU"] = 'T';
    amino_map["ACC"] = 'T';
    amino_map["ACA"] = 'T';
    amino_map["ACG"] = 'T';
    amino_map["AAU"] = 'N';
    amino_map["AAC"] = 'N';
    amino_map["AAA"] = 'K';
    amino_map["AAG"] = 'K';
    amino_map["AGU"] = 'S';
    amino_map["AGC"] = 'S';
    amino_map["AGA"] = 'R';
    amino_map["AGG"] = 'R';

    amino_map["CUU"] = 'L';
    amino_map["CUC"] = 'L';
    amino_map["CUA"] = 'L';
    amino_map["CUG"] = 'L';
    amino_map["CCU"] = 'P';
    amino_map["CCC"] = 'P';
    amino_map["CCA"] = 'P';
    amino_map["CCG"] = 'P';
    amino_map["CAU"] = 'H';
    amino_map["CAC"] = 'H';
    amino_map["CAA"] = 'Q';
    amino_map["CAG"] = 'Q';
    amino_map["CGU"] = 'R';
    amino_map["CGC"] = 'R';
    amino_map["CGA"] = 'R';
    amino_map["CGG"] = 'R';

    amino_map["GUU"] = 'V';
    amino_map["GUC"] = 'V';
    amino_map["GUA"] = 'V';
    amino_map["GUG"] = 'V';
    amino_map["GCU"] = 'A';
    amino_map["GCC"] = 'A';
    amino_map["GCA"] = 'A';
    amino_map["GCG"] = 'A';
    amino_map["GAU"] = 'D';
    amino_map["GAC"] = 'D';
    amino_map["GAA"] = 'E';
    amino_map["GAG"] = 'E';
    amino_map["GGU"] = 'G';
    amino_map["GGC"] = 'G';
    amino_map["GGA"] = 'G';
    amino_map["GGG"] = 'G';

    amino_map["UUU"] = 'F';
    amino_map["UUC"] = 'F';
    amino_map["UUA"] = 'L';
    amino_map["UUG"] = 'L';
    amino_map["UCU"] = 'S';
    amino_map["UCC"] = 'S';
    amino_map["UCA"] = 'S';
    amino_map["UCG"] = 'S';
    amino_map["UAU"] = 'Y';
    amino_map["UAC"] = 'Y';
    amino_map["UAA"] = '*';
    amino_map["UAG"] = '*';
    amino_map["UGU"] = 'C';
    amino_map["UGC"] = 'C';
    amino_map["UGA"] = '*';
    amino_map["UGG"] = 'W';
    for (unsigned i = 0; i < inputString.length(); i +=3)
    {
        inputString.copy(buf, 3, i);
        buf[3] = '\0';
        if (amino_map[buf] != '*')
            outputString.append(1,amino_map[buf]);
    }
}

void protein_translation(string inputString, string& outputString)
{
    string temp;
    dna_rna_transcribe(inputString,temp);
//    cout <<temp<<endl;
    rna_amino_translate(temp, outputString);
}

void peptide_encoding(string inputDNA, string inputAmino, vector<string>& outputSubstrings)
{
//    cout<<inputDNA<<endl;
    string peptide_from_DNA("");
    string tempDNA(""), tempDNArev("");
    for (unsigned i = 0; i < inputDNA.length() - inputAmino.length()*3 + 1; i++)
    {
        if (i % 100000 == 0)
            cout <<"i = "<<i<<endl;
        tempDNA = string(inputDNA, i, inputAmino.length() * 3);
        protein_translation(tempDNA, peptide_from_DNA);
        if (peptide_from_DNA.compare(inputAmino) == 0)
        {
            outputSubstrings.push_back(tempDNA);
//            cout <<tempDNA<<" "<<peptide_from_DNA<<endl;
            continue;
        }
        
        reverse_complement(tempDNA, tempDNArev);
        peptide_from_DNA  = "";
        protein_translation(tempDNArev, peptide_from_DNA);
        if (peptide_from_DNA.compare(inputAmino) == 0)
        {
            outputSubstrings.push_back(tempDNA);
//            cout <<tempDNA<<" "<<peptide_from_DNA<<endl;
//            cout <<tempDNA<<endl;
        }
    }
}

void mass_map(map<char,int>& masses)
{
    masses['G'] = 57;
    masses['A'] = 71;
    masses['S'] = 87;
    masses['P'] = 97;
    masses['V'] = 99;
    masses['T'] = 101;
    masses['C'] = 103;
    masses['I'] = 113;
    masses['L'] = 113;
    masses['N'] = 114;
    masses['D'] = 115;
    masses['K'] = 128;
    masses['Q'] = 128;
    masses['E'] = 129;
    masses['M'] = 131;
    masses['H'] = 137;
    masses['F'] = 147;
    masses['R'] = 156;
    masses['Y'] = 163;
    masses['W'] = 186;
}

void generating_theoretical_spectrum(string inputPeptide, vector<int> &outputSpectrum)
{
    string temp;
    map<char,int> masses;
    mass_map(masses);
    outputSpectrum.push_back(0);
    for (unsigned curlength = 1; curlength < inputPeptide.length(); curlength++)
    {
        for (unsigned curstart = 0; curstart < inputPeptide.length(); curstart++)
        {
            int sum = 0;
            temp = "";
            unsigned curpostemp = curstart;
            for (unsigned curpos = 0; curpos < curlength; curpos++)
            {
                sum += masses[inputPeptide[curpostemp]];
                if (curpostemp == inputPeptide.length() - 1)
                    curpostemp = 0;
                else
                    curpostemp++;
            }
            outputSpectrum.push_back(sum);
//            cout <<"sum = "<< sum<<endl;
        }
    }
    int sum = 0;
    temp = "";
    unsigned curpostemp = 0;
    unsigned curlength = inputPeptide.length();
    for (unsigned curpos = 0; curpos < curlength; curpos++)
    {
        sum += masses[inputPeptide[curpostemp]];
        if (curpostemp == inputPeptide.length() - 1)
            curpostemp = 0;
        else
            curpostemp++;
    }
    outputSpectrum.push_back(sum);
//            cout <<"sum = "<< sum<<endl;

}

#include <stdio.h>
#include <time.h>
int factorial(int n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}
#include <boost/cstdint.hpp>
boost::uint64_t Combinations(unsigned int n, unsigned int r)
{
        if (r > n)
                return 0;

        /** We can use Pascal's triange to determine the amount
          * of combinations. To calculate a single line:
          *
          * v(r) = (n - r) / r
          *
          * Since the triangle is symmetrical, we only need to calculate
          * until r -column.
          */

        boost::uint64_t v = n--;

        for (unsigned int i = 2; i < r + 1; ++i, --n)
                v = v * n / i;

        return v;
}
int counting_peptides_sub(int inputMass, vector<int>& masses, map<int, int>& cur_ar, int prev_mas)
{
    static int count = 0;
    static clock_t t = clock();
//    cout<<"combinations = "<<Combinations(10,8)<<endl;
//    cout<<"Entering mass "<<inputMass<<endl;
    for (int i = prev_mas; i < masses.size(); i++)
    {
        if (inputMass - masses[i] > 0)
        {
            bool found;
            if (cur_ar.count(masses[i]) == 0)
            {
                cur_ar[masses[i]] = 1;
                found = false;
            }
            else
            {
                cur_ar[masses[i]]++;
                found = true;
            }
            counting_peptides_sub(inputMass - masses[i], masses, cur_ar, i);
            (found ? cur_ar[masses[i]]-- : cur_ar.erase(masses[i]));
//            cur_ar.pop_back();
        }
        else if (inputMass - masses[i] == 0)
        {
//            cur_ar.push_back(masses[i]);
            bool found;
            if (cur_ar.count(masses[i]) == 0)
            {
                cur_ar[masses[i]] = 1;
                found = false;
            }
            else
            {
                cur_ar[masses[i]]++;
                found = true;
            }

//             if (count % 1000000 == 0)
//             {
// //                cout << "Evrika! "<<count<<" time = "<< (float)(clock() - t)/CLOCKS_PER_SEC<<endl;
//                 t = clock();
//                 // for (vector<int>::iterator it1 = cur_ar.begin(); it1 != cur_ar.end(); it1++)
//                 // {
//                 //     cout<< *it1<<" ";
//                 // }
//                 // cout<<endl<<"end evrika\n";
//             }
            int temp = 0;
//            count += factorial(cur_ar.size());
//            for (int j = 0; j < cur_ar.size(); j++)
            for (map<int,int>::iterator it = cur_ar.begin();it!= cur_ar.end(); it++)
            {
                temp += it->second;
                //count += Combinations();
            }
            cout<<" temp = "<<temp<<endl;
            for (map<int,int>::iterator it = cur_ar.begin();it!= cur_ar.end(); it++)
            {
                //temp += it->second;
                count += Combinations(temp, it->second);
                temp -= it->second;
            }

//            cur_ar.pop_back();
            (found ? cur_ar[masses[i]]-- : cur_ar.erase(masses[i]));
        }
    }
    return count;
    
}

void counting_peptides(unsigned inputMass)
{
    set<int> massSet;
    map<char,int> massMap;
    mass_map(massMap);
    for (map<char,int>::iterator it = massMap.begin(); it != massMap.end();it++)
    {
        massSet.insert(it->second);
//        cout<<it->second<<" ";
    }
//    cout<<endl;
    cout<<"mass = "<<inputMass<<endl;
    map<int,int> cur_ar;
    vector<int> massvec;
    for (map<char,int>::iterator it = massMap.begin(); it != massMap.end();it++)
    {
        massvec.push_back(it->second);
//        cout<<it->second<<" ";
    }

    cout << "count = "<<counting_peptides_sub(inputMass, massvec, cur_ar,0)<<endl;
}



