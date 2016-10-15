#include "cell.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>

using namespace std;

#define INBITITERATIONS 10000
#define DELTA 1
#define TAUMAX 10
#define TAUINCREMENT 1
#define TAUMIN 10

void checkCurrentCell(cell const *& currentCell_ptr); //check current cell is legit

//not a great function
void checkOFile(ofstream& outputFile){
	//Open and define filesteam at once
	if (outputFile.good()){
		cout << "outfile opened successfully" << endl;
		//outputFile << "writing to my new file!" << endl;
	}
	else
	{
		cerr << "outfile not opened successfully. Terminator." << endl;
	}
}

//generate a bit with probs. corresponding to delta.
int genBit(double delta){
	int bit;
	double p0 = 0.5*(1 + delta);
	double p1 = 0.5*(1 - delta);
	float randN = ((float)rand() / (float)(RAND_MAX));

	if (randN < p0){
		bit = 0;
	}
	else{
		bit = 1;
	}
	
	return bit;
}

//change the current cell pointer from say A0 to A1.
void changeCell(int& bit, const cell (&myCells_ptr)[6], cell const *& currentCell_ptr){
	//cout << "changeCell" << endl;
	//cout << sizeof(myCells_ptr) << endl;
	for (int i = 0; i < sizeof(myCells_ptr) / sizeof(cell); i++){
		if ((myCells_ptr + i)->getState() == currentCell_ptr->getState() && (int)(myCells_ptr + i)->getBit() == bit){
			currentCell_ptr = myCells_ptr + i;
			break;
		}
	}
}

//demon interacts with the input bit for tau*sojournTimeEdge timesteps. (move around the six states)
void demonInteract(cell const *& currentCell_ptr, const double & tau, const double & sojournTimeEdge){
	//cout << "in ";
	//currentCell_ptr->printInfo();

	for (double i = 0; i < tau*sojournTimeEdge; i++){
		//cout << "i = " << i << endl;

		//generate random number, tell thing to go left, right, stay.
		double num = ((double)rand() / (double)(RAND_MAX));

		if (num <= 1 - (currentCell_ptr->getPLeft() + currentCell_ptr->getPRight())){
			//stay still
		}
		else if (num <= 1 - currentCell_ptr->getPRight()){
			//move left. pStill < num < pLeft + pStill
			currentCell_ptr --;
		}
		else{
			//move right. pLeft + PStill < num < 1
			currentCell_ptr ++;
		}
	
		//currentCell_ptr->printInfo();
		//cout << endl;

		checkCurrentCell(currentCell_ptr);

	}
	//cout << "out ";
	//currentCell_ptr->printInfo();
}

//take sojournTime on one of the edge states.
int spinFlywheel(unsigned int nBits, const cell(&myCells_ptr)[6], cell const *& currentCell_ptr, double tau, double delta, double sojournTime){
	int netRotation = 0; //sum deltaChi

	//loop over the input bit stream
	for (unsigned int iteration = 1; iteration <= nBits; iteration++){

		//generate bit with probabilities p0 and p1, input delta, output a bit
		int bit = genBit(delta);

		//change starting cell depending on input bit
		changeCell(bit, myCells_ptr, currentCell_ptr);

		//loop over timesteps (interaction with demon)
		demonInteract(currentCell_ptr, tau, sojournTime);

		int deltaChi;
		deltaChi = currentCell_ptr->getBit() - bit;
		//cout << deltaChi << endl;

		netRotation += deltaChi;
	}

	return netRotation;

}

int main(){

	const cell a0('A', 0, 0, 0.1f);
	const cell b0('B', 0, 0.1f, 0.1f);
	const cell c0('C', 0, 0.1f, 0.1f);
	const cell a1('A', 1, 0.1f, 0.1f);
	const cell b1('B', 1, 0.1f, 0.1f);
	const cell c1('C', 1, 0.1f, 0);

	ofstream phiFile("phi.txt");
	checkOFile(phiFile);
	ofstream tauFile("tau.txt");
	checkOFile(tauFile);
	ofstream deltaFile("delta.txt");
	checkOFile(deltaFile);

	const cell myCells_ptr[6]{a0, b0, c0, a1, b1, c1};
	cell const * currentCell_ptr = myCells_ptr;

	float sojournTime[6];
	for (int i = 0; i < 6; i++){
		sojournTime[i] = 1 / (myCells_ptr[i].getPLeft() + myCells_ptr[i].getPRight()); //Is this formula correct?
	}

	srand((unsigned int)time(NULL)); //seed. Only needs to be seeded each time program runs. rand() produces a sequence of randome numbers

	//repeat with different TAU (plot the whole graph)
	for (double tau = TAUMIN; tau <= TAUMAX; tau += TAUINCREMENT){

		cout << "tau = " << tau << endl;
		tauFile << tau << endl;

		for (double delta = -1.0; delta <= DELTA; delta += 0.1){

			cout << "delta = " << delta << endl;
			deltaFile << delta << endl;

			int netRotation = spinFlywheel(INBITITERATIONS, myCells_ptr, currentCell_ptr, tau, delta, sojournTime[0]);

			//int netRotation = 0; //sum deltaChi

			////loop over the input bit stream
			//for (int iteration = 1; iteration <= INBITITERATIONS; iteration++){

			//	//generate bit with probabilities p0 and p1, input delta, output a bit
			//	int bit = genBit();

			//	//change starting cell depending on input bit
			//	changeCell(bit, myCells_ptr, currentCell_ptr);

			//	//loop over timesteps (interaction with demon)
			//	demonInteract(currentCell_ptr, tau, sojournTime[0]);

			//	int deltaChi;
			//	deltaChi = currentCell_ptr->getBit() - bit;
			//	//cout << deltaChi << endl;

			//	netRotation += deltaChi;
			//}

			cout << netRotation << endl;
			cout << (float)netRotation / INBITITERATIONS << endl;
			cout << "-----" << endl;

			phiFile << (float)netRotation / INBITITERATIONS << endl;
		}
	}

	return 0;
}