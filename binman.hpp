/*******************************************************************************
* This file is pat of binman - Binary Managment library for C++
*
* If this file is in use in another, unrelated project, please see the github
* for binman for more information: https://github.com/ADBeta/binman
*
* This project is under GNU Public Licence.
* (c) 2023 ADBeta
* 
* Notes:
*
* 1 March 2023
* v0.0.1
*******************************************************************************/
#include <string>

#ifndef H_BINMAN
#define H_BINMAN

/*** binman class methods *****************************************************/
class binman {
	//Constructor (char + string overload)
	binman(const char *filename);
	binman(const std::string filename);
	
	//Desctructor


	/*** Private class variables **********************************************/
	private:
	//Filename of the 
	char *filename
	
	//Bytes in the memory array
	size_t memBytes;
	//Pointer to array pointer 
	unsigned char *memPtr;
	

}; //class binman

/*** Helper functions *********************************************************/



#endif
