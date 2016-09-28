#pragma once
#include <string>

namespace KP_FileReaderClass{
	class FileReader
	{
	public:
		FileReader();
		virtual ~FileReader();

		//anathema! access to internal data
		int getFileContents(const std::string filename, std::string &contents);
	private:
		int ReadTheWholeFile(const std::string &filename);
		std::string		filecontents;
	};
}

