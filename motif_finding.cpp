#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <set>
#include "main.h"
#include <boost/cstdint.hpp>
#include <stdio.h>
using namespace std;

vector<int> comb;
extern char nucl[];
bool equal_with_d_mism(const char* word1, const char* word2, int inputD)
{
    // string temp;
    // for (vector<int>::iterator it = comb.begin(); it != comb.end(); it++ )
    // {
    //     for (unsigned l = 0; l < (unsigned)1<<(2*inputD); l++)
    //     {
    //         temp = string(word1);
    //         comp_temp = comp_pattern;
    //         errcount = 0;
    //         for (int j = 0; j < inputK;j++)
    //         {
    //             if (*it & (1<<j))
    //             {
    //                 temp[j] = comp_temp[j] = nucl[((3 <<(2*errcount)) & l) >>(2*errcount)];
    //                 errcount++;
    //             }
    //         }
    //         temp_set.insert(temp);
    //         temp_set_comp.insert(comp_temp);
    //     }
    // }
}


string generate_most_probable_kmer(vector< map<char, double> >& profile, string line)
{
    int bestInd = 0;
    double bestProb = 0;
    for (int i = 0; i < line.length() - profile.size() + 1; i++)
    {
        double  prob = 1;
        for (int j = 0 ; j < profile.size(); j++)
        {
            prob *= profile[j][line[i + j]];
        }
        if (prob > bestProb)
        {
            bestProb = prob;
            bestInd = i;
        }
//        cout <<"i = "<<i<<" prob = " <<prob<<endl;
    }
//    cout<<"bestInd = "<<bestInd<<" best Prob = "<<bestProb<<endl;
//    cout<<" most probable = "<<string(line, bestInd, profile.size());
    return string(line, bestInd, profile.size());
}


void generate_profile(vector<string> inputMotifs, vector< map<char, double> >& profile)
{
    profile.clear();
    map<char,double> temp;
    temp['A'] = 0;
    temp['T'] = 0;
    temp['C'] = 0;
    temp['G'] = 0;
    profile = vector< map<char, double> >(inputMotifs[0].length());
    string temp_string;
    temp.clear();
    for (int j = 0; j < inputMotifs.size(); j++)
    {
        for (int i = 0; i < inputMotifs[j].length(); i++)
        {
            profile[i][inputMotifs[j][i]] += 1;
        }
    }

    for (int i = 0; i < profile.size(); i++)
    {
        double sum = 0;
        sum = profile[i]['A'] + profile[i]['T'] + profile[i]['C'] + profile[i]['G'];
        profile[i]['A'] /= sum;
        profile[i]['T'] /= sum;
        profile[i]['C'] /= sum;
        profile[i]['G'] /= sum;
    }
//    cout <<"most probable: "<< generate_most_probable_kmer(profile)<<endl;
}

void generate_profile_gauss(vector<string> inputMotifs, vector< map<char, double> >& profile)
{
    profile.clear();
    map<char,double> temp;
    temp['A'] = 0;
    temp['T'] = 0;
    temp['C'] = 0;
    temp['G'] = 0;
    profile = vector< map<char, double> >(inputMotifs[0].length());
    string temp_string;
    temp.clear();
    for (int j = 0; j < inputMotifs.size(); j++)
    {
        for (int i = 0; i < inputMotifs[j].length(); i++)
        {
            profile[i][inputMotifs[j][i]] += 1;
        }
    }

    for (int i = 0; i < profile.size(); i++)
    {
        double sum = 0;
        profile[i]['A']++;
        profile[i]['T']++;
        profile[i]['C']++;
        profile[i]['G']++;
        sum = profile[i]['A'] + profile[i]['T'] + profile[i]['C'] + profile[i]['G'];
        profile[i]['A'] /= sum;
        profile[i]['T'] /= sum;
        profile[i]['C'] /= sum;
        profile[i]['G'] /= sum;
        // sum = profile[i]['A'] + profile[i]['T'] + profile[i]['C'] + profile[i]['G'] + 4;
        // profile[i]['A'] = (profile[i]['A'] + 1)/sum;
        // profile[i]['T'] = (profile[i]['T'] + 1)/sum;
        // profile[i]['C'] = (profile[i]['C'] + 1)/sum;
        // profile[i]['G'] = (profile[i]['G'] + 1)/sum;
    }
//    cout <<"most probable: "<< generate_most_probable_kmer(profile)<<endl;
}

