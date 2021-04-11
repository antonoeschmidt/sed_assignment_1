#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

void swap(double* a, double* b) {
	double t = *a;
	*a = *b;
	*b = t;
}

/* This function takes last element as pivot, places
 * the pivot element at its correct position in sorted
 * array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right
 * of pivot */
int partition (double arr[], int low, int high) {
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high- 1; j++) {
		if (arr[j] <= pivot) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/* The main function that implements QuickSort
 * arr[] --> Array to be sorted,
 * low --> Starting index,
 * high --> Ending index
 */
void quickSort(double arr[], int low, int high) {
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void print_array(int arr[], int size) {
	int i;
	for (i=0; i < size; i++)
		cout << arr[i] <<  " ";
	cout << endl;
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
    double linenum = 0;
    string line;
    while (!infile.eof())
    {
        getline(infile, line);
        ++linenum;
    }
    infile.clear();
    infile.seekg(0);
    //Skip the "x,y" line
    getline(infile,line);
    //Accounting for x,y
    return linenum - 1;
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

double var(double arr[], int size){
    // array is array of residuals, NOT of actual observations
    double se[size]; // abb. for squared error, NOT standard error
    for(int i=0; i<size; i++){
        se[i] = arr[i] * arr[i];
    }
    return sum(se) / (size - 1);
}

void mode(double arr[], int size){
    // arr[] is assumed to be sorted already    
    double mode = 0;
    int modeCount = 0;
    int curVal = 0;
    int curCount = 0;
    int n_modes = 1; 
    for(int i=0; i<size; i++){
        if(arr[i] == curVal){
            curCount++;
        }
        else{
            if(curCount > modeCount){   
                mode = curVal;
                modeCount = curCount;
                n_modes = 1;
            }
            else if(curCount == modeCount){
                n_modes++;
            }
            curVal = arr[i];
            curCount = 1;
        }
    }
    double modes[n_modes];
    int modecounter = 0;
    curVal = 0;
    curCount = 0;
    for(int i=0; i<size; i++){
        if(arr[i] == curVal){
            curCount++;
        }
        else{
            if(curCount == modeCount){
                modes[modecounter] = curVal;
                modecounter++;
            }
            curVal = arr[i];
            curCount = 1;
        }
    } 
    // cout << "Number of modes: " << n_modes << endl;
    // cout << "Number of occurences: " << modeCount << endl;
    for(int i=0; i<n_modes; i++){
        cout << "mode " << i+1 << " is " << modes[i] << endl;
    }
    // cout << modes[0] << endl;
    return; 
}

double cov(double resx[], double resy[], int size){
    double resprod = 0;
    for(int i=0; i<size; i++){
        resprod += resx[i] * resy[i]; 
    }
    return resprod / (size - 1);
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
        // cout << y[i] << endl;
    }

    // double a[] = {5, 10, 15};
    // int arrSize = sizeof(a) / sizeof(a[0]);
    // cout << "size: " << arrSize << endl;
    // cout << "sum: " << sum(a) << endl;
    // cout << "mean: " << mean(a, arrSize) << endl;
    double xMean = mean(x, size);
    double yMean = mean(y, size);
    double xResiduals[size], yResiduals[size];
    for(int i=0; i<size; i++){
        xResiduals[i] = x[i] - xMean;
        yResiduals[i] = y[i] - yMean;
    }
    quickSort(x, 0, size);
    quickSort(y, 0, size);

    int medianpos = ceil(size/2);

    cout << "Median of x is " << x[medianpos] << endl << "Median of y is " << y[medianpos] << endl;
    // double x_mode = mode(x, size);
    // double y_mode = mode(y, size);
    // cout << "x has mode: " << x_mode << "\ny has mode: " << y_mode << endl; 
    mode(x, size);
    mode(y, size);
    infile.close();
    return 0;
}