#ifndef CELL_H

class cell{
private:
	int bit; //set in construction to only be 1 or 0.
	char state;
	float pLeft, pRright;
public:
	//cell(){};
	cell(char state, int bit, float pL, float pR);
	~cell(){};

	void printInfo() const;
	//void fillCell(); use pointer instead
	float getPLeft() const;
	float getPRight() const;
	int getBit() const;
	char getState() const;

};

#endif