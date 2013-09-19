#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main ()
{
    ifstream file("/home/maths/Downloads/stepic_dataset.txt");
    if (file.is_open())
    {
        string line;//("TAAAGACTGCCGAGAGGCCAACACGAGTGCTAGAACGAGGGGCGTAAACGCGGGTCCGAT");
        vector<int> min_ind;
        // if (getline(file,pattern))
        // {
        //     cout << "got pattern " << pattern<< endl;
        // }
        int min = 0;
        int func = 0;
        if (getline(file,line))
        {
//            cout << "got line " <<  " of size "<<line.length()<< endl;
        }
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == 'C' || line[i] == 'c')
                func--;
            else if (line[i] == 'G' || line[i] == 'g')
                func++;
            if (func == min)
            {
                min_ind.push_back(i);
            }
            if (func < min)
            {
                min_ind.erase(min_ind.begin(), min_ind.end());
                min = func;
                min_ind.push_back(i);
            }
        }
        cout << "min = " << min << endl;
        for (int i = 0; i < min_ind.size(); i++)
        {
            cout << min_ind[i] << " ";
        }
        
    }
    else
    {
        cout<<"Error opening file"<<endl;
    }
}
