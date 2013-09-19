#include <iostream>
#include <fstream>
#include <map>
using namespace std;

int main ()
{
//    ifstream file("/home/maths/Downloads/stepic_dataset.txt");
    ifstream file("/home/maths/Documents/bioinf/rand_gene.txt");
    if (file.is_open())
    {
        string line;
        int length, k;
        if (getline(file,line))
        {
            length = line.length();
//            cout << "got line " << line<< endl << " of size " << length<<endl;
        }
        file >> k;
        cout << "k = " << k <<endl;
        char *buffer = new char[k+1];
        map <string,int> words;

        for (int i = 0; i < length - k + 1; i++)
        {
            line.copy(buffer,k,i);
            buffer[k] = '\0';
//            cout<< "trying: "<< buffer<< endl;
            if (words.count(buffer) == 0)
            {
                words.insert(std::pair<string,int>(buffer,1));
            }
            else
            {
                words[buffer] += 1;
            }
        }
        std::map<string,int>::iterator it = words.begin();
        int max = 0;
        for (it = words.begin(); it != words.end(); ++it)
        {
            if (it->second >= max)
                max = it->second;
//            cout << it->first << " => " << it->second << endl;
        }
        cout << "The most frequent " << endl;
        for (it = words.begin(); it != words.end(); ++it)
        {
            if (it->second == max)
                cout << it->first << " => "<<it->second << endl;
        }

    }
    else
    {
        cout<<"Error opening file"<<endl;
    }
}
