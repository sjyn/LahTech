#include "../includes/DataStore_File.h"
#include <sstream>
#include <iostream>

DataStore_File::DataStore_File(std::string fileName, Crypto* crypto) :DataStore(crypto) {
	this->myFileName = fileName;
}

DataStore_File::~DataStore_File() {
	
}

bool DataStore_File::load(std::vector<String_Data> &myVector) {
	std::ifstream stream(myFileName);
	if (stream.is_open()) {
		std::string line = "";
		while (std::getline(stream, line)) {
			decrypt(line);
			std::istringstream iis(line);
			//get the first part of the line
			std::string words = "";
			std::getline(iis, words, ',');
			//get the count
			std::string sCount = "";
			std::getline(iis, sCount);
			int count = atoi(sCount.c_str());
			//store it in the vector
			String_Data dater(words, count);
			myVector.push_back(dater);
		}
		return true;
	}
	std::cout << "FALSe" << std::endl;
	return false;
}

bool DataStore_File::save(std::vector<String_Data> &myVector) {
	std::ofstream stream(myFileName);
	if (stream.is_open()) {
		std::vector<String_Data>::iterator it = myVector.begin();
		for (it; it != myVector.end(); ++it) {
			String_Data data = *it;
			std::string sered = data.serialize();
			encrypt(sered);
			stream << sered << std::endl;
		}
		return true;
	}
}