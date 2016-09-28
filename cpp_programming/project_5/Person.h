#pragma once
#include "moveable.h"
class Person :
	public Moveable
{
public:
	Person(sizeofScreenBuffer myScreenBufferSize,location myLoc,SPEED spd=NO_SPD, DIRECTION dir=NO_DIR );
	virtual ~Person(void);

	//always return false since person never deleted
	virtual bool draw(std::vector<std::string> &myScreenVector);	

private:
	//determines if leg is out or in
	bool bLegChangePosition;
};

