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

// ***    Helper functions     *** //
// ------------------------------ //
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

// *** Descriptive Statistics *** //
// ------------------------------ //
double median(double arr[], int size)
{
    double median = 0;
    if ((size - 1) % 2 != 0)
    {
        median = arr[(size - 1) / 2];
    }
    else
    {
        median = arr[(size - 1) / 2];
        median = (median + arr[size / 2 - 1]) / 2;
    }
    return median;
};
double var(double arr[], int size)
{
    double arrM = mean(arr, size);
    double VAR = 0; 
    for (int i = 0; i < size; i++) // 
    {
        VAR += (arr[i] - arrM) * (arr[i] - arrM); // sum of squared residuals
    }
    return VAR / (size - 1); // divide by sample size minus one
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
    // initialize mode, the number of occurrences of mode (modeCount)
    // current value, current count and number of modes
    double mode = 0; 
    int modeCount = 0;
    int curVal = 0;
    int curCount = 0;
    int n_modes = 1;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == curVal) // the values are assumed to be sorted so if value is equal to current value current count goes up by one
        {
            curCount++;
        }
        else
        {
            if (curCount > modeCount) // if there are no more of current value check if count is highest obtained so far
            {
                mode = curVal; // change mode
                modeCount = curCount; // change modecount
                n_modes = 1; // this is the first value with this many occurrences, so # of modes is one
            }
            else if (curCount == modeCount) // if it's another with highest # of occurrences, we have another mode
            {
                n_modes++;
            }
            curVal = arr[i]; // change current value
            curCount = 1; // change current count
        }
    }
    double modes[n_modes]; // initialize modes to how many modes we have
    int modecounter = 0; // which number mode are we at?
    curVal = 0; // initialization of current value ..
    curCount = 0; // .. and current count
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == curVal) // count number of occurrences as before
        {
            curCount++;
        }
        else
        {
            if (curCount == modeCount) // add to modes if we have enough occurrences
            {
                modes[modecounter] = curVal;
                modecounter++;
            }
            curVal = arr[i]; // change current value ..
            curCount = 1; // .. and count
        }
    }
    for (int i = 0; i < n_modes; i++) // cout modes
    {
        if(i != 0 )
        {
            cout << ",";
        }
        cout << modes[i];
    }
    return;
}

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

double kurtosis(double arr[], int size){
    double sum; 
    double aMean = mean(arr, size);
    double s = sd(arr, size);
    for(int i = 0; i<size; i++){
        sum += pow((arr[i] - aMean) / s, 4);
    }
    return sum / size - 3; 
}

double fquartile(double arr[], int size)
{
    int n = size / 2;
    return median(arr, n);
}

// *** Inferential Statistics *** //
// ------------------------------ //
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

double corr(double x[], double y[], int size)
{
    return cov(x, y, size) / (sd(x, size) * sd(y, size));
}

void linreg(double x[], double y[], int size){
    double sdX = sd(x, size);
    double sdY = sd(y, size);
    double r = corr(x,y,size);
    double a = r * sdY / sdX;
    cout << "y = " << a << "x + " << mean(y, size) - a * mean(x, size) << endl;
    return;
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
    int const size = getlinenum(infile);
    //Putting data set into arrays
    double x[size];
    double y[size];
    fillarray(infile, x, y, size);

    int arrSize = sizeof(x) / sizeof(y[0]);

    //OUTPUT
    cout << "var_x=";
    formatoutput(var(x, arrSize));
    cout << " - " << "var_y=";
    formatoutput(var(y, arrSize));
    cout << endl;

    cout << "stdev_x=";
    formatoutput(sd(x, arrSize));
    cout << " - " << "stdev_y=";
    formatoutput(sd(y, arrSize));
    cout << endl;

    cout << "mad_x=";
    formatoutput(meanAbsoluteDeviation(x, arrSize));
    cout << " - " << "mad_y=";
    formatoutput(meanAbsoluteDeviation(y, arrSize));
    cout << endl;

    cout << "skew_x=";
    formatoutput(skewness(x, arrSize));
    cout << " - " << "skew_y=";
    formatoutput(skewness(y, arrSize));
    cout << endl;

    cout << "kurt_x=";
    formatoutput(kurtosis(x, arrSize));
    cout << " - " << "kurt_y=";
    formatoutput(kurtosis(y, arrSize));
    cout << endl;

    cout << "cov(x_y) =";
    formatoutput(cov(x, y, size));
    cout << endl;
    cout << "r(x_y) =";
    formatoutput(corr(x, y, size));
    cout << endl;
    linreg(x,y,arrSize);

    // sort
    quickSort(x, 0, size);
    quickSort(y, 0, size);

    cout << "median_x=";
    formatoutput(median(x, arrSize));
    cout << " - ";

    cout << "median_y=";
    formatoutput(median(y, arrSize));
    cout << endl;

    cout << "q1_x=";
    formatoutput(fquartile(x, size));
    cout << " - ";

    cout << "q1_y=";
    formatoutput(fquartile(y, size));
    cout << endl;

    cout << "mode_x={";
    mode(x, size);
    cout << "}" << " - ";

    cout << "mode_y={";
    mode(y, size);
    cout << "}" << endl;

    groupinfo();
    infile.close();
    return 0;
}