int score_motif(vector<string> inputMotifs)
{
    map<char,double> temp;
    temp['A'] = 0;
    temp['T'] = 0;
    temp['C'] = 0;
    temp['G'] = 0;
    string temp_string;
    char best_char;
    int best_score;
    int sum = 0;
    int score = 0;
    for (int i = 0; i < inputMotifs[0].length(); i++)
    {
        temp.clear();
        for (int j = 0; j < inputMotifs.size(); j++)
        {
            temp[inputMotifs[j][i]] += 1;
        }
        best_score = 0;
        sum = 0;
        for (map<char, double>::iterator it = temp.begin(); it != temp.end(); it++)
        {
            sum += it->second;
            if (it->second > best_score)
            {
                best_score = it->second;
                best_char = it->first;
            }
        }
        score += sum - best_score;
//        cout <<"i = "<<i<<" score = "<<score<<endl;
    }

//    cout <<"score = "<< score<<endl;
    return score;
}

int HemmingDistance(string word1, string word2)
{
    int sum = 0;
    for (int i = 0; i < word1.length(); i++)
    {
        if (word1[i] != word2[i])
        {
            sum++;
        }
    }
    return sum;
}

int GeneralHemmingDistance(string inputPattern, string inputDNAi)
{
    int k = inputPattern.length();
    int l = inputDNAi.length();
    int min = k;
    int temp;
    for (int i = 0; i < l - k + 1; i++)
    {
        temp = HemmingDistance(inputPattern,string(inputDNAi, i, k));
        if ( temp < min)
            min = temp;
    }
    return min;
}

void GreedyMotifSearch(vector<string>& DNA, int k, int t)
{
    vector<string> bestMotifs,
        motifs;
    string motif;
    vector< map<char,double> > profile;
    
    for (int i = 0; i < DNA.size(); i++)
    {
        bestMotifs.push_back(string(DNA[i],0,k));
    }
    int bestScore = score_motif(bestMotifs);
    for (int i = 0; i < DNA[0].length() -k + 1; i++)
    {
        motifs.clear();
        motif = string(DNA[0], i, k);
        motifs.push_back(motif);
        for (int j = 1; j < DNA.size(); j++)
        {
            profile.clear();
//            generate_profile(motifs, profile);
            generate_profile_gauss(motifs, profile);
            motif = generate_most_probable_kmer(profile, DNA[j]);
            motifs.push_back(motif);
        }
        int tempScore = score_motif(motifs);
        if (tempScore < bestScore )
        {
            bestMotifs = motifs;
            bestScore = tempScore;
        }
    }
    for (int i = 0; i < bestMotifs.size(); i++)
    {
        cout<<bestMotifs[i]<<endl;
    }
}

int TotalGeneralHemmingDistance(string inputPattern, vector<string> inputDNA)
{
    int sum = 0;
    for (int i = 0; i < inputDNA.size(); i++)
    {
        sum += GeneralHemmingDistance(inputPattern, inputDNA[i]);
    }
    return sum;
}

string MedianString(vector<string>& inputDNA, int k)
{
    string bestPattern;
    int bestDist = k * inputDNA.size();
    string temp_string;
    int temp;
    for (unsigned l = 0; l < (unsigned)1<<(2*k); l++)
    {
        temp_string.clear();
        for (int m = 0; m < k;m++)
        {
            temp_string.push_back(nucl[((3 <<(2*m)) & l) >>(2*m)]);
        }
        temp = TotalGeneralHemmingDistance(temp_string, inputDNA);
        if (temp <= bestDist)
        {
            bestDist = temp;
            bestPattern = temp_string;
        }
//        cout<<temp_string<<endl;
    }
    cout<<"that's it!\n";
    return bestPattern;
}

