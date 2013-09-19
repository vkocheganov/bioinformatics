#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
using namespace std;

char nucl[] = { 'A', 'G', 'T', 'C'};
char nucl_rev[] = {'T', 'C', 'A', 'G'};


int main(int argc, char *argv[])
{
    map<char,char> mymap;
    mymap['A']='T';
    mymap['G']='C';
    mymap['T']='A';
    mymap['C']='G';
    ifstream file("/home/maths/Downloads/stepic_dataset.txt");
    if (file.is_open())
    {
        string line;
        getline (file,line);
        int number = line.length();
        for (int i = number-1; i >=0; i--)
        {
            cout<<mymap[line[i]];
        }
        cout <<endl;
        file.close();
    }
    else
    {
        cout << "Error in opening" << endl;
    }
}

