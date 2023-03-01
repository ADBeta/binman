/*******************************************************************************
* This file is pat of binman - Binary Managment library for C++
*
* If this file is in use in another, unrelated project, please see the github
* for binman for more information: https://github.com/ADBeta/binman
*
* This project is under GNU Public Licence.
* (c) 2023 ADBeta
*******************************************************************************/
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>

#include "binman.hpp"

/*** Constructor / Destructor *************************************************/
binman::binman(const char *fn) {
	//Create a char array at m_filename the size of the input string.
	this->filename = new char[ strlen(fn) + 1 ];
	
	//Copy the input string to the new char array at m_filename
	strcpy(this->filename, fn);
}

binman::binman(const std::string fn) {
	//Create a char array at m_filename the size of the input string.
	this->filename = new char[ fn.size() + 1 ];

	//Copy the input string to the new char array at m_filename
	strcpy(this->filename, fn.c_str());
} 

binman::~binman() {
	delete[] memPtr;
}

/*** File management **********************************************************/
//Reads input file into the RAM array
int binman::read() {

	return 0;
}

/*** RAM management ***********************************************************/
int binman::allocMem(size_t bytes) {
	//Create a new array in RAM, check for bad_allocation and error
	unsigned char *newArr;
	try { 
		newArr = new unsigned char[bytes];	
	} catch (std::bad_alloc& ba) {
		std::cerr << "Error: binman: " << ba.what() << std::endl;
		return -1;
	}
	
	//Set the new size of memBytes
	this->memBytes = bytes;
	
	//Delete the old array to prevent RAM leaks
	delete[] memPtr;
	
	//Set the pointer of memPtr to the new RAM bank just allocated
	this->memPtr = newArr;
	
	//Return success
	return 0;
}

int binman::resizeMem(size_t newBytes) {
	//If the new size is the same as the last, just exit as a success
	if(memBytes == newBytes) return 0;

	//How many bytes to copy from array, depending on if the new size is smaller
	size_t copyBytes;
	//If the new size is smaller, it needs to be the copy size
	if(newBytes > memBytes) {
		copyBytes = memBytes;
	} else {
		copyBytes = newBytes;
	}
	
	//Create a new array in RAM, check for bad_allocation and error
	unsigned char *newArr;
	try { 
		newArr = new unsigned char[newBytes];	
	} catch (std::bad_alloc& ba) {
		std::cerr << "Error: binman: " << ba.what() << std::endl;
		return -1;
	}
	
	//If copyBytes shows there is something to copy, copy it
	if(copyBytes != 0) {
		//Move the data from the original array to the new array
		memcpy(newArr, this->memPtr, copyBytes);
	}
	
	//Set the new size of memBytes
	this->memBytes = newBytes;
	
	//Delete the old array to prevent RAM leaks
	delete[] memPtr;
	
	//Set the pointer of memPtr to the new RAM bank just allocated
	this->memPtr = newArr;
	
	//Return success
	return 0;
}

int binman::incMem(size_t incBytes) {
	//TODO 
	
	return 0;
}

int binman::decMem(size_t decBytes) {
	return 0;
}
