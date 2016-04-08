
#pragma
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>


//#define CREATE

#ifndef CREATE
#include "delegates.hpp"
#endif
using namespace std;

const int N = 3000;

void createDelegates()
{
	ofstream delegateFile("delegates.hpp");
	delegateFile << "#pragma\n\
#include <vector>\n\
#include <functional>\n\
#include \"delegate.hpp\"\n\
std::vector<std::function<int()>> functorEvent;\n\
std::vector<Delegate*> fpEvent;\n";
	for (int i = 0; i < N; ++i)
	{

		delegateFile << "class Delegate" << i << ":public Delegate\n\
{\n\
	public: virtual int invoke() { return " << i << ";}\n\
} delegate" << i << ";\n";
	}

	delegateFile << "void create_event()\n{";
	for (int i = 0; i < 10; ++i)
	{
		delegateFile << "fpEvent.push_back(&delegate" << i << ");\n";
		delegateFile << "functorEvent.push_back(std::bind(&Delegate" << i << "::invoke, delegate" << i << "));\n";
	}
	delegateFile << "}";

}
#ifndef CREATE
void test_delegates() 
{
	clock_t t;
	t = clock();
	for (int j = 0; j < 5000; ++j)
		for (int i = 0; i < 10; ++i)
		{
			fpEvent[i]->invoke();
		}
	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

}

void test_functor()
{
	clock_t t;
	t = clock();
	for (int j = 0; j < 5000; ++j)
		for (int i = 0; i < 10; ++i)
		{
			functorEvent[i]();
		}
	t = clock() - t;
	printf("It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
}
#endif




int main()
{
#ifdef CREATE
	createDelegates();
#else
	create_event();
	test_delegates();
#endif
	getchar();
}
