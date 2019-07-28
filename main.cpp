#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <omp.h>
#include <dirent.h>

using namespace std;
int main()
{
    DIR *dpdf;
    struct dirent *epdf;
    vector<string> path;
    dpdf = opendir("./txtFiles");
    if (dpdf != NULL)
    {
       while (epdf = readdir(dpdf))
       {
           string subStr_file_ext = ".txt";
           if(string(epdf->d_name).find(subStr_file_ext) != string::npos)
           {
               string subStr_txtDir = "./txtFiles/";
               path.push_back(subStr_txtDir + epdf->d_name);
           }
            else
                continue;
       }
    }
    closedir(dpdf);
    string subStr_comp = "";
    cout << "Enter string to compare: ";
    cin >> subStr_comp;
    for(auto it = path.begin();it != path.end(); it++)
    {
        ifstream myfile(*it);
        string line = "", subStr = "";
        int occCount = 0, map_key = 0;
        map<int, string> mymap;
        double fill_time_start = omp_get_wtime();
        //Load to map
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
                        {	
			//Entries with multiple spaces per word
                            //Peek for frontal spaces and ignores it
                            if (line[i + 1] == ' ')
                                continue;
                            else
                            {
                                mymap.insert(pair<int, string>(map_key, subStr));
                                map_key++;
                                subStr.clear();
                            }
                        }
                        else if (i == int(line.size() - 1))
                        {
                            //For spaceless entries
                            subStr.push_back(line[i]);
                            mymap.insert(pair<int, string>(map_key, subStr));
                            map_key++;
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
        double fill_EndTime = omp_get_wtime() - fill_time_start;
        cout << "Map Filling Time Taken: " << fill_EndTime << endl;
        //Parallelize This
        double proc_start_time = omp_get_wtime();
        int j = 0;
        int k = 0;
    #pragma omp parallel for private(line,k,j)
        for (int i = 0; i < int(mymap.size()); i++)
        {
            j = 0;
            line = mymap[i];
            for (k = 0; k<int(line.size()); k++)
            {
                while (line[k] == subStr_comp[j])
                {
                    if (j == int(subStr_comp.size()) - 1)
                    {
                        //Critical region that manipulates occCount
                        #pragma omp critical
                        occCount++;
                        break;
                    }
                    k++;
                    j++;
                }
                j = 0;
            }
        }
        double proc_end_time = omp_get_wtime() - proc_start_time;
        cout << "Text Processing Time Taken: " << proc_end_time << endl;
        cout << "Occurrence of " << subStr_comp << " : " << occCount << endl;
        mymap.clear();//Clear list, check for next file
    }
	return 0;
}
