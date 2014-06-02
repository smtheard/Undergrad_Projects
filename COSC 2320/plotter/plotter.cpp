#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstring>

using namespace std;

void output(string s, string op);

int main(int argc, char *argv[])
{	int n = 10000;
	long result = n*n + n*n + n*n + n;
	cout << result;
	stringstream ss; 
	ss<< "n,value"<<endl;
	string results = ss.str();
	output(results, "");
	int selection = 0;
	while(selection != 3)
	{
		cout << "1 for union, 2 for intersection 3 to exit " << endl;
		cin >> selection;
		if(selection == 1)
		{
			for(long n = 1; n<=17000; n+=n)
			{
				long result = n*n + n*n + n;
				ss<<n<<","<< result << endl;
				results = ss.str();
				ss.str("");
				output(results, "append");
			}
		}
		else if(selection == 2)
		{
			for(long n = 1; n<=17000; n+=n)
			{
				long result = n*n + n*n + n*n + n;
				ss<<n<<","<< result << endl;
				results = ss.str();
				ss.str("");
				output(results, "append");
			}
		}
	}
	return 99;
}

void output(string s, string op)
{
	ofstream fout;
	string s2 = "graph.csv";
	if(op == "append")
		fout.open(s2.c_str(), ios::out | ios::app);
	else
		fout.open(s2.c_str());
	fout << s << endl;
	fout.close();
	return;
}