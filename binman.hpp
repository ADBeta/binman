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
* v0.1.3
*******************************************************************************/
#include <string>

#ifndef H_BINMAN
#define H_BINMAN

/*** binman class methods *****************************************************/
class binman {
	public:
	//Constructor (char + string overload)
	binman(const char *filename);
	binman(const std::string filename);
	
	//Desctructor
	~binman();
	/*** File management ******************************************************/
	//Reads input file into the RAM array
	int read();


	/*** Private class variables **********************************************/
	//private: TODO
	//Filename of the input/output file
	char *filename;
	
	//Bytes in the memory array
	size_t memBytes;
	//Pointer to array pointer 
	unsigned char *memPtr;
	
	/*** RAM Manager **********************************************************/
	//Allocate the RAM array, deletes the data previously pointed to
	int allocMem(size_t bytes);	
	//Resize the RAM array directly
	int resizeMem(size_t newBytes);
	//Resizes the RAM array via incrememnt or decrement
	int incMem(size_t incBytes);
	int decMem(size_t decBytes);
	

}; //class binman

/*** Helper functions *********************************************************/



#endif
