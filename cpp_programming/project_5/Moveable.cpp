#include "Moveable.h"


Moveable::Moveable(sizeofScreenBuffer myScreenBufferSize,location myLoc, SPEED spd, DIRECTION dir, int pointsIfMoveableWins, int pointsIfCosmoWins ):myScreenBufferSize(myScreenBufferSize),myLoc(myLoc),spd(spd)
{
}

void Moveable::setDirection(DIRECTION dir){
	this->dir = dir;
}
void Moveable::setSpeed(SPEED spd){
	this->spd = spd;
}
Moveable::~Moveable(void){

}

void Moveable::setCollidedState(COLLISION col)
{
	if(col!=NO)
		setCollidable(false);
	this->col = col;
}


