#include <map>
#include <vector>
#include <string>
using namespace std;
void freq_words(string inputString, int inputPatternSize, map<string,int>& OutputKMers);
void reverse_complement(string inputString, string& outputString);
void pattern_matching(string inputPattern, string inputString, vector<int>& outputPoss);
void clump_finding(string inputString, int inputK, int inputL, int inputT, map<string,int>& outputClumps);
void skew_min(string inputString, vector<int>& outputMinPoints, bool);
void approximate_pattern_matching(string inputPattern,string inputStrging,  int inputD, vector<int> & outputPoss);
void approximate_pattern_matching1(string inputPattern,string inputStrging,  int inputD, vector<int> & outputPoss);
void generate_comb(int n, int k, vector<int>& combinations);
void freq_words_with_mism(string inputString, int inputK, int inputD, vector<string>& outputMaxPat);
void protein_translation(string inputString, string& outputString);
void peptide_encoding(string inputDNA, string inputAmino, vector<string>& outputSubstrings);
void generating_theoretical_spectrum(string inputPeptide, vector<int> &outputSpectrum);
int counting_peptides(unsigned inputMass);
void cycloPeptideSequencing(vector<int>& spectrum);
void spectralConvolutionProblem(vector<int> spectrum);
void leaderBoardCyclopeptideSequencing(int N, vector<int> theoreticalSpectrum);
void ConvolutionCyclopeptideSequencing(int M, int N, vector<int> theoreticalSpectrum);
void MotifEnumeration(vector<string>& inputDNA, int k, int d, vector<string>& outputKmers);
string MedianString(vector<string>& inputDNA, int k);
string ProfileMostProbableKMerProblem(string inputDNA, int inputK, vector< map<char,double> >& profile);
void generate_profile(vector<string> inputMotifs, vector< map<char, double> >& profile);
int score_motif(vector<string> inputMotifs);
void GreedyMotifSearch(vector<string>& DNA, int k, int t);
void RandomizedMotifSearch(vector<string>& DNA, int k, int t, vector<int> rand_vec_inp);
