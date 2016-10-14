#include "cell.h"

#include <iostream>
#include <stdio.h>

using namespace std;

cell::cell(char InState, bool InBit, float pL, float pR){
	bit = InBit;
	state = InState;
	pLeft = pL;
	pRright = pR;
}
void cell::printInfo(){
	cout << state << bit << " " << pLeft << " " << pRright << endl;
}
float cell::getPLeft(){
	return pLeft;
}
float cell::getPRight(){
	return pRright;
}
