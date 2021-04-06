#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

// *** QuickSort from Teacher *** //
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
	double pivot = arr[high];
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

void print_array(double arr[], int size) {
	int i;
	for (i=0; i < size; i++)
		cout << arr[i] <<  " ";
	cout << endl;
}

// *** END QUICKSORT ** //

/* Splitting the string x,y into integers x and y by finding ',' and using it as a 
reference to split the string*/
void splitting(string buffer, string delimiter, double *x, double *y)
{-
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
    getline(infile, line);
    //Accounting for x,y
    return linenum - 1;
}

double sum(double arr[], int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

double mean(double arr[], int size)
{
    double aSum = sum(arr, size);
    return aSum / size;
}

double* median(double x[], double y[], long length) {
    double medianX = 0;
    double medianY = 0;

    for (int i = 0; i < length - 1; i++) {
        if ((length - 1) % 2 != 0) { // check whether the array is odd
            medianX = x[(length - 1) / 2]; // if odd -> median is the middle value
            medianY = y[(length - 1) / 2];
        }
        else { // if the array length is even
            medianX = x[(length - 1) / 2]; // get the first middle value
            medianX = (medianX + x[length / 2 - 1]) / 2; // add with the second middle value and divided by 2.

            medianY = y[(length - 1) / 2];
            medianY = (medianY + y[length / 2 - 1]) / 2;
        }
    }
    cout << "median_x = " << medianX << " - median_y = " << medianY << endl; // print out the median
    double medians[2] = { medianX, medianY }; // store in array to return the value

    return medians; 
}

double var(double arr[], int size){
    double aMean = mean(arr, size);
    double se[size]; // abb. for squared error, NOT standard error
    for(int i=0; i<size; i++){
        se[i] = (arr[i] - aMean) * (arr[i] - aMean);
    }
    return sum(se, size) / (size - 1);
}

// double mode(double arr[], int size){
//     double out = 0;
//     for(int i=0; i<size; i++){
//         int count = 0;
//         for(int j = 0; j<size; j++) {
//             if(arr[j] == arr[i]){
                
//             }
//         }
//     }
// }

int main(int argc, char *argv[])
{
    // Checks if the program is executed in the correct format
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
    }

    int arrSize = sizeof(x) / sizeof(y[0]);
    cout << "size: " << arrSize << endl;
    cout << "sum: " << sum(x, arrSize) << endl;
    cout << "mean: " << mean(x, arrSize) << endl;

    
    double* medians;
    medians = median(x, y, arrSize);




    // quickSort(x, 0, size);
    // quickSort(y, 0, size);

    // cout << "Median of x is " << x[medianpos] << endl << "Median of y is " << y[medianpos] << endl;

    print_array(x, arrSize);
    quickSort(x, 0, arrSize);
    print_array(x, arrSize);

    infile.close();
    return 0;
}