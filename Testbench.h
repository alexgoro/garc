/*
 * Testbench.h
 *
 *  Created on: Jan 1, 2013
 *      Author: alex
 */

#ifndef TESTBENCH_H_
#define TESTBENCH_H_

#include <iostream>
#include <fstream>
#include <NTL/ZZ.h>
#include <NTL/mat_ZZ.h>
#include <NTL/ZZ_p.h>
#include <NTL/mat_ZZ_p.h>
#include <sys/time.h>

using namespace std;
using namespace NTL;

class Testbench {

public:
	Testbench(const char * output_path);
	virtual ~Testbench();
	void run();

private:
	ofstream output;
	struct timeval start;
	struct timeval stop;
	mat_ZZ mZZ[8];
	mat_ZZ tmpZZ[8];
	mat_ZZ mZZp[8];
	mat_ZZ tmpZZp[8];

	void startTimer();
	void stopTimerAndPrintMilliSeconds(const char * operation, int mat_size, int int_size, int rounds);
	void initMatrix(mat_ZZ & m, int int_size);
	void initMatrix(mat_ZZ_p & m, int int_size);
};

#endif /* TESTBENCH_H_ */
