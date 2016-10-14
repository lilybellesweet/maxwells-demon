#ifndef CELL_H

class cell{
private:
	bool bit;
	char state;
	float pLeft, pRright;
	bool full;
public:
	cell(){};
	cell(char state, bool bit, float pL, float pR);
	~cell(){};

	void printInfo();
	//void fillCell(); use pointer instead
	float getPLeft();
	float getPRight();
};

#endif