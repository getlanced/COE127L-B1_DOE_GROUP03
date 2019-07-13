// writing on a text file
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
void comp(string,string,long*);
int main ()
{
    ifstream myfile ("words.txt");
    string line;
    long num_count = 0 ;
    if (myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile,line);
            comp(line,"ea",&num_count);
        }
    }
    else
        cout << "Unable to open file";

    cout<<"Occurrences: "<<num_count<<endl;
    myfile.close();

    return 0;
}

void comp(string line,string sub,long* c)
{
    int j =0;
    for(int i = 0; i<int(line.length());i++)
    {
        while(line[i] == sub[j])
        {
            if(j == int(sub.length()) - 1)
            {
                (*c)++;
                break;
            }
            i++;
            j++;
        }
        j=0;
    }
}
