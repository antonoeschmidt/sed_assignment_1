#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <iomanip>

using namespace std;


void groupinfo()
{
    cout << "ASSIGNMENT 1 GROUP 30" << endl;
    cout << "s3891411, s3891411@rmit.edu.vn, Jeppe Ekstrand Halkjaer Madsen" << endl;
    cout << "s3877375, s3877375@rmit.edu.vn, Le Pham Ngoc Hieu" << endl;
    cout << "s3775271, s3775271@rmit.edu.vn, Ramanaharan Ramcharan" << endl;
    cout << "s3892062, s3892062@rmit.edu.vn, Anton Ostergaard Schmidt" << endl;
}

void formatoutput(double output)
{
    cout << setprecision(5) << output;
}

/* Splitting the string x,y into integers x and y by finding ',' and using it as a 
reference to split the string*/
void splitting(string buffer, string delimiter, double *x, double *y)
{
    int startpos = 0;
    int endpos = buffer.find(delimiter);

    *x = stof(buffer.substr(startpos, endpos - startpos));
    if (endpos != -1)
    {
        startpos = endpos + delimiter.size();
    }

    *y = stof(buffer.substr(startpos, endpos - startpos));
}
int getlinenum(ifstream &infile)
{
    int linenum = 0;
    string line;
    char delimiter[] = ",";
    while (!infile.eof())
    {
        getline(infile, line);
        double x[sizeof(line)];
        double y[sizeof(line)];
        try
        {
        splitting(line, delimiter, x, y);
        }
        catch (const invalid_argument)
        {
            continue;
        }
        linenum++;
    }
    infile.clear();
    infile.seekg(0);
    return linenum;
}
double sum(double arr[])
{
    double sum = 0;
    for (int i = 0; i < sizeof(*arr); i++)
    {
        sum += arr[i];
    }
    return sum;
}

double mean(double arr[], int size)
{
    double aSum = sum(arr);
    return aSum / size;
}
void swap(double *xp, double *yp) 
{ 
	double temp = *xp; 
	*xp = *yp; 
	*yp = temp; 
} 

void insertionSort(double arr[], int n) 
{ 
	int i, key, j; 
	for (i = 1; i < n; i++) { 
		key = arr[i]; 
		j = i - 1; 

		/* Move elements of arr[0..i-1], that are 
		greater than key, to one position ahead 
		of their current position */
		while (j >= 0 && arr[j] > key) { 
			arr[j + 1] = arr[j]; 
			j = j - 1; 
		} 
		arr[j + 1] = key; 
	} 
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

    int size = getlinenum(infile);
    //Putting data set into arrays
    double x[size];
    double y[size];
    string buffer;
    char delimiter[] = ",";
    for (int i = 0; i < size; i++)
    {
        infile >> buffer;
        splitting(buffer, delimiter, &x[i], &y[i]);
        cout << x[i] << endl;
    }

    double a[] = {5, 10, 15};

    int arrSize = sizeof(a) / sizeof(a[0]);
    cout << "size: " << arrSize << endl;
    cout << "sum: " << sum(a) << endl;
    cout << "mean: " << mean(a, arrSize) << endl;
    insertionSort(x, size);
    insertionSort(y, size);

    int medianpos = ceil(size/2);

    cout << "Median of x is " << x[medianpos] << endl << "Median of y is " << y[medianpos] << endl;

    infile.close();
    return 0;
}