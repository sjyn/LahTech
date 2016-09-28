

#include <sstream>
#include <time.h>
#include <mutex>
#include <Windows.h>
#include <conio.h>
#include "ThreadUserInput.h"

void ThreadUserInput::run()  
{ 
	while (!m_stop) 
	{ 
		//see if user wants to go anywhere
		char val = _getch_nolock();
		{   
			//scoped to gurantee mutex unlock
			std::lock_guard<std::mutex> guard(instance_lock);
			mChar = val;
		}
	}
}

char ThreadUserInput::getInput(){   
		//scoped to gurantee mutex unlock
		std::lock_guard<std::mutex> guard(instance_lock);
		char userChar = mChar;
		mChar = '\0';
		return userChar;
}


