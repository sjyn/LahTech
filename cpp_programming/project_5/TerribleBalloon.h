#pragma once
#include "moveable.h"
#include "Balloon.h"

class TerribleBalloon :
	public Balloon
{
public:
	TerribleBalloon(sizeofScreenBuffer myScreenBufferSize,location myLoc, int iHowLongBeforeFall, SPEED spd=NO_SPD, DIRECTION dir=DOWN);
	virtual ~TerribleBalloon(void);
	
	//returns true if its time to delete
	virtual bool draw(std::vector<std::string> &myScreenVector);	

    private:
	//Construtor sets this to 0 
	int iHowLongBeforeFall,totalScreenFrames, speedFrames;
	bool shouldFall;
	bool bWingFlap;
	
};