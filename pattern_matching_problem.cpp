#include <iostream>
#include <fstream>
#include <map>

using namespace std;

int main ()
{
    ifstream file("/home/maths/Downloads/Vibrio_cholerae.txt");
    if (file.is_open())
    {
        string pattern("CTTGATCAT"), line;
        // if (getline(file,pattern))
        // {
        //     cout << "got pattern " << pattern<< endl;
        // }
        if (getline(file,line))
        {
            cout << "got line " <<  " of size "<<line.length()<< endl;
        }
        for (int i = 0; i < line.length() - pattern.length() + 1; i++)
        {
            if (line.compare(i,pattern.length(),pattern) == 0)
            {
                cout <<i<<" ";
            }
        }
    }
    else
    {
        cout<<"Error opening file"<<endl;
    }
}
