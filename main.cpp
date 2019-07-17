#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <omp.h>
using namespace std;
int main()
{
	ifstream myfile("word2.txt");
	string line, subStr = "";
	string subStr_comp = "her";
	int occCount, map_key = 0;

	map<int,string> mymap;
	
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
}
