#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

const char nucl[] = {'A', 'C', 'G', 'T'};
    
int main ()
{
    ifstream file("/home/maths/Downloads/stepic_dataset.txt");
    if (file.is_open())
    {
        string pattern, line;
        int d;
        set<string> pattern_ar;
        if (getline(file,pattern))
        {
            cout << "got pattern " << pattern<< endl;
        }
        if (getline(file,line))
        {
            cout << "got line " <<  " of size "<<line.length()<< endl;
        }
        file >> d;
        {
            cout << "got d " <<d<< endl;
        }
        int* indices = new int[d];
        int* indices_1 = new int[d];

        // int count = 0,
        //     count1 = 0;
        string temp;
        for (int j = 0; j < d; j++)
        {
            indices[j] = j;
        }

        int cur_ind = d - 1;
        while (1)
        {
//            count++;

            // for (int j = 0; j < d; j++)
            // {
            //     cout << indices[j] << " ";
            // }
            // cout <<endl;
            cur_ind = d - 1;
//            cout<<"count1 = "<<count1<<endl;
            for (int j = 0; j < d; j++)
            {
                indices_1[j] = 0;
            }

            while (1)
            {
                temp = pattern;
//                cout<< "temp = "<< temp<<endl;
//                cout << "ind_1 = ";
                for (int i = 0; i <d;i++)
                {
//                    cout<<indices_1[i]<<" ";
                    temp[indices[i]] = nucl[indices_1[i]];
                }
//                cout<<endl;
//                cout<< "temp = "<< temp<<endl;
//                count1++;
                pattern_ar.insert(temp);
                cur_ind = d - 1;
                while( cur_ind >=0 && (indices_1[cur_ind] == 3) )
                {
                    cur_ind--;
                }
                if (cur_ind < 0)
                    break;
                indices_1[cur_ind]++;
                cur_ind++;
                for (int i = cur_ind; i < d; i++)
                    indices_1[i] = 0;
            }
            
            for (int i = 0; i < 4; i ++)
            {
            }

            cur_ind = d - 1;
            while ( (indices[cur_ind] == pattern.length() -1 + cur_ind - d + 1 ) && (cur_ind >= 0))
            {
                cur_ind--;
            }
            if (cur_ind < 0)
                break;
            indices[cur_ind]++;
            cur_ind++;
            while (cur_ind < d)
            {
                indices[cur_ind] = indices[cur_ind - 1] + 1;
                cur_ind++;
            }
        }
//        cout << "count1 "<< count1<<endl;
        cout << "pat count = " << pattern_ar.size()<<endl;
        set <string,int>::iterator it = pattern_ar.begin();
        cout << "pat count = " << pattern_ar.size()<<endl;
        for (int i = 0; i < line.length() - pattern.length() + 1; i++)
        {
            // if (i % 1000 == 0)
            // {
                
            //     cout <<"i = "<<i<<endl;
            // }
            
            for (it = pattern_ar.begin(); it !=  pattern_ar.end(); it++)
            {
                temp = *it;
                if (line.compare(i,temp.length(),temp) == 0)
                {
                    cout <<i<<" ";
                }

            }
        }
    }
    else
    {
        cout<<"Error opening file"<<endl;
    }
}
