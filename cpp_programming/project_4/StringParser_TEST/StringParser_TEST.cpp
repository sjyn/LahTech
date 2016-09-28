//============================================================================
// Name        : Proj4_Test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "..\Include\FileReader.h"	//relative path, from PWD, go up one, then down into Include to find FileReader.h
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"
#include "..\Include\StringParserClass.h"

void outputvectorrow(std::string i) {
	std::cout << i << std::endl;
}
void foreach(std::vector<std::string> myVector) {
	std::for_each(myVector.begin(), myVector.end(), outputvectorrow);
}

using namespace std;
using namespace KP_FileReaderClass;
using namespace KP_StringParserClass;

int main() {
	string filename, contents = "";
	vector<string> vec;
	FileReader* reader = new FileReader();
	StringParserClass* parser = new StringParserClass();
	parser->setTags("<frome>", "</frome>");
	cout << "Enter filename" << endl;
	cin >> filename;
	reader->getFileContents(filename, contents);
	parser->getDataBetweenTags(&contents[0], vec);
	foreach(vec);
	delete reader;
	delete parser;
	return 0;
}