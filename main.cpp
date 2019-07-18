#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <omp.h>
using namespace std;
int main()
{
	ifstream myfile("words.txt");
	string line, subStr = "";
	string subStr_comp = "";
	int occCount, map_key = 0;

	map<int,string> mymap;
	cout<< "Enter string to compare: ";
	cin >> subStr_comp;
	
	double vtime_start = omp_get_wtime();
	//Load to vector
	if (myfile.is_open())
	{
		while (!myfile.eof())
		{
			getline(myfile, line);
			if (line == "\n")
				continue;
			//Get Line and remove leading and trailing spaces
			else
			{
				//Remove Trailing Space of line
				for (int i = int(line.size() - 1); i >= 0; i--)
				{
					if (line[line.size() - 1] == '\n')
						continue;
					else if (line[i] == ' ')
						line.erase(i);
					else
						break;
				}
				//Remove leading Space of line
				for (int i = 0; i<int(line.size()); i++)
				{
					if (line[i] == ' ')
						line.erase(i);
					else
						break;
				}
				//Map Fill Handler
				for (int i = 0; i< int(line.size()); i++)
				{
					if (line[i] == ' ')
					{	//Entries with multiple spaces per word
						//Peek for frontal spaces and ignores it
						if (line[i + 1] == ' ')
							continue;
						else
						{
							mymap.insert(pair<int, string>(map_key, subStr));
							subStr.clear();
						}
					}
					else if (i == int(line.size() - 1))
					{
						//For spaceless entries
						subStr.push_back(line[i]);
						mymap.insert(pair<int,string>(map_key,subStr));
						subStr.clear();
					}
					else
						subStr.push_back(line[i]);
				}
			}
		}
	}
	else
	{
		cout << "Unable to open file\n";
		return -1;
	}

	myfile.close();
	double vEndTime = omp_get_wtime() - vtime_start;
	cout << "Vector Filling Time Taken: " << vEndTime << endl;

	//Parallelize This
	double start_time = omp_get_wtime();
	for (int i = 0; i < int(mymap.size()); i++)
	{
		int j = 0;
		line = mymap[i];
		for (int i = 0; i<int(line.size()); i++)
		{
			while (line[i] == subStr_comp[j])
			{
				if (j == int(subStr_comp.size()) - 1)
				{
					//Critical region that manipulates occCount
					occCount++;
					break;
				}
				i++;
				j++;
			}
			j = 0;
		}

	}
	double time = omp_get_wtime() - start_time;
	cout << "Text Processing Time Taken: " << time << endl;
	cout << "Occurrence of " << subStr_comp << " : " << occCount << endl;
	mymap.clear();//Clear list, check for next file
	return 0;
=======
int main ()
{
    ifstream myfile ("words.txt");
    string line,subStr;
    string subStr_comp = "he"; //Will Change to user input
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
    //Implement folder iteration
    mymap.clear();//Clear Map, check for next file
    return 0;
}
