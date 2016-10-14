#include "cell.h"

#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

void printCells(cell* myCell_ptr);

int main(){

	cell a0('A', 0, 0, 0.6f);
	cell b0('B', 0, 0.4f, 0.6f);
	cell c0('C', 0, 0.4f, 0.6f);
	cell a1('A', 1, 0.4f, 0.6f);
	cell b1('B', 1, 0.4f, 0.6f);
	cell c1('C', 1, 0.4f, 0);

	//vector<cell> myVec{a0, b0};

	cell myCells_ptr[6]{ a0, b0, c0, a1, b1, c1 };
	cell* currentCell_ptr = myCells_ptr;

	srand(time(NULL)); //seed. Only needs to be seeded each time program runs. rand() produces a sequence of randome numbers

	//loop over tau timesteps
	currentCell_ptr->printInfo();
	cout << endl;

	int tau = 3;
	for (int i = 0; i < tau; i++){
		//generate random number, tell thing to go left, right, stay.
		float num = ( (float)rand() / (float)(RAND_MAX) );
		cout << num << endl;

		if(num < 1 - (currentCell_ptr->getPLeft() + currentCell_ptr->getPRight())){
			//stay still
		}
		else if (num < 1 - currentCell_ptr->getPRight()){
			//move left. pStill < num < pLeft + pStill
			currentCell_ptr--;
		}
		else{
			//move right. pLeft + PStill < num < 1
			currentCell_ptr++;
		}
		currentCell_ptr->printInfo();
		cout << endl;
	}

	return 0;
}
