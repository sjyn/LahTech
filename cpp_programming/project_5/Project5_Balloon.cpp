#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include "controller.h"
#include "Instructions.h"
#include "constants.h"
#include "ThreadUserInput.h"

using namespace std;

BOOL gotoxy(const WORD x, const WORD y) {
	COORD xy;
	xy.X = x;
	xy.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

int main() {
	int width = DEFAULT_WIDTH;
	int height = DEFAULT_HEIGHT;
	bool continueGame=true;
	
	/* get the width and height of the console window*/
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if ( GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)){
		width = csbi.dwSize.X;
		height = csbi.srWindow.Bottom - csbi.srWindow.Top;
	}

	ThreadUserInput myInput;
	myInput.start();

	//set up controller
	Controller		myController(width,height,CONTROLLER_SPEED);

	//user input
	char myChar;

	//this is the game loop it runs until we close the app
	while (continueGame) {
		//go back to location 00 on screen and redraw
		gotoxy(0,0);

		//render the scene
		myController.draw();

		//see if user wants to go anywhere
		myChar = myInput.getInput();
		switch (myChar){
		case LEFT_ARROW:
			myController.changeCosmoDirection(LEFT);
			break;
		case RIGHT_ARROW:
			myController.changeCosmoDirection(RIGHT);
			break;
		case UP_ARROW:
			myController.changeCosmoDirection(UP);
			break;
		case DOWN_ARROW:
			myController.changeCosmoDirection(NO_DIR);
			break;
		case 'i':
		case 'I':
			myController.setControllerState(SHOW_INTRO);
			break;
		case 'r':
		case 'R':
			myController.setControllerState(RESET);
			break;
		case 'b':
		case 'B':
			myController.setControllerState(RUN);
			break;
		case 't':
		case 'T':
			myController.swapTerrible();
			myController.setControllerState(RUN);
			break;
		// End the game if X or x
		case 'x':
		case 'X':
			continueGame=false;
			myController.setControllerState(END);
			
		}
	}
	//std::cout<<"Stopping input"<<std::endl;
	//this kills the thread that inputs chars
	//Simulate key press
	keybd_event(VK_SPACE, 0x45, KEYEVENTF_EXTENDEDKEY | 0, 0);
	// Simulate a key release
	keybd_event(VK_SPACE, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
	myInput.stop();
	
	std::cout<<"Input stopped"<<std::endl;
	return 0; 

}
