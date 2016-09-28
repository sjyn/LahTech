#include "Balloon.h"
#include <iostream>
Balloon::Balloon(sizeofScreenBuffer myScreenBufferSize,location myLoc,int iHowLongBeforeFall, SPEED spd, DIRECTION dir ):Moveable(myScreenBufferSize,myLoc,spd, dir)
{
	setSpeed(spd);
	setCollidable(true);
	setDirection(DOWN);
	setPointsIfCosmoWins(1);
	setPointsIfMoveableWins(1);
	setCollidedState(NO);
	totalScreenFrames = 0;
	speedFrames = 0;
	this->iHowLongBeforeFall = iHowLongBeforeFall;
	this->shouldFall = false;	
}

Balloon::~Balloon(void)
{
}

//returns true if its time to delete this balloon
bool Balloon::draw(std::vector<std::string> &myScreenVector){			//pure virtual, abstract base class, MUST BE DEFINED BY DERIVED CLASSES	
	int x=(myLoc.x);
	int y=(myLoc.y);

	if (totalScreenFrames < iHowLongBeforeFall) {
		//not ready to fall just yet
		totalScreenFrames++;
	}
	else{
		shouldFall = true;
	}
	if (shouldFall){
		if (speedFrames < spd) {
			//not falling yet
			speedFrames++;
		}
		else {
			//Fall then wait for the next time to fall
			speedFrames = 0;
			myLoc.y++;
		}
		//totalScreenFrames = 0;
	}
	
	bool bDeleteMe = false;
	if( (y>24) ) //Item is off the screen
		return true;
	
	switch (col) {

	case COSMO_POPPED:			
		if ((y)<24)   myScreenVector[y   ].replace( x,BALLOON_WIDTH,"       ");
		if ((y+1)<24) myScreenVector[y+1 ].replace( x,BALLOON_WIDTH,"    |  ");
		if ((y+2)<24) myScreenVector[y+2 ].replace( x,BALLOON_WIDTH,"  \\   /");
		if ((y+3)<24) myScreenVector[y+3 ].replace( x,BALLOON_WIDTH," - pop-");
		if ((y+4)<24) myScreenVector[y+4 ].replace( x,BALLOON_WIDTH,"  /   \\");
		if ((y+5)<24) myScreenVector[y+5 ].replace( x,BALLOON_WIDTH,"    |  ");
		if ((y+6)<24) myScreenVector[y+6 ].replace( x,BALLOON_WIDTH,"       ");
		setCollidable(false);
		bDeleteMe = true;
		break;
	case BALLOON_CLOBBERED_COSMO:
		if ((y)<24) myScreenVector[y   ].replace( x,BALLOON_WIDTH,"   *   ");
		if ((y+1)<24) myScreenVector[y+1 ].replace( x,BALLOON_WIDTH," *   * ");
		if ((y+2)<24) myScreenVector[y+2 ].replace( x,BALLOON_WIDTH,"* * * *");
		if ((y+3)<24) myScreenVector[y+3 ].replace( x,BALLOON_WIDTH,"*BOOM *");
		if ((y+4)<24) myScreenVector[y+4 ].replace( x,BALLOON_WIDTH,"* * * *");
		if ((y+5)<24) myScreenVector[y+5 ].replace( x,BALLOON_WIDTH," *   * ");
		if ((y+6)<24) myScreenVector[y+6 ].replace( x,BALLOON_WIDTH,"   *   ");
		setCollidable(false);
		bDeleteMe = true;
		break;
	case NO:
		if ((y)<24) myScreenVector[y   ].replace( x,BALLOON_WIDTH,"  ___  ");
		if ((y+1)<24) myScreenVector[y+1 ].replace( x,BALLOON_WIDTH," //\\ \\ ");
		if ((y+2)<24) myScreenVector[y+2 ].replace( x,BALLOON_WIDTH,"| \\/  |");
		if ((y+3)<24) myScreenVector[y+3 ].replace( x,BALLOON_WIDTH," \\   / ");
		if ((y+4)<24) myScreenVector[y+4 ].replace( x,BALLOON_WIDTH,"  \\ /  ");
		if ((y+5)<24) myScreenVector[y+5 ].replace( x,BALLOON_WIDTH,"   |   ");
		if ((y+6)<24) myScreenVector[y+6 ].replace( x,BALLOON_WIDTH,"   |   ");
		bDeleteMe = false;
		break;

	}

	return bDeleteMe;
}