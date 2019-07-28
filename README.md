# COE127L-B1_DOE_Group03
Requirements:
- OpenMP 3.1+ support 
(Usually comes with the latest MinGW or TDM-GCC compiler)
TDM-GCC - https://sourceforge.net/projects/tdm-gcc/
MinGW - https://sourceforge.net/projects/mingw/
- c++14 compiler
How to Run:
Linux/ Windows:
1) Put all .txt files to stream under the txtFiles folder.
2) From the terminal, change the directory to where the main.cpp is located
  by executing "cd ./path"
  *Sample path ./Desktop/ 
3) Compile the program with the flag -fopenmp to enable omp.h and its #pragma directive.
  g++ -fopenmp -o prog prog.cpp
4) Profit.

To Graph
Requirements:
-Python version 3.7

To run:
- Have the graphDat.csv on the same folder as the python file.
- Assuming you have python in your environment, simply run the the file name by
  using the command "python graphTest.py" or on Linux "python3 graphTest.py"
