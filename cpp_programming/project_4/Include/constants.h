/*
 * constants.h
 *
 *  Created on: Oct 7, 2013
 *      Author: lynn
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

const int 	SUCCEEDED			 				=  0;
const int 	USER_CHOSE_TO_EXIT 					= SUCCEEDED-1;
const int 	COULD_NOT_OPEN_FILE					= SUCCEEDED-2;
const int 	COULD_NOT_CLOSE_FILE				= SUCCEEDED-3;
const int 	COULD_NOT_READ_FILE_INTO_CONTAINER	= SUCCEEDED-4;
const int 	COULD_NOT_WRITE_CONTAINER_TO_FILE	= SUCCEEDED-5;
const int 	FILE_NOT_OPEN						= SUCCEEDED-6;

//possible error conditions from parser
const int	ERROR_NO_ERROR 						= SUCCEEDED -21;
const int	ERROR_TAGS_NULL						= SUCCEEDED -22;
const int	ERROR_DATA_NULL						= SUCCEEDED -23;

const double		UNINITIALIZED					= -1.0;

const std::string	TEST_FILE_NAME			= "..\\include\\Textfile.txt";
const std::string 	OUTPUTFILENAME	 		= "..\\include\\OutputStrings.txt";
const std::string 	EXITCHAR 				= "X";
const std::string	ENTER_FN_OR_X			= "Please enter a filename or an X to eXit";

const char 	START_TAG[]							="<to>";
const char  END_TAG[]							="</to>";


//enum whichTag{START_TAG,END_TAG};

#endif /* CONSTANTS_H_ */
