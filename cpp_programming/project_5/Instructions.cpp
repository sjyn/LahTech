#include "Instructions.h"


Instructions::Instructions(sizeofScreenBuffer myScreenBufferSize,location myLoc, SPEED spd, DIRECTION dir ):Moveable(myScreenBufferSize,myLoc,spd, dir)
{
}


Instructions::~Instructions(void)
{
}


bool Instructions::draw(std::vector<std::string> &myScreenVector){			//pure virtual, abstract base class, MUST BE DEFINED BY DERIVED CLASSES	
	
	myScreenVector[3  ].replace(1,61,"                Inflated Balloons are a clock ticking menace!");
	myScreenVector[4  ].replace(1,69,"       Silent, creepy, ever closer. Better to proactively pop them on");
	myScreenVector[5  ].replace(1,64,"       your terms than to have them sneak up on you and explode.");
	myScreenVector[8  ].replace(1,60,"            \\\\\\\\\\|/////                                  ___");                               
	myScreenVector[9  ].replace(1,61,"             \\\\|~ ~|//                                  //\\ \\");
	myScreenVector[10  ].replace(1,62,"              \\|O O|/                                  | \\/  |");
	myScreenVector[11  ].replace(1,61,"               | ^ |   <-Cosmo              Balloon->   \\   /");
	myScreenVector[12  ].replace(1,60,"               | v |                                     \\ /");
	myScreenVector[13 ].replace(1,59,"               |___| o--   <-Needle                       |") ;                                            
	myScreenVector[14 ].replace(1,59,"               __|__/                                     |");                                             
	myScreenVector[15 ].replace(1,59,"               \\ |                                         ");                
	myScreenVector[16 ].replace(1,59,"                o|                                         ");
	myScreenVector[17 ].replace(1,59,"                _|_                                        ");
	myScreenVector[20 ].replace(1,59,"                     arrow keys (or K M H P) = movement    ");
	myScreenVector[21 ].replace(1,63,"              B,b = Begin   R,r = Reset  I,i = Help  X,x = Exit");
	
	//myScreenVector[18 ].replace(1,59,"                      <- or -> (K or B) = left/right       ");
	//myScreenVector[19 ].replace(1,61,"                      Down arrow t      = pause defenselessly");
	//myScreenVector[20 ].replace(1,63,"                      Up arrow          = take aggressive stand");
	return false;
}
