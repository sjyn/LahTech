#pragma once
#include "moveable.h"
class Instructions :
	public Moveable
{
public:
	Instructions(sizeofScreenBuffer myScreenBufferSize,location myLoc,SPEED spd = NO_SPD, DIRECTION dir= NO_DIR );
	virtual ~Instructions(void);
	//returns true if its time to delete
	virtual bool draw(std::vector<std::string> &myScreenVector);	
private:
};

