#include <string>
#include <sstream>
#include "..\Include\StringParserClass.h"
#include "..\Include\FileReader.h"
#include "..\Include\constants.h"
#include "..\Include\Debug_Help.h"

using namespace KP_StringParserClass;
using namespace std;

namespace KP_StringParserClass {
	/*
	StringParserClass(void)

	A default constuctor for the StringParserClass.
	*/
	StringParserClass::StringParserClass(void) {
		lastError = ERROR_NO_ERROR;
		areTagsSet = false;
		pStartTag = pEndTag = "";
	}

	/*
	~StringParserClass(void) 

	A deconstuctor for the StringParserClass.
	*/
	StringParserClass::~StringParserClass(void) {
		cleanup();
	}

	/*
	bool setTags(const char* pStartTag, const char* pEndTag)

	Sets the tags for the parser.

	@param *pStartTag		The starting tag to search for
	@param *pEndTag			The end tag to search for
	@return bool			True if the tags were valid and set correctly, false otherwise.
							If the tags are not set properly, lastError is set.
	*/
	bool StringParserClass::setTags(const char *pStartTag, const char *pEndTag) {
		if (pStartTag && pEndTag) {
			int i = 0;
			this->pStartTag = _strdup(pStartTag);
			this->pEndTag = _strdup(pEndTag);
			return (areTagsSet = true);
		}
		lastError = ERROR_TAGS_NULL;
		return (areTagsSet = false);
	}

	/*
	bool getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector)

	Gets the data between the pre determined tags. The data will be pushed into myVector.

	@param	*pDataToSearchThru			The data to be scanned
	@param	&myVector					The vector in which the data will be stored
	@return	bool						True if the data was successfully parsed, false otherwise.
										This method sets lastError.
	*/
	bool StringParserClass::getDataBetweenTags(char *pDataToSearchThru, std::vector<std::string> &myVector) {
		if (areTagsSet && *pDataToSearchThru) {
			while (true) {
				char* f = strstr(pDataToSearchThru, pStartTag);
				char* e = strstr(pDataToSearchThru, pEndTag);
				if (e && f) {
					int len = strlen(pDataToSearchThru) - strlen(f);
					len += strlen(pStartTag);
					pDataToSearchThru += len;
					len = strlen(pDataToSearchThru) - strlen(e);
					string s;
					int i = 0;
					while (i < len) {
						s += pDataToSearchThru[i];
						i++;
					}
					myVector.push_back(s);
					pDataToSearchThru += i;
					pDataToSearchThru += strlen(pEndTag);
				}
				else {
					return true;
				}
			}
		}
		else if (!areTagsSet) {
			lastError = ERROR_TAGS_NULL;
		}
		else if (pDataToSearchThru == NULL) {
			lastError = ERROR_DATA_NULL;
		}
		return false;
	}

	/*
	int getLastError()

	Return and resets the last error encountered by the parser.

	@return	int				The lastError encountered by the parser
	*/
	int StringParserClass::getLastError() {
		int tmp = lastError;
		lastError = ERROR_NO_ERROR;
		return tmp;
	}

	void StringParserClass::cleanup() {
		lastError = ERROR_NO_ERROR;
		areTagsSet = false;
	}

	bool StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {
		return false;
	}
}