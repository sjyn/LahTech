#include "Person.h"


	Person::Person(sizeofScreenBuffer myScreenBufferSize,location myLoc, SPEED spd, DIRECTION dir ):Moveable(myScreenBufferSize,myLoc, spd, dir),bLegChangePosition(false)
{

}


Person::~Person(void)
{
}

//always return false since person never deleted
bool Person::draw(std::vector<std::string> &myScreenVector){			//pure virtual, abstract base class, MUST BE DEFINED BY DERIVED CLASSES	
	int x=(myLoc.x);
	int y=(myLoc.y);
		
	bLegChangePosition = !bLegChangePosition;
	switch(dir){
	case LEFT:
		myScreenVector[14].replace( x,PERSON_WIDTH,"   \\\\\\\\|//// ");
		myScreenVector[15].replace( x,PERSON_WIDTH,"    |~ ////  ");
		myScreenVector[16].replace( x,PERSON_WIDTH,"    |O  //   ");
		myScreenVector[17].replace( x,PERSON_WIDTH,"   <    |    ");
		myScreenVector[18].replace( x,PERSON_WIDTH,"    |_/ |    ");
		myScreenVector[19].replace( x,PERSON_WIDTH,"--o |__/     ");
		myScreenVector[20].replace( x,PERSON_WIDTH,"   \\__|      ");
		myScreenVector[21].replace( x,PERSON_WIDTH,"      |      ");
		if (bLegChangePosition){
			myScreenVector[22].replace( x,PERSON_WIDTH,"     /|      ");
			myScreenVector[23].replace( x,PERSON_WIDTH,"   \\/_|      ");
		}
		else{
			myScreenVector[22].replace( x,PERSON_WIDTH,"      |      ");
			myScreenVector[23].replace( x,PERSON_WIDTH,"    \\||      ");
		}
		if (myLoc.x>0)
			myLoc.x--;
		break;
	case RIGHT:
		myScreenVector[14].replace( x,PERSON_WIDTH," \\\\\\\\|////   ");
		myScreenVector[15].replace( x,PERSON_WIDTH,"  \\\\\\\\ ~|    ");
		myScreenVector[16].replace( x,PERSON_WIDTH,"   \\\\  O|    ");
		myScreenVector[17].replace( x,PERSON_WIDTH,"    |    >   ");
		myScreenVector[18].replace( x,PERSON_WIDTH,"    | \\_|    ");
		myScreenVector[19].replace( x,PERSON_WIDTH,"     \\__| o--");
		myScreenVector[20].replace( x,PERSON_WIDTH,"      |__/   ");
		myScreenVector[21].replace( x,PERSON_WIDTH,"      |      ");
		if (bLegChangePosition){
			myScreenVector[22].replace( x,PERSON_WIDTH,"      |\\     ");
			myScreenVector[23].replace( x,PERSON_WIDTH,"      |_\\/    ");
		}
		else{
			myScreenVector[22].replace( x,PERSON_WIDTH,"      |     ");
			myScreenVector[23].replace( x,PERSON_WIDTH,"      ||/    ");
		}
		if (myLoc.x<DEFAULT_WIDTH-PERSON_WIDTH-1) //Minus one to correct for vector indexing
			myLoc.x++;
		break;
	case UP:
		myScreenVector[14].replace( x,PERSON_WIDTH," \\\\\\\\\\|///// ");
		myScreenVector[15].replace( x,PERSON_WIDTH,"  \\\\|\\ /|//  ");
		myScreenVector[16].replace( x,PERSON_WIDTH,"   \\|O O|/   ");
		myScreenVector[17].replace( x,PERSON_WIDTH,"    | ^ |    ");
		myScreenVector[18].replace( x,PERSON_WIDTH," \\  | - |  / ");
		myScreenVector[19].replace( x,PERSON_WIDTH,"  o |___| o  ");
		myScreenVector[20].replace( x,PERSON_WIDTH,"   \\__|__/   ");
		myScreenVector[21].replace( x,PERSON_WIDTH,"      |     ");
		myScreenVector[22].replace( x,PERSON_WIDTH,"      |     ");
		myScreenVector[23].replace( x,PERSON_WIDTH,"     _|_     ");
		break;
	case NO_DIR:
	case DOWN:
		myScreenVector[14].replace( x,PERSON_WIDTH," \\\\\\\\\\|///// ");
		myScreenVector[15].replace( x,PERSON_WIDTH,"  \\\\|~ ~|//  ");
		myScreenVector[16].replace( x,PERSON_WIDTH,"   \\|O O|/   ");
		myScreenVector[17].replace( x,PERSON_WIDTH,"    | ^ |    ");
		myScreenVector[18].replace( x,PERSON_WIDTH,"    | v |    ");
		myScreenVector[19].replace( x,PERSON_WIDTH,"    |___|    ");
		myScreenVector[20].replace( x,PERSON_WIDTH,"    __|__    ");
		myScreenVector[21].replace( x,PERSON_WIDTH,"    \\ | /    ");
		myScreenVector[22].replace( x,PERSON_WIDTH,"     0|0     ");
		myScreenVector[23].replace( x,PERSON_WIDTH,"     _|_     ");
		break;
	}
	return false;
}
