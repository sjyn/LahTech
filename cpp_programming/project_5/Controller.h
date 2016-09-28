#pragma once
#include <vector>
#include <memory>
#include <atomic>
#include "Constants.h"
#include "Person.h"
#include "Balloon.h"
#include "TerribleBalloon.h"
#include "Anvil.h"
#include "ScoreKeeper.h"
#include "Instructions.h"

class Controller
{
public:
	//pass in width and height of console window, plus default speed
	Controller(int width, int height, SPEED speed=MEDIUM);
	~Controller(void);

	//render the scene
	void draw();
	void createBalloon();
	void createTBalloon();
	void createAnvil();
	bool swapTerrible();
	

	//change game speed.
	inline void setSpeed(SPEED speed){mSpeed = speed;};

	//current state intro or run
	inline void setControllerState(CONTROLLER_STATE state){mControllerState = state;};

	//TODO you will have to change this function when you replace
	//myBalloons with a polymorphic vector
	//test to see if cosmo has run into an object
	COLLISION hasCollidedWithCosmo(Moveable& moveable);

	inline void changeCosmoDirection(DIRECTION dir){cosmo.setDirection(dir);};

private:
	bool terribleONLY;
	//reset it all
	void initialize();

	//fills screen buffer with blanks
	void clearScreen();

	//draw scores if needed
	void renderScoresToScreenbuffer();
	
	SPEED mSpeed;		//game speed
	//number of game ticks before  created
	int iTimeBetweenBalloonCreation;
	sizeofScreenBuffer myScreenBufferSize;	//width and height of consolewindow
	int ballonsCreated;
	//holds entire consolewindow screen, 
	//usually 80 chars wide by 24 lines long
	std::vector<std::string> myScreenVector;

	//all of our balloons not polymorphic though
	std::vector<std::unique_ptr <Moveable> > myBalloons;

	//cosmo the person
	Person cosmo;

	//for writing instructions
	Instructions myInstructions;

	//max distance between center of squares for a collision to have occured
	//its corner of one object bounding box touching corner of another
	double mCollisionDistance;

	ScoreKeeper scorekeeper;
	CONTROLLER_STATE mControllerState;
};

