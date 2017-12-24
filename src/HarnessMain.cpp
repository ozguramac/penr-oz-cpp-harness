//============================================================================
// Name        : harnessMain.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ContextSwitchMeasurement.h"
#include <iostream>
using namespace std;

int main() {

	cout << "Hello World! " << endl;

	//Test Context switch measurement
	cout << "Number of thread switches in about one second was " << getCtxSwitchMeasurement() << endl;

	return 0;
}
