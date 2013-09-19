#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream my_file;
    string line;
    int count = 0;
    my_file.open("Vibrio_cholerae.txt");
    if (my_file.is_open())
    {
        while (getline(my_file,line))
        {
            count += line.length();
            // cout << "line " << count << ":" << line << endl;
        }
    }
    else
    {
        cout <<"Error" << endl;
    }
    cout << "count = " << count<< endl;
    my_file.close();
    return 0;
}
