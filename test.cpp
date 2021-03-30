#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* Splitting the string x,y into integers x and y by finding ',' and using it as a 
reference to split the string*/
void splitting(string buffer, string delimiter, int *x, int *y)
{
    int startpos = 0;
    int endpos = buffer.find(delimiter);

    *x = stoi(buffer.substr(startpos, endpos - startpos));
    if (endpos != -1)
    {
        startpos = endpos + delimiter.size();
    }
    *y = stoi(buffer.substr(startpos, endpos - startpos));
}

int main(int argc, char *argv[])
{
    //Checks if the program is executed in the correct format
    if (argc != 2)
    {
        cout << "Invalid amount of argument";
        return -1;
    }

    //Opening the file and checking if it's opened properly
    ifstream infile(argv[1]);
    if (!infile)
    {
        cerr << "Error opening file" << endl;
        return -1;
    }

    //Getting number of lines in file (to be used to create an array that fits the data)
    int linenum = 0;
    string line;
    while (!infile.eof())
    {
        getline(infile, line);
        ++linenum;
    }
    cout << linenum << endl;

    //returning to beginning of file
    infile.clear();
    infile.seekg(0);

    string buffer;
    char delimiter[] = ",";
    getline(infile, line);
    for (int i = 0; i < 3; i++)
    {
        infile >> buffer;
        int x;
        int y;
        cout << "buffer: " << buffer << endl;

        splitting(buffer, delimiter, &x, &y);
        cout << x << " " << y << endl;
    }

    infile.close();
    return 0;
}