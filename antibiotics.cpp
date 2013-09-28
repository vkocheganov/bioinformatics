#include <iostream>
#include <stdlib.h>
#include <map>

using namespace std;

void dna_rna_transcribe(string inputString, string& outputString)
{
    for (unsigned i = 0; i < inputString.length(); i++)
    {
        if (inputString[i] == 'T')
            inputString[i] = 'U';
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
        if (amino_map[buf] != '*')
            outputString.append(1,amino_map[buf]);
    }
}


void protein_translation(string inputString, string& outputString)
{
    dna_rna_transcribe(inputString, outputString);
    rna_amino_translate(inputString, outputString);
}

