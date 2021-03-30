#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/* Splitting the string x,y into integers x and y by finding ',' and using it as a 
reference to split the string*/
void splitting(string buffer, string delimiter, double *x, double *y)
{
    int startpos = 0;
    int endpos = buffer.find(delimiter);
    
    *x = stoi(buffer.substr(startpos, endpos - startpos));
    if(endpos != -1)
    {
        startpos = endpos + delimiter.size();
    }
    *y = stoi(buffer.substr(startpos, endpos - startpos));
}

int getlinenum(ifstream &infile)
{
    double linenum = 0;
    string line;
    while(!infile.eof())
    {
        getline(infile, line);
        ++linenum;
    }
    infile.clear();
    infile.seekg(0);
    return linenum;
}

int main(int argc, char *argv[])
{
    //Checks if the program is executed in the correct format
    if(argc != 2)
    {
        cout << "Invalid amount of argument";
        return -1;
    }

    //Opening the file and checking if it's opened properly
    ifstream infile (argv[1]);
    if(!infile)
    {
        cerr << "Error opening file" << endl;
        return -1;
    }

    //Getting number of lines in file (to be used to create an array that fits the data)
    int size = getlinenum(infile);

    //Putting data set into arrays
    double x[size];
    double y[size];
    string buffer;
    for(int i = 0; i < size; i++)
    {
        infile >> buffer;
        char delimiter[] = ",";
        splitting(buffer, delimiter, &x[i], &y[i]);
    }

    infile.close();
    return 0;
}