double wordProb(string word, vector< map<char,double> >& profile)
{
    double prob = 1;
    for (int i = 0; i < profile.size(); i++)
        {
            prob *= profile[i][word[i]];
        }
             return prob;
}

    string ProfileMostProbableKMerProblem(string inputDNA, int inputK, vector< map<char,double> >& profile)
    {
        string bestPattern;
        double bestProb = 0;
        string temp;
        double tempProb;
        for (int i = 0; i < inputDNA.length() - inputK + 1; i++)
        {
            temp = string(inputDNA, i, inputK);
            tempProb = wordProb(temp, profile);
            if (tempProb > bestProb)
            {
                bestProb = tempProb;
                bestPattern = temp;
            }
        }
        return bestPattern;
    }
    


void MotifEnumeration(vector<string>& inputDNA, int k, int d, vector<string>& outputKmers)
{
    comb.clear();
    generate_comb(k,d,comb);
    vector < set<string> > kmers;
    set<string> temp;
    string temp_string;
    char* cur_kmer = new char[k + 1];
    int errcount;
    
    for (int i = 0; i < inputDNA.size(); i++)
    {
        temp.clear();
        for (int j = 0; j < inputDNA[i].length() - k + 1; j++)
        {
            inputDNA[i].copy(cur_kmer, k, j);
            cur_kmer[k] = '\0';
            for (vector<int>::iterator it = comb.begin(); it != comb.end(); it++ )
            {
                for (unsigned l = 0; l < (unsigned)1<<(2*d); l++)
                {
                    temp_string = string(cur_kmer);
                    errcount = 0;
                    for (int m = 0; m < k;m++)
                    {
                        if (*it & (1<<m))
                        {
                            temp_string[m] = nucl[((3 <<(2*errcount)) & l) >>(2*errcount)];
                            errcount++;
                        }
                    }
                    temp.insert(temp_string);
                }
            }
            
//            temp.insert(string(cur_kmer));
            //        cout<<cur_kmer<<endl;
        }
        kmers.push_back(temp);
    }

    cout<<"result"<<endl;
    for (set<string>::iterator it = kmers[0].begin(); it != kmers[0].end(); it++)
    {
        bool flag = true;
        for (int j = 1; j < kmers.size(); j++)
        {
            if (kmers[j].find(*it) == kmers[j].end())
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            cout<<*it<<" ";
            outputKmers.push_back(*it);
        }
        
    }
    
    // for (int i = 0; i < kmers.size(); i++)
    // {
    //     cout<< "i = "<<i<<endl;
    //     for (set<string>::iterator j = kmers[i].begin(); j != kmers[i].end(); j++)
    //     {
    //         cout<<*j<<endl;
    //     }
    // }
    
}
vector<int> get_random_vector(int size, int max_val)
{
    vector<int> rand_vec;
    for (int i = 0; i < size; i++)
    {
        rand_vec.push_back(rand()% max_val);
    }
    return rand_vec;
}

vector<string> get_motifs_by_indices(vector<int>& vec_ind, vector<string>& DNA, int k)
{
    vector<string> temp;
    for (int i = 0; i < DNA.size(); i++)
    {
        temp.push_back(string(DNA[i],vec_ind[i],k));
    }
    return temp;
}

#include <time.h>
void RandomizedMotifSearch(vector<string>& DNA, int k, int t, vector<int> rand_vec_inp)
{
    srand(time(NULL));
//    vector<int> rand_vec = get_random_vector(t, DNA[0].length());
    vector<int> rand_vec = rand_vec_inp;
    vector<string> motifs = get_motifs_by_indices(rand_vec, DNA, k);
    vector<string> best_motifs = motifs;
    int best_score = score_motif(best_motifs);
    cout << "initial score = "<<best_score<<endl;
    vector< map<char,double> > profile;
    while (1)
    {
        generate_profile_gauss(motifs, profile);
        motifs.clear();
        for (int i = 0; i < DNA.size(); i++)
        {
            motifs.push_back(generate_most_probable_kmer(profile, DNA[i]));
        }
        int score_temp = score_motif(motifs);
        if (score_temp < best_score)
        {
            best_score = score_temp;
            best_motifs = motifs;
        }
        else
        {
            cout<<"Best motifs:"<<endl;
            for (int i = 0; i < best_motifs.size(); i++)
            {
                cout<<best_motifs[i]<<endl;
            }
            cout<<"score = "<<score_temp<<endl;
            return ;
        }
    }
}
