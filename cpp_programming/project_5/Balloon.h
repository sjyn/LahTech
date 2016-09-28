#pragma once
#include "moveable.h"

class Balloon :
	public Moveable
{
public:
	Balloon(sizeofScreenBuffer myScreenBufferSize,location myLoc, int iHowLongBeforeFall, SPEED spd=NO_SPD, DIRECTION dir=DOWN);
	virtual ~Balloon(void);

	//returns true if its time to delete
	virtual bool draw(std::vector<std::string> &myScreenVector);	

    private:
	//waits until falltime
	//speed count
	//waits around a while before it falls 
	int iHowLongBeforeFall;
protected:
	//waits until falltime
	//speed count
	int totalScreenFrames, speedFrames;
	bool shouldFall;
};

