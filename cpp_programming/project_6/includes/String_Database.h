#pragma once
#include <string>
#include <vector>
#include <mutex>
#include "..\includes\String_Data.h"
#include "..\includes\DataStore_File.h"

class String_Database
{
private:
	std::mutex mutex;
	std::vector<String_Data> myStrings;
	std::vector<String_Data>::iterator  myStringsIter;
	
public:
	String_Database(void);
	~String_Database(void);

	//add or increment the count for myString
	void add(std::string &myString);

	//get number of times myString has been seen
	//sometimes you need getters
	int getCount(std::string &myString);

	//clear the vector
	void clear();

	//load from datastore
	bool load(DataStore  *myDataStore);

	//save to datastore
	bool save(DataStore *myDataStore);

	void printme();
};

