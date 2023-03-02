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
* 2 March 2023
* v0.3.6
*******************************************************************************/
#include <string>
#include <fstream>

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
	/*** File Management ******************************************************/
	//Reads input file into the RAM array
	int read();
	
	//Print a section or all of the binary file, pass offset and bytes to print 
	//Default call prints the whole file to the terminal
	void print(size_t offset = 0, size_t n = 0);


	/*** Private class variables **********************************************/
	//private: TODO
	/*** Config Variables *****************************************************/
	bool confVerbose = true;
	
	
	/*** File Variables *******************************************************/
	//File object
	std::fstream file;
	
	//Filename of the input/output file
	char *filename;
	
	//Bytes in the memory array
	size_t memBytes;
	//Pointer to array pointer 
	unsigned char *memPtr;
	
	/*** RAM Manager **********************************************************/
	//Allocate the RAM array, deletes the data previously pointed to
	int allocMem(const size_t bytes);	
	//Resize the RAM array directly
	int resizeMem(const size_t newBytes);
	//Resizes the RAM array via incrememnt or decrement
	int incMem(const size_t incBytes);
	int decMem(const size_t decBytes);
	
	/*** Util functions *******************************************************/
	//Converts an int to HEX Uppercase value and pads it with 0's
	std::string toHexString(const size_t val, unsigned int pad);

}; //class binman

/*** Helper functions *********************************************************/



#endif
