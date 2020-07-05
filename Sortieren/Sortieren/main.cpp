#include <vector>
#include <deque>
#include <random>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>

#include "sortFuns.h"


using namespace std;
using namespace std::chrono;

#define HEADER_TEXT "Comparing different sorting algorithms based on sorting speed: shell sort, quick sort, std:sort\neach tested on array and container (vector, deque) with various element count. (10,1000,10000,100000)\n"
#define HEADER_LINE2 "Number of Elements;std:sort [ms];shell_sort [ms];quick_sort [ms]\n"
#define MAX_CONTAINERS 4

void format_TimeStamp(duration<double> ts, ofstream& fout)
{
	string temp = "";
	temp = to_string(duration_cast<milliseconds>(ts).count());
	temp.append(",");
	temp += to_string(duration_cast<microseconds>(ts).count());
	temp += to_string(duration_cast<nanoseconds>(ts).count());
	temp.append(";");

	fout.write(temp.c_str(), temp.length());
}


int main() {
	ofstream fout;
	auto rng = default_random_engine{};

	//fill deques and vectors

	vector<int> v[MAX_CONTAINERS];
	deque<int> d[MAX_CONTAINERS];
	vector<int>::iterator v_iters_fi[MAX_CONTAINERS];
	vector<int>::iterator v_iters_la[MAX_CONTAINERS];
	deque<int>::iterator d_iters_fi[MAX_CONTAINERS];
	deque<int>::iterator d_iters_la[MAX_CONTAINERS];
	int containersizes[MAX_CONTAINERS];

	for (int i = 0; i < MAX_CONTAINERS; i++)
	{
		if (i == 0)
		{
			containersizes[i] = 100;
		}
		else if (i > 0) {
			containersizes[i] = containersizes[i - 1] * 10;
		}
		for (int k = 0; k < containersizes[i]; ++k) {
			v[i].push_back(rand() % containersizes[i] + 1);
			d[i].push_back(rand() % containersizes[i] + 1);

			v_iters_fi[i] = v[i].begin();
			v_iters_la[i] = v[i].end();
			d_iters_fi[i] = d[i].begin();
			d_iters_la[i] = d[i].end();
		}
	}

	fout.open("data.csv");

	if (fout.fail()) {
		cerr << "Could not write .csv file." << endl;
		exit(2);
	}else if (fout.is_open())
	{

		fout.write(HEADER_TEXT,strlen(HEADER_TEXT));
		fout.write(HEADER_LINE2, strlen(HEADER_LINE2));
		for (int k = 0; k < 2; k++)
		{
			if (k == 0)
			{
				fout.write("Vector:\n", strlen("Vector:\n"));
			}
			else {
				fout.write("Deque:\n", strlen("Deque:\n"));
			}
			for (int j = 0; j < MAX_CONTAINERS; j++)
			{			
				string number="";
				if (k == 0)
				{
					number = to_string(v[j].size()); 
				}
				else {
					number = to_string(d[j].size());
				}
			
				number.append(";");
				fout.write(number.c_str(), number.length());

				//assign correct iterators first and last, for each array
				for (int i = 0; i < 3; i++)
				{
					//sort with every method
					switch (i)
					{
						case 0:
						{
							auto start = high_resolution_clock::now();
							if (k == 0)
							{
								sort(v_iters_fi[j], v_iters_la[j]);
							}
							else {
								sort(d_iters_fi[j], d_iters_la[j]);
							}
							auto end = high_resolution_clock::now();
							duration<double> diff = end - start;
							format_TimeStamp(diff, fout);
							if (k == 0)
							{
								shuffle(v_iters_fi[j], v_iters_la[j], rng);
							}
							else {
								shuffle(d_iters_fi[j], d_iters_la[j], rng);
							}
						}
						break;
						case 1:
						{
							auto start = high_resolution_clock::now();
							if (k == 0)
							{
								
								shell_sort(v_iters_fi[j], v_iters_la[j]);
							}
							else {
								shell_sort(d_iters_fi[j], d_iters_la[j]);
							}
							auto end = high_resolution_clock::now();
							duration<double> diff = end - start;
							format_TimeStamp(diff, fout);
							if (k == 0)
							{
								shuffle(v_iters_fi[j], v_iters_la[j], rng);
							}
							else {
								shuffle(d_iters_fi[j], d_iters_la[j], rng);
							}
						}
						break;
						case 2:
						{
							auto start = high_resolution_clock::now();
							if (k == 0)
							{
								quick_sort(v_iters_fi[j], v_iters_la[j]);
							}
							else {
								quick_sort(d_iters_fi[j], d_iters_la[j]);
							}
							auto end = high_resolution_clock::now();
							duration<double> diff = end - start;
							format_TimeStamp(diff, fout);
							if (k == 0)
							{
								shuffle(v_iters_fi[j], v_iters_la[j], rng);
							}
							else {
								shuffle(d_iters_fi[j], d_iters_la[j], rng);
							}
						}
						break;


					}

				}
				fout.write("\n", strlen("\n"));

			}

			fout.write("\n", strlen("\n"));

		}
		
	
	}

	fout.close();


    return 0;
}
