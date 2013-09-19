#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

char nucl[] = { 'A', 'G', 'T', 'C'};
    
int main(int argc, char *argv[])
{
    if (argc != 2)
        cout << "need 1 argument!" << endl;
    int number = atoi(argv[1]);
    ofstream file("rand_gene.txt");
    if (file.is_open())
    {
        for (int i = 0; i < number; i++)
        {
            file << nucl[rand() % 4];
        }
        file << endl<<"9";
        file.close();
    }
    else
    {
        cout << "Error in opening" << endl;
    }
    
}

