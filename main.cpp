/*
 * main.cpp
 *
 *  Created on: Dec 21, 2012
 *      Author: alex
 */

#include <stdio.h>
#include <iostream>
#include "Testbench.h"
using namespace std;

int main(int argc, char ** argv) {

	Testbench tb("output.txt");
	tb.run();
	return 0;

}
