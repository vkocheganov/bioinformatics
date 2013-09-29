#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <set>
#include "main.h"
#include <boost/cstdint.hpp>
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
            boost::uint64_t sum = 0;
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
    boost::uint64_t sum = 0;
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
boost::uint64_t factorial(boost::uint64_t n)
{
  return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

boost::uint64_t Combinations( boost::uint64_t n,  boost::uint64_t r)
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

        for ( boost::uint64_t i = 2; i < r + 1; ++i, --n)
                v = v * n / i;

        return v;
}

map<int, int> cur_ar;
vector<int> masses, masses_double;
boost::uint64_t counting_peptides_sub(int inputMass, int prev_mas)
{
//    cout<<"inputMass "<<inputMass<<endl;
    static boost::uint64_t count = 0;
    bool found;
    int temp = 1, total = 0;
    map<int,int>::iterator it =  cur_ar.begin();
//    cout<<"combinations = "<<Combinations(10,8)<<endl;
//    cout<<"Entering mass "<<inputMass<<endl;
//    static int count_size = 0;
    for (int i = prev_mas; i < masses.size(); i++)
    {
//         if (cur_ar.size()== 1)
//         {
//             count_size++;
// //            cout << "i= "<<i<<" size "<<cur_ar.size()<< " "<<count_size  <<endl;
//         }
        
        if (inputMass - masses[i] > 0)
        {
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
            counting_peptides_sub(inputMass - masses[i], i);
            (found ? cur_ar[masses[i]]-- : cur_ar.erase(masses[i]));
//            cur_ar.pop_back();
        }
        else if (inputMass - masses[i] == 0)
        {
//            cur_ar.push_back(masses[i]);
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
            temp = 1, total = 0;
//            count += factorial(cur_ar.size());
//            for (boost::uint64_t j = 0; j < cur_ar.size(); j++)
            for (it = cur_ar.begin();it!= cur_ar.end(); it++)
            {
                total += it->second;
                //count += Combinations();
            }
//            cout<<" total = "<<total<<endl;
//            cout<<"Evrika"<<cur_ar.size()<<endl;
            for ( it = cur_ar.begin();it!= cur_ar.end(); it++)
            {
                // if ((it->first == 113) || (it->first == 128))
                //     temp *= (1<<it->second);
                //temp += it->second;
                temp *= Combinations(total, it->second);;
                total -= it->second;
//                cout << it->first<< " "<<it->second<<endl;
            }
            count += temp;
//            cout<<"count = "<<count<<endl;
            // if (count > 1000000000)
            //     cout<< "exceeded\n";
//            cur_ar.pop_back();
            (found ? cur_ar[masses[i]]-- : cur_ar.erase(masses[i]));
        }
    }
    return count;
    
}

vector<int> mas_array;
static boost::uint64_t count = 0;
boost::uint64_t iterations = 0;
boost::uint64_t counting_peptides_sub1(int inputMass, int prev_mas)
{
    if (prev_mas == masses.size())
        return 0;
    bool found;
    int temp = 1, total = 0;
    int cur_mass = inputMass;
    counting_peptides_sub1(cur_mass, prev_mas + 1);
    mas_array[prev_mas] = 1;
    cur_mass = cur_mass - mas_array[prev_mas] * masses[prev_mas];
    while ( cur_mass > 0)
    {
        // if (iterations % 1000000000 == 0)
        //     cout<<"iter = "<<iterations<<endl;
        iterations++;
        counting_peptides_sub1(cur_mass, prev_mas + 1);
        mas_array[prev_mas]++;
        cur_mass = cur_mass - masses[prev_mas];
        // if (prev_mas == 11)
        //     cout << " mas_array[prev_mas] = "<< mas_array[prev_mas]<<endl;
    }

    if (cur_mass == 0)
    {
        temp = 1, total = 0;
        for (int i = 0; i < 18; i++)
        {
            total += mas_array[i];
        }
        for (int i = 0; i < 18; i++)
        {
            if (mas_array[i])
                temp *= Combinations(total, mas_array[i]);;
            total -= mas_array[i];
        }

        // for (it = cur_ar.begin();it!= cur_ar.end(); it++)
        // {
        //     total += it->second;
        // }
        // for ( it = cur_ar.begin();it!= cur_ar.end(); it++)
        // {
        //     if (it->second)
        //         temp *= Combinations(total, it->second);;
        //     total -= it->second;
        // }
        count += temp;
    }
    mas_array[prev_mas] = 0;
//    cur_ar.erase(masses[prev_mas]);// = 0;
    return count;
    
    
}

void counting_peptides(unsigned inputMass)
{
    clock_t t = clock();
    set<int> massSet;
    map<char,int> massMap;
    mass_map(massMap);
    for (map<char,int>::iterator it = massMap.begin(); it != massMap.end();it++)
    {
        massSet.insert(it->second);
    }
    cout<<"mass = "<<inputMass<<endl;
    for (set<int>::iterator it = massSet.begin(); it != massSet.end();it++)
    {
        masses.push_back(*it);
    }
    for (int i = 0 ; i < 18 ; i ++)
        mas_array.push_back(0);
    
    cout << "count = "<<counting_peptides_sub1(inputMass, 0)<<endl;
    cout <<" time = "<<((double(clock()) - t))/CLOCKS_PER_SEC<<endl;
}



