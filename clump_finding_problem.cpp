#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <string.h>
using namespace std;
int main ()
{
//    ifstream file("/home/maths/Downloads/stepic_dataset.txt");
    ifstream file("/home/maths/Downloads/E-coli.txt");
    if (file.is_open())
    {
        string cur_line, line;
        int length, k, L, t;
        cout << "sizeof(int) = "<<sizeof(int)<<endl;
        if (getline(file,line))
        {
            length = line.length();
            cout << "length = " << length<< endl;
//            cout << "got line " << line<< endl << " of size " << length<<endl;
        }
        // file >> k;
        // cout << "k = " << k <<endl;
        // file >> L;
        // cout << "L = " << L <<endl;
        // file >> t;
        // cout << "t = " << t <<endl;
        k=9;L=500;t=3;
        char const*cur_line_c;
        char const*line_c = line.c_str();
        
        char *buffer = new char[k+1];
        map <string,int> words;
        map <string,int> global_words;
        cur_line_c = line_c;

        for (int i = 0; i < L - k + 1; i++)
        {
            strncpy(buffer,cur_line_c+i,k);// = cur_line_c + i;
            buffer[k] = '\0';
//                    cout<< "trying: "<< buffer<< endl;
            if (words.count(buffer) == 0)
            {
                words.insert(std::pair<string,int>(buffer,1));
//                cout << i << "inserting "<<buffer<<endl;
            }
            else
            {
                words[buffer] += 1;
            }
        }

        std::map<string,int>::iterator it = words.begin();
        for (it = words.begin(); it != words.end(); ++it)
        {
            if (it->second >= t)
            {
//                        cout << it->first << " => " << it->second << endl;
                if (global_words.count(it->first) == 0)
                {
                    global_words.insert(std::pair<string,int>(it->first,it->second));
                    cout << global_words.size()<< " "<<it->first << endl;
                }
                        
            }
        }

        for (int j = 1; j < line.length() - L + 1; j++)
        {
            // if (j % 1000000 == 0)
            //     cout << "j = " << j<<endl;
            cur_line_c = line_c + j;
            strncpy(buffer,cur_line_c-1,k);// = cur_line_c + i;
            buffer[k] = '\0';
            it = words.find(buffer);
            // if (it == words.end())
            // {
            //     cout <<"Error " <<buffer<<" addr "<<(int*)cur_line_c<< " j = "<<j <<endl;
            //     return 1;
            // }
            if (it->second == 1)
            {
                words.erase(it);
            }
            else
            {
                it->second -= 1;
            }

            if (it->second >= t)
            {
                global_words.insert(std::pair<string,int>(it->first,it->second));
//                cout << global_words.size()<< " "<<it->first << endl;
            }
            
            strncpy(buffer,((const char*)cur_line_c)+L-k,k);// = cur_line_c + i;
            buffer[k] = '\0';
            it = words.find(buffer);
            if (it == words.end())
            {
                words.insert(std::pair<string,int>(buffer,1));
            }
            else
            {
                it->second += 1;
            }

            if (it->second >= t)
            {
                global_words.insert(std::pair<string,int>(it->first,it->second));
            }
        }
        // for (it = global_words.begin(); it != global_words.end(); ++it)
        // {
        //     cout << it->first << " ";
        //     if (global_words.count(it->first) >1)
        //         cout << "sddddddddddsdfgsdf\n"<<endl;
        // }
        cout << "global map size = " << global_words.size()<<endl;
    }
    else
    {
        cout<<"Error opening file"<<endl;
    }
    return 0;
}
