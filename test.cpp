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

// *** QuickSort from Teacher *** //
void swap(double *a, double *b)
{
    double t = *a;
    *a = *b;
    *b = t;
}
/* This function takes last element as pivot, places
 * the pivot element at its correct position in sorted
 * array, and places all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right
 * of pivot */
int partition(double arr[], int low, int high)
{
    double pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
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
void quickSort(double arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
		at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void print_array(double arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// *** END QUICKSORT ** //

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
void fillarray(ifstream &infile, double *x, double *y, int size)
{
    char delimiter[] = ",";
    string buffer;
    for (int i = 0; i < size; i++)
    {
        infile >> buffer;
        try
        {
            splitting(buffer, delimiter, &x[i], &y[i]);
        }
        catch (const invalid_argument)
        {
            i--;
            continue;
        }
    }
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
{    double aSum = sum(arr, size);
    return aSum / size;
}

void median(double x[], double y[], int size) {
    double medianX = 0;
    double medianY = 0;

    for (int i = 0; i < size - 1; i++) {
        if ((size - 1) % 2 != 0) { 
            medianX = x[(size - 1) / 2]; 
            medianY = y[(size - 1) / 2];
        }
        else { 
            medianX = x[(size - 1) / 2]; 
            medianX = (medianX + x[size / 2 - 1]) / 2; 

            medianY = y[(size - 1) / 2];
            medianY = (medianY + y[size / 2 - 1]) / 2;
        }
    }
    cout << "median_x = " << medianX << " - median_y = " << medianY << endl; 
    
};

double var(double arr[], int size)
{
    double arrM = mean(arr, size);
    double VAR = 0; // abb. for squared error, NOT standard error
    for (int i = 0; i < size; i++)
    {
        VAR += (arr[i] - arrM) * (arr[i] - arrM);
    }
    return VAR / (size - 1);
}

double sd(double arr[], int size)
{
    return sqrt(var(arr, size));
}

double meanAbsoluteDeviation(double arr[], int size)
{
    double sum;
    double aMean = mean(arr, size);
    for (int i = 0; i < size; i++)
    {
        sum += fabs(arr[i] - aMean);
    }

    return sum / size;
}

void mode(double arr[], int size)
{
    // arr[] is assumed to be sorted already
    double mode = 0;
    int modeCount = 0;
    int curVal = 0;
    int curCount = 0;
    int n_modes = 1;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == curVal)
        {
            curCount++;
        }
        else
        {
            if (curCount > modeCount)
            {
                mode = curVal;
                modeCount = curCount;
                n_modes = 1;
            }
            else if (curCount == modeCount)
            {
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
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == curVal)
        {
            curCount++;
        }
        else
        {
            if (curCount == modeCount)
            {
                modes[modecounter] = curVal;
                modecounter++;
            }
            curVal = arr[i];
            curCount = 1;
        }
    }
    // cout << "Number of modes: " << n_modes << endl;
    // cout << "Number of occurences: " << modeCount << endl;
    for (int i = 0; i < n_modes; i++)
    {
        cout << "mode " << i + 1 << " is " << modes[i] << endl;
    }
    // cout << modes[0] << endl;
    return;
}

double cov(double x[], double y[], int size)
{
    double resprod = 0;
    double meanX = mean(x, size);
    double meanY = mean(y, size);
    for (int i = 0; i < size; i++)
    {
        resprod += (x[i] - meanX) * (y[i] - meanY);
    }
    return resprod / (size - 1);
}

class Statistics
{
private:
    int n;
    double *arrx = new double(n);
    double *arry = new double(n);

public:
    ~Statistics() { ; }
    Statistics(int size, double x[], double y[])
    {
        n = size;
        arrx = x;
        arry = y;
    }

    double getx(int n) { return arrx[n]; }
    double gety(int n) { return arry[n]; }

    double getMean(string col)
    {
        double aSum;
        if (col == "x")
        {
            aSum = sum(arrx, n);
        }
        else if (col == "y")
        {
            aSum = sum(arry, n);
        }
        else
            return 0;
        return aSum / n;
    }
    double getVarX()
    {
        double aMean = mean(arrx, n);
        double se[n]; // abb. for squared error, NOT standard error
        for (int i = 0; i < n; i++)
        {
            se[i] = (arrx[i] - aMean) * (arrx[i] - aMean);
        }
        return sum(se, n) / (n - 1);
    }
    double getVarY()
    {
        double aMean = mean(arry, n);
        double se[n]; // abb. for squared error, NOT standard error
        for (int i = 0; i < n; i++)
        {
            se[i] = (arry[i] - aMean) * (arry[i] - aMean);
        }
        return sum(se, n) / (n - 1);
    }

    double meanAbsoluteDeviationX()
    {
        double sum;
        double aMean = mean(arrx, n);
        for (int i = 0; i < n; i++)
        {
            sum += fabs(arrx[i] - aMean);
        }
        return sum / n;
    }
    double meanAbsoluteDeviationY()
    {
        double sum;
        double aMean = mean(arry, n);
        for (int i = 0; i < n; i++)
        {
            sum += fabs(arry[i] - aMean);
        }
        return sum / n;
    }
};

double skewness(double arr[], int size)
{
    double sum;
    double aMean = mean(arr, size);
    double s = sd(arr, size);

    for (int i = 0; i < size; i++)
    {
        sum += pow(((arr[i] - aMean) / s), 3);
    }
    return sum / size;
}


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
    fillarray(infile, x, y, size);

    int arrSize = sizeof(x) / sizeof(y[0]);

    // TESTING OUTPUT
    cout << "size: " << arrSize << endl;
    cout << "sum: " << sum(x, arrSize) << endl;
    //cout << "median:" << endl;
    median(x, y, arrSize);
    //cout << "mean: " << mean(x, arrSize) << endl;
    cout << "MAD: " << meanAbsoluteDeviation(x, arrSize) << endl;
    cout << "Skewness: " << skewness(x, arrSize) << endl;

    string buffer;
    char delimiter[] = ",";
   
    double xMean = mean(x, size);
    double yMean = mean(y, size);
    double xResiduals[size], yResiduals[size];
    double covariance = cov(x, y, size);
    double varX = var(x, size);
    double varY = var(y, size);
    double sdX = sqrt(varX);
    double sdY = sqrt(varY);
    double corr = covariance / (sdX * sdY);
    cout << "covariance: " << covariance << endl;
    cout << "sd(X): " << sdX << endl;
    cout << "sd(Y): " << sdY << endl;
    cout << "pearson correlation: " << corr << endl;
    quickSort(x, 0, size);
    quickSort(y, 0, size);

    Statistics stat(size, x, y);
    cout << stat.getx(5) << endl;
    cout << stat.gety(5) << endl;
    cout << stat.getMean("x") << endl;
    cout << stat.getVarX() << endl;
    cout << stat.getVarY() << endl;

    mode(x, size);
    mode(y, size);

   


    infile.close();
    return 0;
}




