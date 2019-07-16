
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
int main ()
{
    ifstream myfile ("parawords.txt");
    string line,subStr;
    string subStr_comp = "he";
    long OccCount, LnCount;
    OccCount = LnCount = 0;

	map<int,string> mymap;

	//Load to Map
    if (myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile,line);
            if(line == "\n")
                continue;
            else
            {
                //Split string by space
                //Remove Trailing Space
                for(int i=int(line.size()-1);i >= 0 ;i-- )
                {
                    if(line[line.size() - 1] == '\n')
                        continue;
                    else if(line[i] == ' ')
                        line.erase(i,1);
                    else
                        break;
                }
                //Remove leading Space
                for(int i=0;i<int(line.size());i++ )
                {
                    if(line[i] == ' ')
                        line.erase(i,1);
                    else
                        break;
                }
                //Map Filling
                for(int i = 0; i< int(line.size()); i++)
                {
                    if(line[i] == ' ')
                    {
                        i++;
                        mymap.insert(pair<int,string>(LnCount,subStr));
                        subStr.clear();
                        LnCount++;
                    }
                    else
                        subStr.push_back(line[i]);
                }
            }
        }
    }
    else
        cout << "Unable to open file";

    myfile.close();

	//Parallelize This
    //#pragma omp parallel for default(shared) reduction(+:OccCount) //Error
    for(auto it = mymap.begin();it != mymap.end();it++)
    {
        int j =0;
        line = it->second;
        for(int i=0; i<int(line.size());i++)
        {
            while(line[i] == subStr_comp[j])
            {
                if(j == int(subStr_comp.length()) - 1)
                {
                    //Critical region that manipulates OccCount
                    OccCount++;
                    break;
                }
                i++;
                j++;
            }
            j=0;
        }
    }
    cout<<OccCount<<endl;
    mymap.clear();//Clear Map, check for next file
    return 0;
}
