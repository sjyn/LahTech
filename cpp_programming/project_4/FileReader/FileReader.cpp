#include <iostream>
#include <fstream>
#include "..\Include\FileReader.h"
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"
using namespace std;
using namespace KP_FileReaderClass;

namespace KP_FileReaderClass {
	/*
	FileReader()

	A default constructor for the FileReader class
	*/
	FileReader::FileReader() {
		filecontents = "";
	}

	/*
	~FileReader()

	A deconstructor for the FileReader class
	*/
	FileReader::~FileReader() {
		filecontents = "";
	}

	/*
	int getFileContents(const std::string filename, std::string &contents) 

	Reads in the file at filename and stores its contents into contents.

	@param	filename			The path to the file that will be read
	@param	&contents			The string into which the file contents will be stored
	@return	int					The corresponding status code for the method call
	*/
	int FileReader::getFileContents(const std::string filename, std::string &contents) {
		if (ReadTheWholeFile(filename) == SUCCEEDED) {
			contents = filecontents;
			return SUCCEEDED;
		}
		return COULD_NOT_READ_FILE_INTO_CONTAINER;
	}

	int FileReader::ReadTheWholeFile(const std::string &filename) {
		ifstream fstr(filename);
		if (fstr.is_open()) {
			string tmp;
			while (getline(fstr, tmp)) {
				filecontents += tmp + '\n';
			}
			fstr.close();
			if (fstr.is_open()) {
				return COULD_NOT_CLOSE_FILE;
			}
			return SUCCEEDED;
		}
		return FILE_NOT_OPEN;
	}

	string filecontents;
}
