#pragma once
#include <vector>
#include <string>

namespace KP_StringParserClass{

	using ::std::string;
	using ::std::vector;

	class StringParserClass
	{
	public:
		StringParserClass(void);
		virtual ~StringParserClass(void);

		//indicates the last error the library experienced
		//resets error on completion, indicates a global variable that holds
		//error state
		int getLastError();

		//these are the start tag and the end tags that we want to find,
		//presumably the data of interest is between them
		bool setTags(const char *pStartTag, const char *pEndTag);

		//going to search thru pDataToSearchThru, looking for info bracketed by
		//pStartTag and pEndTag, will add that data to myStrings
		bool getDataBetweenTags(char *pDataToSearchThru, vector<string> &myVector);

	private:
		void cleanup();
		//pStart points to where we want to search in array
		bool findTag(char *pTagToLookFor, char *&pStart, char *&pEnd);

		char	*pStartTag;
		char	*pEndTag;
		bool	areTagsSet;
		int		lastError;
	};
}


