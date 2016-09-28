#pragma once
#include <atomic>
#include <thread>
#include "Runnable.h"

class ThreadUserInput : public Runnable
{
	public:
		char getInput(); 
	protected:
		void run(); 
	private:
		std::mutex instance_lock;
		char mChar;
};
