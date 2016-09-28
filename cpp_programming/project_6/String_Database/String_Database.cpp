#include "../includes/String_Database.h"
#include <iostream>

String_Database::String_Database() {

}

String_Database::~String_Database(){

}

void String_Database::add(std::string &myString) {
	std::lock_guard<std::mutex> lock(mutex);
	bool hasSeenBefore = false;
	String_Data comp(myString);
	for (myStringsIter = myStrings.begin(); myStringsIter != myStrings.end(); myStringsIter++) {
		//String_Data dater = *myStringsIter;
		if ((*myStringsIter) == comp) {
			//We have alredy seen this string.
			printf("%s\n","Equal");
			hasSeenBefore = true;
			(*myStringsIter).increment();
			break;
		}
		else {
			printf("%s\n", "neq");
		}
	}
	if (!hasSeenBefore)
		myStrings.push_back(comp);
	//std::lock_guard<std::mutex> unlock(mutex);
}

int String_Database::getCount(std::string &myString) {
	std::lock_guard<std::mutex> lock(mutex);
	String_Data comp(myString);
	for (myStringsIter = myStrings.begin(); myStringsIter != myStrings.end(); myStringsIter++) {
		if (*myStringsIter == comp) {
			//std::lock_guard<std::mutex> unlock(mutex);
			return (*myStringsIter).getCount();
		}
	}
	//std::lock_guard<std::mutex> unlock(mutex);
	return 0;
}

void String_Database::clear(){
	std::lock_guard<std::mutex> lock(mutex);
	myStrings.clear();
	//std::lock_guard<std::mutex> unlock(mutex)
}

bool String_Database::load(DataStore *myDataStore) {
	std::lock_guard<std::mutex> lock(mutex);
	return myDataStore->load(myStrings);
	//std::lock_guard<std::mutex> unlock(mutex);
}

bool String_Database::save(DataStore *myDataStore) {
	std::lock_guard<std::mutex> lock(mutex);
	return myDataStore->save(myStrings);
	//std::lock_guard<std::mutex> unlock(mutex);
}

void String_Database::printme() {
	for (myStringsIter = myStrings.begin(); myStringsIter != myStrings.end(); myStringsIter++) {
		std::cout << (*myStringsIter).serialize() << std::endl;
	}
}