#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

void straightforward(double num_array[]); //iterative min/max function
void divideandconquer(int x, int y, double min, double max); //recursive min/max function

double num_array[10001];
double minimum, maximum;
int n = 0;

/*class timer 
{
    private:
        long begTime;
    public:
        void start() 
        {
            begTime = (long) clock();
        }

        long elapsedTime() 
        {
            return (((long) clock() - begTime) / CLOCKS_PER_SEC);
        }
};*/

int main(int argc, char *argv[])
{


    int choice = 0;
    //timer timer_obj;
    string filename = argv[1];
    ifstream fin;
    fin.open(filename.c_str());

    if(fin.fail())
    {
        cout << "error with input file" << endl;
        return -1;
    }

    double temp = 0;
    for(int i = 0; i < 10001; i++)
        num_array[i] = 0;
    while(fin >> temp)
    {
        fin >> temp;
        num_array[n] = temp;
        n++;
    }
    while(choice != 3)
    {
    	cout << "Enter 1 for straightforward algorithm, 2 for divide & conquer, 3 to exit." << endl;
    	cin >> choice;
    	switch(choice)
    	{
    		case 1:
                //start = clock();
    			straightforward(num_array);
                //end = clock();
                //t = difftime(start,end)/CLOCKS_PER_SEC;
                //cout << "time elapsed: " << t << endl;
    			break;
    		case 2:
                //timer_obj.start();
                minimum = num_array[0];
                maximum = num_array[0];
    			divideandconquer(0, 1, minimum, maximum);
                cout << "minimum = " << minimum << endl;
                cout << "maximum = " << maximum << endl;
                //cout << "time elapsed: " << timer_obj.elapsedTime() << endl;
    			break;
    		case 3:
    			break;

    	}
    }
    return 0;
}

void straightforward(double num_array[])
{
    if(n == 0)
        return;

    double min = num_array[0], max = num_array[0];

    for(int i = 0; num_array[i] > n; i++)
    {
        if(min > num_array[i])
            min = num_array[i];
        if(max < num_array[i])
            max = num_array[i];
    }
    cout << "minimum = " << min << endl;
    cout << "maximum = " << max << endl;
}

void divideandconquer(int x, int y, double min, double max) //recursive divide & conquer algorithm to find max and min
{
    if(n == 0)
        return;
    if(x == y)
        return;
    if(x == y-1) //base case: if x and y are next to each other, compare
    {
        if(num_array[x] < num_array[y])
        {
            minimum = num_array[x];
            maximum = num_array[y];
            
        }
        else if (num_array[x] > num_array[y])
        {
            maximum = num_array[x];
            minimum = num_array[y];
        }
        else
        {
            maximum = num_array[x];
            minimum = num_array[y];
        }
        max = maximum;
        min = minimum;
    }
    else
    {
        int midpoint = (x+y)/2; //splitting subproblem by factor of two
        cout << midpoint << " midpoint" << endl;
        double min2 = min, max2 = max;
        divideandconquer(x, midpoint, min, max); //recursive call on lower half
        divideandconquer(midpoint+1, y, min2, max2); //recursive call on upper half
        if(min > min2)
            min = min2;
        if(max < max2)
            max = max2;
        minimum = min;
        maximum = max;
        return;
    }
}
