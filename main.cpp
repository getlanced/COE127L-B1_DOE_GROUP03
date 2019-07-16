// writing on a text file
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main ()
{
    ifstream myfile ("words.txt");
    string line;
	string subStr="ae";
    long num_count = 0 ;
    if (myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile,line);
            {
                int j =0;
                for(int i = 0; i<int(line.length());i++)
                {
                    while(line[i] == subStr[j])
                    {
                        if(j == int(subStr.length()) - 1)
                        {
                            num_count++;
                            break;
                        }
                        i++;
                        j++;
                    }
                    j=0;
                }
			}
        }
    }
    else
        cout << "Unable to open file";

    cout<<"Occurrences: "<<num_count<<endl;
    myfile.close();

    return 0;
}
