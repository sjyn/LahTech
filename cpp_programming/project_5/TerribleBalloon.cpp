#include "Moveable.h"
#include "Balloon.h"
#include "TerribleBalloon.h"

TerribleBalloon::TerribleBalloon(sizeofScreenBuffer myScreenBufferSize,location myLoc,int iHowLongBeforeFall, SPEED spd, DIRECTION dir):Balloon(myScreenBufferSize,myLoc, iHowLongBeforeFall,spd, dir),bWingFlap(false)
{
	bCollidable=IS_BALLOON;
	setSpeed(spd);
	setCollidedState(NO);
	setCollidable(true);
	setDirection(dir);
	setPointsIfMoveableWins(1);
	setPointsIfCosmoWins(1);
	totalScreenFrames = 0;
	speedFrames = 0;
	this->shouldFall = false;
	this->iHowLongBeforeFall=iHowLongBeforeFall;
}

TerribleBalloon::~TerribleBalloon(void)
{
}

//returns true if its time to delete this balloon
bool TerribleBalloon::draw(std::vector<std::string> &myScreenVector){			//pure virtual, abstract base class, MUST BE DEFINED BY DERIVED CLASSES	
	int x=(myLoc.x);
	bWingFlap = !bWingFlap;
	if (getCollidable()) {
		if (totalScreenFrames < iHowLongBeforeFall) {
			//not ready to fall just yet
			totalScreenFrames++;
		}
		else {
			shouldFall = true;
		}
		if (shouldFall) {
			if (speedFrames < spd) {
				//not falling yet
				speedFrames++;
			}
			else {
				//Fall then wait for the next time to fall
				speedFrames = 0;
				myLoc.y++;
			}

		}
	}
	else{
		if (shouldFall) {
			if (speedFrames < spd) {
				//not falling yet
				speedFrames++;
			}
			else {
				//Fall then wait for the next time to fall
				speedFrames = 0;
				switch(dir){
				case UP:
					myLoc.y--;
					break;
				case DOWN:
					myLoc.y++;
					break;
				case LEFT:
					myLoc.x--;
					break;
				case RIGHT:
					myLoc.x++;
					break;
				}

			}
		}

	}
	int y = (myLoc.y);
	bool bDeleteMe = false;
	if( (y>=22) || (y<=0) ) //Item is off the screen
		return true;
	if ( (x<=0) || (x>=74) ) //Bee has hit the left or right edge
		return true;

	if(bCollidable){
		switch (col){
		case COSMO_POPPED:
			if ((y)<24)   myScreenVector[y   ].replace( x,BALLOON_WIDTH,"       ");
			if ((y+1)<24) myScreenVector[y+1 ].replace( x,BALLOON_WIDTH,"    |  ");
			if ((y+2)<24) myScreenVector[y+2 ].replace( x,BALLOON_WIDTH,"  \\   /");
			if ((y+3)<24) myScreenVector[y+3 ].replace( x,BALLOON_WIDTH," - pop-");
			if ((y+4)<24) myScreenVector[y+4 ].replace( x,BALLOON_WIDTH,"  /   \\");
			if ((y+5)<24) myScreenVector[y+5 ].replace( x,BALLOON_WIDTH,"    |  ");
			if ((y+6)<24) myScreenVector[y+6 ].replace( x,BALLOON_WIDTH,"       ");
			setCollidable(false);
			setDirection(LEFT);
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
			setDirection(RIGHT);
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
	}

	else if(!bCollidable){
		int changeDir = rand()%90;
		switch(dir){
		case LEFT:
			if ((y+1)<24) myScreenVector[y+1].replace( x,BEE_WIDTH,"%000-" );
			if ((y+2)<24) myScreenVector[y+2].replace( x,BEE_WIDTH,"     " );

			if (bWingFlap){
				if ((y)<24) myScreenVector[y].replace( x,BEE_WIDTH," ()) ");				
			}
			else{
				if ((y)<24) myScreenVector[y].replace( x,BEE_WIDTH," ()  ");				
			}
			if (changeDir==0)
				dir=DOWN;
			if (changeDir==2)
				dir=UP;
			break;
		case RIGHT:
			if ((y+1)<24) myScreenVector[y+1].replace( x,BEE_WIDTH,"-000%");
			if ((y+2)<24) myScreenVector[y+2].replace( x,BEE_WIDTH,"     ");			
			if (bWingFlap){
				if ((y)<24) myScreenVector[y  ].replace( x,BEE_WIDTH,"  (()" );
			}
			else{
				if ((y)<24) myScreenVector[y  ].replace( x,BEE_WIDTH,"   ()" );
			}
			if (changeDir==0)
				dir=UP;
			if (changeDir==2)
				dir=DOWN;
			break;
		case UP:
			if ((y+1)<24) myScreenVector[y  ].replace( x,BEE_WIDTH,"  %  " );
			if ((y+2)<24) myScreenVector[y+1].replace( x,BEE_WIDTH," =0= ");
			if ((y+3)<24) myScreenVector[y+2].replace( x,BEE_WIDTH,"  |  " );
			if (changeDir==0)
				dir=LEFT;
			if (changeDir==2)
				dir=RIGHT;
			break;
		case DOWN:
			if ((y+1)<24) myScreenVector[y  ].replace( x,BEE_WIDTH,"  |  " );
			if ((y+2)<24) myScreenVector[y+1].replace( x,BEE_WIDTH," =0= ");
			if ((y+3)<24) myScreenVector[y+2].replace( x,BEE_WIDTH,"  %  " );
			if (changeDir==0)
				dir=LEFT;
			if (changeDir==2)
				dir=RIGHT;
			break;
		}
	}

	return bDeleteMe;
}