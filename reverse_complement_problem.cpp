#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
using namespace std;

void reverse_complement(string inputString, string& outputString)
{
    map<char,char> mymap;
    mymap['A']='T';
    mymap['G']='C';
    mymap['T']='A';
    mymap['C']='G';
    int number = inputString.length();
    outputString.resize(inputString.length());
    for (int i = number-1; i >=0; i--)
    {
        outputString[number - i - 1] = mymap[inputString[i]];
    }
}

