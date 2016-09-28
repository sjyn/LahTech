#pragma once
#include <vector>
#include <string>
#include "constants.h"

class Moveable
{
public:
	//size of screen, mylocation (x,y)  etc.
	Moveable(sizeofScreenBuffer myScreenBufferSize, location myLoc, SPEED spd, DIRECTION dir, int pointsIfMoveableWins=1, int pointsIfCosmoWins=1);
	void setDirection(DIRECTION dir);
	void setSpeed(SPEED spd); 
	
	inline int getX(){return myLoc.x;};
	inline int getY(){return myLoc.y;};
	inline void setCollidable(bool bCollide){this->bCollidable = bCollide;};
	inline bool getCollidable(){return bCollidable;};
	inline void setPointsIfMoveableWins(int movePoints){this->pointsIfMoveableWins = movePoints;};
	inline void setPointsIfCosmoWins(int movePoints){this->pointsIfCosmoWins = movePoints;};
	inline int getPointsIfCosmoWins(){return this->pointsIfCosmoWins;};
	inline int getPointsIfMoveableWins(){return this->pointsIfMoveableWins;};
	inline DIRECTION getDir(){return dir;};
	void setCollidedState(COLLISION col);
	inline void setLocation(location myLoc){this->myLoc = myLoc;};
	
	//returns true if its time to delete
	virtual	bool draw(std::vector<std::string> &myScreenVector)=0;			//pure virtual, abstract base class, MUST BE DEFINED BY DERIVED CLASSES
	virtual ~Moveable(void);
protected:
	location myLoc; 
	sizeofScreenBuffer myScreenBufferSize;
	DIRECTION dir;
	SPEED spd;
	int iTimeBetweenMovements;	
	COLLISION col;
	int pointsIfMoveableWins;
	int pointsIfCosmoWins;
	
	//use this to limit the number of times a collision can be counted
	//for instance when a terrible balloon turns into a Bee dont count collisions afterward
	bool bCollidable;
	
};
