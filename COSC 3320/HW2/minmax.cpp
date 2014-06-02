#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

void straightforward(double num_array[]); //iterative min/max function
void divideandconquer(int x, int y); //recursive min/max function

double num_array[10001];
double min, max;
int n = 0;

int main(int argc, char *argv[])
{
    steady_clock::time_point start, end;
    duration<double> time_span;
    int choice = 0;
    string filename = argv[1];
    ifstream fin;
    fin.open(filename.c_str());

    if (fin.fail())
    {
        cout << "error with input file" << endl;
        return -1;
    }

    double temp = 0;
    for (int i = 0; i < 10001; i++)
        num_array[i] = 0;
    while (fin >> temp)
    {
        num_array[n] = temp;
        n++;
        cout << n << endl;
    }
    while (choice != 3)
    {
        cout << "Enter 1 for straightforward algorithm, 2 for divide & conquer, 3 to exit." << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            start = steady_clock::now();
            straightforward(num_array);
            end = steady_clock::now();
            time_span = duration_cast<duration<double>>(end - start);
            cout << "time taken: " << time_span.count() << endl;
            break;
        case 2:
            start = steady_clock::now();
            divideandconquer(0, n-1);
            end = steady_clock::now();
            cout << "minimum = " << min << endl;
            cout << "maximum = " << max << endl;
            time_span = duration_cast<duration<double>>(end - start);
            cout << "time taken: " << time_span.count() << endl;

            break;
        case 3:
            break;

        }
    }
    return 0;
}

void straightforward(double num_array[])
{
    double min = num_array[0], max = num_array[0];

    for (int i = 0; i < n; i++)
    {
        if (min > num_array[i])
            min = num_array[i];
        if (max < num_array[i])
            max = num_array[i];
    }
    cout << "min = " << min << endl;
    cout << "max = " << max << endl;
}
//credit for the following algorithm goes to Y. Jayarathina Madharasan, I've made a couple of improvements (preventing integer overflow for example) and
//applied it in a way that fits my program, but the basis of his algorithm is still here. I could not think of another or more effecient way to solve this problem using divide and conquer.
void divideandconquer(int x, int y) //recursive divide & conquer algorithm to find max and min
{
    double min2, max2;
    int midpoint;

    if (x == y)
    {
        min = num_array[x];
        max = num_array[y];
    }
    else
    {
        if (x == y - 1) //ideal case, pair next to each other for comparison
        {
            if (num_array[x] < num_array[y])
            {
                min = num_array[x];
                max = num_array[y];
            }
            else
            {
                max = num_array[x];
                min = num_array[y];
            }
        }
        else
        {
            midpoint = x/2 + y/2; //splitting subproblem by factor of two
            divideandconquer(x, midpoint); //recursive call on lower half
            min2 = min;
            max2 = max;
            divideandconquer(midpoint + 1, y); //recursive call on upper half
            if (min > min2)
                min = min2;
            if (max < max2)
                max = max2;
        }
    }
    return;
}