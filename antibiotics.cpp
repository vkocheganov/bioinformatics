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
void generating_theoretical_spectrum1(vector<int> inputPeptide, vector<int> &outputSpectrum)
{
    string temp;
    map<char,int> masses;
    mass_map(masses);
    outputSpectrum.push_back(0);
    for (unsigned curlength = 1; curlength < inputPeptide.size(); curlength++)
    {
        for (unsigned curstart = 0; curstart < inputPeptide.size(); curstart++)
        {
            boost::uint64_t sum = 0;
            temp = "";
            unsigned curpostemp = curstart;
            for (unsigned curpos = 0; curpos < curlength; curpos++)
            {
                sum += inputPeptide[curpostemp];
                if (curpostemp == inputPeptide.size() - 1)
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
    unsigned curlength = inputPeptide.size();
    for (unsigned curpos = 0; curpos < curlength; curpos++)
    {
        sum += inputPeptide[curpostemp];
        if (curpostemp == inputPeptide.size() - 1)
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
vector<int> masses, masses_double, double_masses, triple_masses;
vector<int> masses_count, double_masses_count, triple_masses_count;
boost::uint64_t count = 0;

boost::uint64_t counting_peptides_sub(int inputMass, int prev_mas)
{
    cout <<"counting\n";
    int temp = 1, total = 0;
    for (int i = prev_mas; i < masses.size(); i++)
    {
        if (inputMass - masses[i] > 0)
        {
            masses_count[i]++;
            counting_peptides_sub(inputMass - masses[i], i);
            masses_count[i]--;
        }
        else if (inputMass - masses[i] == 0)
        {
            masses_count[i]++;
            temp = 1, total = 0;
            for (int j = 0; j < masses_count.size(); j++)
            {
                total += masses_count[j];
            }
            
           cout<<"Evrika total = "<<total<<endl;
            for (int j = 0; j < masses_count.size(); j++)
            {
                if (masses_count[j])
                {
                    temp *= Combinations(total, masses_count[j] );
                    total -= masses_count[j];
                    cout<<masses[j]<<" "<<masses_count[j]<<endl;
                }
                
            }

            count += temp;
            masses_count[i]--;
        }
        else
        {
            return count;
        }
        
    }
    return count;
}


boost::uint64_t counting_peptides_sub2(int inputMass, int prev_mas)
{
    int temp = 1, total = 0;
    for (int i = prev_mas; i < double_masses.size(); i++)
    {
        if (inputMass - double_masses[i] > 0)
        {
            double_masses_count[i]++;
            counting_peptides_sub(inputMass - double_masses[i], i);
            double_masses_count[i]--;
        }
        else if (inputMass - double_masses[i] == 0)
        {
            double_masses_count[i]++;
            temp = 1, total = 0;
            for (int j = 0; j < double_masses_count.size(); j++)
            {
                total += double_masses_count[j];
            }
            
//           cout<<"Evrika total = "<<total<<endl;
            for (int j = 0; j < double_masses_count.size(); j++)
            {
                if (double_masses_count[j])
                {
                    temp *= Combinations(total, double_masses_count[j] );
                    total -= double_masses_count[j];
//                cout<<masses[j]<<" "<<masses_count[j]<<endl;
                }
                
            }
            
            count += temp;
            double_masses_count[i]--;
        }
        else
        {
            return count;
        }
        
    }
    return count;
}

vector< vector<int> > triple_masses_18,
           double_masses_18;
boost::uint64_t count_all_masses(int double_mas_ind, int mas_ind)
{
    // vector<int> temp_masses;
    // for (int i = 0; i < masses.size(); i++)
    // {
    //     temp_masses.push_back(0);
    // }
    int total = 0, temp = 1;
    int loc_count = 0;
    for (int i = 0; i < triple_masses_count.size(); i++)
    {
        total += triple_masses_count[i];
    }
    for (int i = 0; i < triple_masses_count.size(); i++)
    {
        if (triple_masses_count[i])
        {
            temp *= Combinations(total, triple_masses_count[i] );
            total -= triple_masses_count[i];
//            cout << "i = "<<int(i  / 324) << " " << int((i%324)/18) <<" "<< i % 18<< " tr = "<<triple_masses_count[i]<<endl;
        }
        
        // temp_masses[(triple_masses_18[i])[0]] += triple_masses_count[i];
        // temp_masses[(triple_masses_18[i])[1]] += triple_masses_count[i];
        // temp_masses[(triple_masses_18[i])[2]] += triple_masses_count[i];
    }
//    cout << "returning "<<temp<<"double mas ind = "<<double_mas_ind<<" mas_ind = "<<mas_ind<<endl;
    return temp;
}

boost::uint64_t counting_peptides_sub3(int inputMass, int prev_mas)
{
    bool double_18 = false, triple_18=false;
    int temp = 1, total = 0;
    for (int i = prev_mas; i < triple_masses.size(); i++)
    {
//        cout<<"input "<< inputMass<<" triple_masses "<<triple_masses[i]<<endl;
        if (inputMass - triple_masses[i] > 0)
        {
            triple_masses_count[i]++;
            counting_peptides_sub3(inputMass - triple_masses[i], i);
            triple_masses_count[i]--;
        }
        else if (inputMass - triple_masses[i] == 0)
        {
            triple_masses_count[i]++;
            count += count_all_masses(-1,-1);
            triple_masses_count[i]--;
        }
        else
        {
            triple_18 = true;
        }
    }
    if (triple_18 == true)
    {
//        cout<<"triple == true\n";
        double_18 = false;
        for (int j = 0; j < double_masses.size(); j++)
        {
//            cout <<"input mas "<<inputMass<<" double "<<double_masses[j]<<endl;
            if (inputMass - double_masses[j] == 0)
            {
                count += count_all_masses(j,-1);
            }
            else if (inputMass  - double_masses[j] < 0)
            {
                double_18 = true;
            }
        }
        if (double_18 == true)
        {
            int k = 0;
//            cout<<"double == true "<<inputMass<<" masses.size() "<<masses.size()<<endl;
            for (k = 0; k < masses.size(); k++)
            {
                if (inputMass - masses[k] == 0)
                {
//                    cout<<" Yuppy: ["<<k<<"] "<<masses[k]<<endl;
                    count += count_all_masses(-1,k);
                }
            }
        }
        else
        {
//            cout<<"double == false\n";
        }
        
    }
    else
    {
//        cout<<"triple == false\n";
    }
    
    
    return count;
}

vector<int> mas_array;
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
//        cout<<"evrika:"<<endl;
        for (int i = 0; i < 18; i++)
        {
            if (mas_array[i])
            {
//                cout <<masses[i]<<" "<<mas_array[i]<<" ";
                temp *= Combinations(total, mas_array[i]);;
            }
            total -= mas_array[i];
        }
//            cout<<endl;

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

boost::uint64_t** global_d;
boost::uint64_t counting_peptides_sub4(int inputMass)
{
    vector<uint64_t> res_array;
    for (int i = 0; i <= inputMass; i++)
    {
        res_array.push_back(0);
    }

    for (int i = 0; i <= inputMass; i++)
    {
        for (int j = 0; j < masses.size(); j++)
        {
            if (i - masses[j] > 0)
            {
                if (res_array[i - masses[j]] != 0)
                {
                    res_array[i] += res_array[i - masses[j]];
                    // if (masses[j] == 113 || masses[j] == 128)
                    //     res_array[i] += res_array[i - masses[j]];
                }
            }
            else if (i - masses[j] == 0)
            {
                res_array[i] += 1;
                // if (masses[j] == 113 || masses[j] == 128)
                //     res_array[i] += 1;
            }
        }
    }
    return res_array[inputMass];
}

int counting_peptides(unsigned inputMass)
{
    count = 0;
    clock_t t = clock();
    set<int> massSet;
    map<char,int> massMap;
    mass_map(massMap);
    masses.clear();
    massSet.clear();
    double_masses.clear();
    triple_masses.clear();
    for (map<char,int>::iterator it = massMap.begin(); it != massMap.end();it++)
    {
        massSet.insert(it->second);
    }
//    cout<<"mass = "<<inputMass<<endl;
    int i1 = 0, i2= 0, i3 = 0;
    for (set<int>::iterator it = massSet.begin(); it != massSet.end();it++, i1++)
    {
        for (set<int>::iterator it1 = massSet.begin(); it1 != massSet.end();it1++, i2++)
        {
            double_masses.push_back(*it + *it1);
            double_masses_count.push_back(0);
            for (set<int>::iterator it2 = massSet.begin(); it2 != massSet.end();it2++, i3++)
            {
                triple_masses.push_back(*it + *it1 + *it2);
                triple_masses_count.push_back(0);
                vector<int> temp_vec;
            }
        }

                
        masses.push_back(*it);
        masses_count.push_back(0);
    }
    for (int i = 0 ; i < 18 ; i ++)
        mas_array.push_back(0);

//    int diff = counting_peptides_sub(inputMass, 0) - counting_peptides_sub3(inputMass, 0);
//    if (diff != 0)
//        cout <<"diff = "<<diff<<"mass = "<<inputMass<<endl;
//    cout <<"count_before "<<count<<endl;
    global_d = new boost::uint64_t*[inputMass];
    for (int i = 0; i < inputMass; i++)
    {
        global_d[i] = new boost::uint64_t[inputMass];
        for (int j = 0; j < inputMass; j++)
            global_d[i][j] = 0;
    }

    for (int i = 1; i <= 186; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
        }
    }
    
    return counting_peptides_sub1(inputMass,0);
    
//    cout <<" time = "<<((double(clock()) - t))/CLOCKS_PER_SEC<<endl;
}

// int array[10] = {0,1,2,3,4,5,6,7,8,9};

void swap(int x, int y, vector<int>& ar){
    int temp = ar[x];
    ar[x]=ar[y];
    ar[y]=temp;

    return;
}

// bool is_consistent(vector<int>& peptide, set<int>& spectrum)
// {
    
// }


// void printArray(int size, vector<int>& ar){
//     int i;

//     for (i=0;i<size -1;i++)
//         std::cout << ar[i] << "-";
//     std::cout << ar[i] <<" ";


//     return;
// }

int premuteCount;
vector<vector<int> > perm_ar;
vector<vector<int> > possible_ar;
void permute(int k,int size, vector<int>& ar){
    int i;

    if (k==0)
        perm_ar.push_back(ar);
    else{
        for (i=k-1;i>=0;i--){
            swap(i,k-1,ar);
            permute(k-1,size,ar);
            swap(i,k-1,ar);
        }
    }
//     return;
}

void calc_possible(vector<int>& possible_aminos,int pos, vector<int> temp_ar)
{
    if (pos == possible_aminos.size())
    {
        possible_ar.push_back(temp_ar);
        return;
    }
    calc_possible(possible_aminos, pos+1, temp_ar);
    temp_ar.push_back(possible_aminos[pos]);
    calc_possible(possible_aminos, pos+1, temp_ar);
}

#include <numeric>
#include <set>
#include <functional>
bool is_consistent(vector<int>& peptide, set<int>& spectrum)
{
    vector<int>::iterator it = peptide.begin();
    for (unsigned curlength = 1; curlength < peptide.size(); curlength++)
    {
        for (unsigned curstart = 0; curstart < peptide.size(); curstart++)
        {
            boost::uint64_t sum = 0;
            unsigned curpostemp = curstart;
            for (unsigned curpos = 0; curpos < curlength; curpos++)
            {
                sum += peptide[curpostemp];
                if (curpostemp == peptide.size() - 1)
                    curpostemp = 0;
                else
                    curpostemp++;
            }
            if (spectrum.end() == spectrum.find(sum) )
            {
//                cout <<"no mass" <<sum<<endl;
                return false;
            }

            //outputSpectrum.push_back(sum);
//            cout <<"sum = "<< sum<<endl;
        }
    }

    // for (int i = 1; i < peptide.size(); i++)
    // {
    //     for (it = peptide.begin(); it != peptide.end(); it++)
    //     {
    //         int temp = 0;
    //         for(std::vector<int>::iterator j=it;j!=it+i;++j)
    //         {
    //                 temp += *j;  
    //         }
    //         if (spectrum.end() == spectrum.find(temp) )
    //         {
    //             cout <<"no mass" <<temp<<endl;
    //             return false;
    //         }
            
    //     }
    // }
    return true;
}
#include <algorithm>


void cycloPeptideSequencing(vector<int>& spectrum)
{
    std::sort (spectrum.begin(), spectrum.end());
    // vector<int> aminos;
    // cout<<"mass = "<<mass;
    set<int> spectrum_set;
    cout<<"spectrum set ";
    for (int i = 0; i < spectrum.size(); i++)
    {
        spectrum_set.insert(spectrum[i]);
        cout<<spectrum[i]<<" ";
    }
    
    int ind = 1;
    vector<int> stable_aminos,
        possible_aminos,
        temp_ar;
    while (spectrum[ind] <= 186)
    {
        int temp = counting_peptides(spectrum[ind]);

        if (temp == 1)
            stable_aminos.push_back(spectrum[ind]);
        else
            possible_aminos.push_back(spectrum[ind]);
        
        ind++;
    }
    cout <<"stable = "<<stable_aminos.size()<<" possible = "<<possible_aminos.size()<<endl;
    permute(stable_aminos.size(),stable_aminos.size(),stable_aminos);
    calc_possible(possible_aminos, 0, temp_ar);
    int count = 0;
    cout<<"solution:"<<endl;
    for (int j = 0; j < possible_ar.size(); j++)
    {
//        cout <<"size = " << j<<endl;
//        vector<int> local_temp = perm_ar[i];
        vector<int> local_temp = stable_aminos;
        local_temp.insert(local_temp.begin(),possible_ar[j].begin(),possible_ar[j].end());
        if ((local_temp.size()*(local_temp.size()-1)) + 2 != spectrum.size())
        {
            continue;
        }
        perm_ar.clear();
        permute(local_temp.size(),local_temp.size(),local_temp);
        for (int i = 0; i < perm_ar.size(); i++)
        {
            local_temp = perm_ar[i];
            // cout<<"checking peptide "<<endl;
            // for (int k = 0; k < local_temp.size(); k++)
            // {
            //     cout<<local_temp[k]<<" ";
            // }
            // cout<<endl;

            
            if (is_consistent(local_temp, spectrum_set))
            {
                int sum = 0;
                for (int k = 0; k < local_temp.size()-1;k++)
                {
                    sum += local_temp[k];
                }
//                cout <<"sum = "<<sum<<endl;
                if (spectrum_set.end() != spectrum_set.find(sum))
                {
                    for (int k = 0; k < local_temp.size()-1;k++)
                    {
                        cout<<local_temp[k]<<"-";
                    }

                    cout<<local_temp[local_temp.size()-1]<<" ";
                }
                
            }
        }
    }
//    cout<<"count = "<<count<<endl;
    // for (int i = 0; i < possible_ar.size(); i++)
    // {
    //     for (int j = 0; j < possible_ar[i].size();j++)
    //     {
    //         cout<<possible_ar[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    cout<<"stable size = "<<perm_ar.size()<<endl;
    cout<<"possible_ar size = "<<possible_ar.size()<<endl;
    return;
//    permute(possible_aminos.size(),possible_aminos.size(),possible_aminos);
    for (int i = 0; i < perm_ar.size(); i++)
    {
        // for (int j = 0; j < perm_ar[i].size(); j++)
        //     cout<<perm_ar[i][j]<<" ";
        
        cout<<endl;
    }
    
//    for ()
    // while (mass != 0)
    // {
    //     ind++;
    //     mass -= spectrum[ind];
    //     aminos.push_back(spectrum[ind]);
    // }
    // return ;
    // cout<<"aminos = "<<ind<<endl;
    // permute(3,3, aminos);
}

bool myFunction(std::pair<int,int> first, std::pair<int,int> second)
{
    if (first.second > second.second)
        return true;
    if (first.second == second.second)
        if (first.first > second.first)
            return true;
    return false;
}

int find_max(map<int,int>& mymap)
{
    
}


void spectralConvolutionProblem(vector<int> spectrum, vector<std::pair<int,int> >& outputConvolution)
{
    std::sort (spectrum.begin(), spectrum.end());
    // cout<<"input spectrum"<<endl;
    // for (int i = 0; i < spectrum.size(); i++)
    // {
    //     cout <<spectrum[i]<<" ";
    // }
    // cout<<endl;
    
    map<int,int> convolution;
    for (int i = 1; i < spectrum.size(); i++)
    {
        int temp = spectrum[i];
//         if (convolution.find(temp) != convolution.end())
//         {
// //            cout<<"found "<<temp<<endl;
//             convolution[temp] ++;
//         }
//         else
//         {
// //            cout<<"adding "<<temp<<endl;
//             convolution[temp] = 1;
//         }
        for (int j = 0; j < i; j++)
        {
            temp = spectrum[i] - spectrum[j];
            if (convolution.find(temp) != convolution.end())
            {
//            cout<<"found "<<temp<<endl;
                convolution[temp] ++;
            }
            else if (temp > 0)
            {
//            cout<<"adding "<<temp<<endl;
                convolution[temp] = 1;
            }
        }
    }
    vector<std::pair<int,int> > myVec(convolution.begin(), convolution.end());
    std::sort(myVec.begin(),myVec.end(),&myFunction);
    cout<<endl;
    outputConvolution = myVec;
    cout<<"convolution:"<<endl;
    for (vector<std::pair<int,int> > ::iterator it = myVec.begin(); it != myVec.end(); it++)
    {
        cout <<it->first<<" "<<it->second<<endl;
    }
}

//generating_theoretical_spectrum(string inputPeptide, vector<int> &outputSpectrum)
void print_vector(const vector<int>& vec)
{
    cout<<"vector: ";
    for (int i = 0; i < vec.size() - 1; i++)
    {
        cout << vec[i]<<"-";
    }
    cout<<vec[vec.size() - 1];
    cout<<endl;
}

int score(vector<int> peptide, vector<int> theoreticalSpectrum)
{
//    cout<<"comparing:"<<endl;
//    print_vector(spectrum);
//    print_vector(theoreticalSpectrum);
    vector<int> spectrum;
    generating_theoretical_spectrum1(peptide,spectrum);
    int matches = 0;
    vector<int>::iterator it;
    for (int i = 0; i < spectrum.size(); i++)
    {
        it = find (theoreticalSpectrum.begin(), theoreticalSpectrum.end(), spectrum[i]);
        if( theoreticalSpectrum.end() != it)
        {
            matches++;
            theoreticalSpectrum.erase(it);
        }
    }
    return matches;
}
template <typename T1, typename T2>
struct less_second {
    typedef pair<T1, T2> type;
    bool operator ()(type const& a, type const& b) const {
        return a.second < b.second;
    }
};

void leaderBoardCyclopeptideSequencingSub(int N, vector<int> theoreticalSpectrum, vector<int>& alphabet);
void leaderBoardCyclopeptideSequencing(int N, vector<int> theoreticalSpectrum)
{
    map<char,int> massMap;
    mass_map(massMap);
    
    set<int> massSet;
    for (map<char,int>::iterator it = massMap.begin(); it != massMap.end();it++)
    {
        massSet.insert(it->second);
    }
    masses.clear();

    for (set<int>::iterator it = massSet.begin(); it != massSet.end();it++)
    {
        masses.push_back(*it);
        cout << *it<<endl;
    }
    
    leaderBoardCyclopeptideSequencingSub(N, theoreticalSpectrum, masses);
}
void ConvolutionCyclopeptideSequencing(int M, int N, vector<int> theoreticalSpectrum)
{
    std::sort(theoreticalSpectrum.begin(),theoreticalSpectrum.end());
    vector<std::pair<int,int> > convolution;
    spectralConvolutionProblem(theoreticalSpectrum, convolution);
    vector<std::pair<int,int> >::iterator it = convolution.begin();
    for (it = convolution.begin(); it != convolution.end(); it++)
    {
        cout<<it->first<<" "<<it->second<<endl;
    }
    int i = 0, j = 0;
    vector<int> alphabet;
    map<char,int> realMass;
    mass_map(realMass);
    
    set<int> realMassSet;
    for (map<char,int>::iterator it = realMass.begin(); it != realMass.end();it++)
    {
        realMassSet.insert(it->second);
    }

    while ((i < M) && (j < convolution.size()))
    {
//        if ((convolution[j].first >= 57) && (convolution[j].first <= 186) && (realMassSet.find(convolution[j].first) != realMassSet.end()))
        if ((convolution[j].first >= 57) && (convolution[j].first <= 200) )
        {
            alphabet.push_back(convolution[j].first);
            i++;
        }
        j++;
    }
    std::sort(alphabet.begin(),alphabet.end());
    leaderBoardCyclopeptideSequencingSub(N, theoreticalSpectrum, alphabet);
        
}

void leaderBoardCyclopeptideSequencingSub(int N, vector<int> theoreticalSpectrum, vector<int>& alphabet)
{
    cout<<"alphabet:"<<endl;
    for (int i = 0; i < alphabet.size(); i++)
    {
        cout<<alphabet[i]<<" ";
    }
    cout<<endl;
    map<vector<int>,int > leaderBoard;

    vector<int> temp;
    pair<vector<int>,int > leader(temp,0);
    leaderBoard.insert(leader);
    map<vector<int>,int >::iterator it = leaderBoard.begin(), it_next = leaderBoard.begin();
    map<vector<int>,int > tempMap;
    while (leaderBoard.size() > 0)
    {
        tempMap.clear();
        for (it = leaderBoard.begin(); it != leaderBoard.end(); it++)
        {
            for (int i = 0; i < alphabet.size(); i++)
            {
                temp = it->first;
                temp.push_back(alphabet[i]);
                int scor = score(temp,theoreticalSpectrum);
                tempMap.insert( pair< vector < int >,int >( temp, scor) );
            }
        }
        leaderBoard.clear();
        for (it = tempMap.begin(); it != tempMap.end(); it++)
        {
            leaderBoard.insert(pair< vector<int>,int >(it->first,it->second));
        }
        tempMap.clear();
        for (it = leaderBoard.begin(); it != leaderBoard.end();it++)
        {
            temp = it->first;
            int sum = 0;
            for (int k = 0; k < temp.size();k++)
            {
                sum += temp[k];
            }
            if (sum  == theoreticalSpectrum[theoreticalSpectrum.size()-1])
            {
                if (it->second > leader.second)
                {
                    leader.first = it->first;
                    leader.second = it->second;
                    cout<<"new leader with score = "<<it->second<<" and size = "<<it->first.size()<<endl;
                    print_vector(it->first);
                }
            }
            else if (sum > theoreticalSpectrum[theoreticalSpectrum.size() - 1])
            {
                continue;
            }
            tempMap.insert(pair<vector<int>,int>(it->first,it->second));
        }
        leaderBoard.clear();
        leaderBoard = tempMap;
        if (leaderBoard.size() > N)
        {
            vector<pair<vector<int>, int> > mapcopy(leaderBoard.begin(), leaderBoard.end());
            sort(mapcopy.begin(), mapcopy.end(), less_second< vector<int>, int>());
            int i = 0;
            int t = mapcopy.size() - N;
            mapcopy.erase(mapcopy.begin(),mapcopy.begin() + mapcopy.size() - N);
            leaderBoard.clear();
            for (i = 0;i < mapcopy.size(); i++)
            {
                leaderBoard.insert(mapcopy[i]);
            }
        }
    }
        cout<<"leader:"<<endl;
        print_vector(leader.first);
        cout<<leader.second<<endl;
        temp.clear();
        generating_theoretical_spectrum1(leader.first,temp);
        std::sort(temp.begin(),temp.end());
        print_vector(temp);
        cout<<"the end\n";
}
