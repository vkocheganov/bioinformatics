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
