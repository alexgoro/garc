/*
 * Testbench.cpp
 *
 *  Created on: Jan 1, 2013
 *      Author: alex
 */

#include "Testbench.h"

Testbench::Testbench(const char * output_path) {
	//open file:
	output.open (output_path);
	//initialize matrices:
	int j = 0;
	for (int i = 64; i <= 8192; i*=2) {
		mZZ[j] = mat_ZZ(INIT_SIZE, i, i);
		mZZp[j] = mat_ZZ(INIT_SIZE, i, i);
		tmpZZ[j] = mat_ZZ(INIT_SIZE, i, i);
		tmpZZp[j] = mat_ZZ(INIT_SIZE, i, i);
		j++;
	}
}

Testbench::~Testbench() {
	//close file:
	output.close();
}

void Testbench::run() {
	for (int i = 0; i < 8; i++) {
		for (int j = 64; j <= 8192; j*=2) {

			initMatrix(mZZ[i], j);
			initMatrix(mZZp[i], j);

			int loops = (j <= 1024 && mZZ[i].NumRows() <= 1024) ? 10 : 1;
			//add ZZ:
			startTimer();
			for (int k = 0; k < loops; k++) {
				add(tmpZZ[i], mZZ[i], mZZ[i]);
			}
			stopTimerAndPrintMilliSeconds("Add ZZ", mZZ[i].NumRows(), j, loops);
			//mul ZZ:
			startTimer();
			for (int k = 0; k < loops; k++) {
				mul(tmpZZ[i], mZZ[i], mZZ[i]);
			}
			stopTimerAndPrintMilliSeconds("Mul ZZ", mZZ[i].NumRows(), j, loops);
			//add ZZ_p:
			startTimer();
			for (int k = 0; k < loops; k++) {
				add(tmpZZp[i], mZZp[i], mZZp[i]);
			}
			stopTimerAndPrintMilliSeconds("Add ZZp", mZZ[i].NumRows(), j, loops);
			//mul ZZ_p:
			startTimer();
			for (int k = 0; k < loops; k++) {
				mul(tmpZZp[i], mZZp[i], mZZp[i]);
			}
			stopTimerAndPrintMilliSeconds("Mul ZZp", mZZ[i].NumRows(), j, loops);

			output << "****************************************************" << endl;
		}
	}
}

void Testbench::startTimer() {
	gettimeofday(&start, NULL);
}

void Testbench::stopTimerAndPrintMilliSeconds(const char * operation, int mat_size, int int_size, int rounds) {
	int64_t diff;
	gettimeofday(&stop, NULL);
	diff = (stop.tv_sec - start.tv_sec)*1000000 + stop.tv_usec - start.tv_usec;
	output << operation << " Mat Size: " << mat_size << " Int Size: " << int_size << ": " << diff/1000/rounds << "ms average" << endl << endl;
}

void Testbench::initMatrix(mat_ZZ & m, int int_size) {
	ZZ n;
	switch (int_size) {
		case 64:
			n = to_ZZ("9999999999999999995");
			break;
		case 128:
			n = to_ZZ("99993749237498237498237493299999999995");
			break;
		case 256:
			n = to_ZZ("99993749237498237498237493299999937129873912873981273129842343242399999799995");
			break;
		case 512:
			n = to_ZZ("9999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995");
			break;
		case 1024:
			n = to_ZZ("99993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995");
			break;
		case 2048:
			n = to_ZZ("9999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995");
			break;
		case 4096:
			n = to_ZZ("99993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995");
			break;
		case 8192:
			n = to_ZZ("9999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995");
			break;
		default:
			n = to_ZZ("9999999999999999995");
			break;
	}
	for (int i = 1; i <= m.NumRows(); i++) {
		for (int j = 1; j <= m.NumCols(); j++) {
			m(i,j) = n;
		}
	}
}

void Testbench::initMatrix(mat_ZZ_p & m, int int_size) {
	ZZ_p n;
	n.init(to_ZZ("56563749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995"));

	switch (int_size) {
		case 64:
			n = to_ZZ_p(to_ZZ("9999999999999999995"));
			break;
		case 128:
			n = to_ZZ_p(to_ZZ("99993749237498237498237493299999999995"));
			break;
		case 256:
			n = to_ZZ_p(to_ZZ("99993749237498237498237493299999937129873912873981273129842343242399999799995"));
			break;
		case 512:
			n = to_ZZ_p(to_ZZ("9999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995"));
			break;
		case 1024:
			n = to_ZZ_p(to_ZZ("99993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995"));
			break;
		case 2048:
			n = to_ZZ_p(to_ZZ("9999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995"));
			break;
		case 4096:
			n = to_ZZ_p(to_ZZ("99993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995"));
			break;
		case 8192:
			n = to_ZZ_p(to_ZZ("9999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995999937492374982374982374932999999371298739128739812731298423432423999997999959999374923749823749823749329999993712987391287398127312984234324239999979999599993749237498237498237493299999937129873912873981273129842343242399999799995"));
			break;
		default:
			n = to_ZZ_p(to_ZZ("9999999999999999995"));
			break;
	}
	for (int i = 1; i <= m.NumRows(); i++) {
		for (int j = 1; j <= m.NumCols(); j++) {
			m(i,j) = n;
		}
	}
}
