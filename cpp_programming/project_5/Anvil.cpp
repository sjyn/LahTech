#include "Anvil.h"

Anvil::Anvil(sizeofScreenBuffer myScreenBufferSize,location myLoc,int iHowLongBeforeFall, SPEED spd, DIRECTION dir ):Moveable(myScreenBufferSize,myLoc,spd, dir)
{
	setSpeed(spd);
	setCollidable(true);
	setCollidedState(NO);
	setDirection(dir);
	setPointsIfMoveableWins(5);
	setPointsIfCosmoWins(0);
	totalScreenFrames = 0;
	speedFrames = 0;
	this->shouldFall = true;	
}

Anvil::~Anvil(void)
{
}

//returns true if its time to delete this anvil
bool Anvil::draw(std::vector<std::string> &myScreenVector){			//pure virtual, abstract base class, MUST BE DEFINED BY DERIVED CLASSES	
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
	if( (y>=24)) //Item is off the screen
		return true;
	switch (col) {
		//Need to use &myScreenVector here somehow -- Steven
		// I am fairly confident this is the correct implementation - Jacob

	case ANVIL_CLOBBERED_COSMO:
		if (y<24)     myScreenVector[y   ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		if ((y+1)<24) myScreenVector[y+1 ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		if ((y+2)<24) myScreenVector[y+2 ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		if ((y+3)<24) myScreenVector[y+3 ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		if ((y+4)<24) myScreenVector[y+4 ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		setCollidable(false);
		bDeleteMe = true;
		break;
	case COSMO_POPPED:
		if (y<24)     myScreenVector[y   ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		if ((y+1)<24) myScreenVector[y+1 ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		if ((y+2)<24) myScreenVector[y+2 ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		if ((y+3)<24) myScreenVector[y+3 ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		if ((y+4)<24) myScreenVector[y+4 ].replace( x,ANVIL_WIDTH,"  OUCH!!  ");
		setCollidable(false);
		bDeleteMe = true;
		break;
	case NO:
		if ((y)<24)   myScreenVector[y   ].replace( x,ANVIL_WIDTH,"    __    ");
		if ((y+1)<24) myScreenVector[y+1 ].replace( x,ANVIL_WIDTH,"   /__/\\  ");
		if ((y+2)<24) myScreenVector[y+2 ].replace( x,ANVIL_WIDTH,"  / 1 \\ \\ ");
		if ((y+3)<24) myScreenVector[y+3 ].replace( x,ANVIL_WIDTH," / TON \\ \\");
		if ((y+4)<24) myScreenVector[y+4 ].replace( x,ANVIL_WIDTH,"/_______\\/");
		bDeleteMe = false;
		break;
	}

	return bDeleteMe;
}