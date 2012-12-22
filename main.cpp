/*
 * main.cpp
 *
 *  Created on: Dec 21, 2012
 *      Author: alex
 */

#include <stdio.h>
#include <iostream.h>
#include "Eigen/Core"
#include "Eigen/Dense"
#include <gmpxx.h>
#include <sys/time.h>

using namespace std;
using namespace Eigen;

typedef Matrix<mpz_class, Dynamic, Dynamic> Matrix_mpz;

void startTimer(struct timeval * tv);
void stopTimerAndPrintMilliSeconds(struct timeval * tv, const char * str);
void initMatrix(Matrix_mpz * m);

int main(int argc, char ** argv) {
	struct timeval tv;

	Matrix_mpz m(256,256);
	initMatrix(&m);

	//measure addition:
	startTimer(&tv);
	m = m + m;
	stopTimerAndPrintMilliSeconds(&tv, "Addition Time (ms): ");

	//measure multiplication:
	startTimer(&tv);
	m = m * m;
	stopTimerAndPrintMilliSeconds(&tv, "Multiplication Time (ms): ");
}

void startTimer(struct timeval * tv) {
	gettimeofday(tv, NULL);
}

void stopTimerAndPrintMilliSeconds(struct timeval * tv, const char * str) {
	struct timeval tv2;
	int diff;
	gettimeofday(&tv2, NULL);
	diff = (tv2.tv_sec - tv->tv_sec)*1000000 + tv2.tv_usec - tv->tv_usec;
	cout << str << diff/1000 << endl << endl;
}

void initMatrix(Matrix_mpz * m) {
	for (int i = 0; i < m->rows(); i++) {
		for (int j = 0; j < m->cols(); j++) {
			mpz_class n;
			//n.set_str("42342342367657094385702394790342342429809089802348923824875093475908347509384", 10);
			n.set_str("a646aeffe54f64f6ea46a5e4f6ae54fae5640890980131fae3fea3f21eae1cc57576534980cceef", 16);
			(*m)(i,j) = n;
		}
	}
}
