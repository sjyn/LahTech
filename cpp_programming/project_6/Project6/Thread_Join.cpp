#include "stdafx.h"
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <sstream>
#include "..\includes\String_Database.h"
#include "..\includes\DataStore_File.h"
#include "..\includes\Crypto_AES.h"

const int TOTAL_ADDED_PER_THREAD	=20;
const int TOTAL_THREADS				=20;
const std::string ENCRYPT_FILE1 = "Encryptfile1.txt";
const std::string ENCRYPT_FILE2 = "Encryptfile2.txt";

const std::string NO_ENCRYPT_FILE1 = "noEncryptfile1.txt";
const std::string NO_ENCRYPT_FILE2 = "noEncryptfile2.txt";

const int NUMBER_TIMES_TO_ADD_STRING = 20;

//I've provided some hints in the form of comments and commented out code
//use them if you wish

////global database object 
String_Database myGlobalCache;

//will add myString numbTimes to myGlobalCache
void ThreadFunc(int numbTimes, std::string myString) 
{
	cout << "called" << endl;
	for (int i = 0; i < numbTimes; i++)
	{
		myGlobalCache.add(myString);
	}
}

bool testSerialization(const std::string &MYFILE1, const std::string &MYFILE2, Crypto *pCrypto){
	DataStore_File myDataStore_File1(MYFILE1,pCrypto);

	myGlobalCache.save(&myDataStore_File1);

	//clear cache
	myGlobalCache.clear();

	//load it
	myGlobalCache.load(&myDataStore_File1);

	//save to a different file
	DataStore_File myDataStore_File2(MYFILE2,pCrypto);
	myGlobalCache.save(&myDataStore_File2);

	//I use my own objects here to compare the files
	return true;
}

void threadFunctionToRun(){

}

int main() 
{
	//I created and run a bunch(20) of threads that use ThreadFunc above 
	for (int i = 0; i < 20; i++)
	{
		if (i % 2 == 0){
			std::thread mThr(ThreadFunc, (i + 4) * 20, "Hello I Am String ");
			mThr.join();
		}
		else {
			std::thread mThr(ThreadFunc, (i + 4) * 20, "Hello I Am not String ");
			mThr.join();
		}
	}
	//Then I wait for all of them to finish so my program does not crash
 
	//Then I go through myGlobalCache and make sure that it holds the correct data
	//myGlobalCache.printme();

	//then I test that serialization works correctly
	//first without encryption, 
	testSerialization(NO_ENCRYPT_FILE1, NO_ENCRYPT_FILE2, 0);

	//runTest(NO_ENCRYPT_FILE1, NO_ENCRYPT_FILE2, 0);
	//then with
	Crypto_AES myCrypto("I Like Rollos   ");
	testSerialization(ENCRYPT_FILE1, ENCRYPT_FILE2, &myCrypto);
	return 0;
}