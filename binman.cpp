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
#include <sstream>
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
	//Delete any existing RAM array data
	delete[] memPtr;

	//Open class file as an input 
	file.open(filename, std::ios::in | std::ios::binary);
	
	//Make sure file is open and exists
	if(file.is_open() == 0) {
		std::cerr << "Error: binman: Cannot open file " << filename 
		          << std::endl;
		return 1;
	}
	
	//Get size (in bytes) of file
	file.seekg(0, std::ios::end); //Go to end of file
	size_t byteCount = file.tellg(); //Ask for byte position (is file bytes)
	file.seekg(0, std::ios::beg); //Go back to the beginning of file
	
	//Allocate the RAM array
	allocMem(byteCount);
	
	//Read the files data into the RAM array
	file.read((char*)memPtr, byteCount);
	
	//Finish up with the file
	file.clear(); //Clear internal std::ios flags
	file.seekg(0, std::ios::beg); //Go to beginning of the file
	file.close(); //Close the fsteam file to free I/O
	
	//If verbosity is enabled, print a nice message
	if(this->confVerbose == true) {
		std::cout << "Read " << filename << " Successful: " << byteCount 
		          << " bytes." << std::endl;
	}
	
	//Success
	return 0;
}

void binman::print(size_t offset, size_t n) {
	//Limit the input values.
	if(offset > memBytes) offset = memBytes;
	if(n > memBytes) n = memBytes;
	
	//Handle default n
	if(n == 0) n = memBytes;
	
	//Print the bytes in the file. In hex format, with offset bytes in hex
	//Offset - 0xAABBCCDD (32bit)   bytes - AA BB CC DD..... to fill 80 chars
	size_t cPrintByte = 0;
	
	while(offset != n) {
		if(cPrintByte == 0) {
			//Print newline and offset
			std::cout << "\n" << toHexString(offset, 8) << "    ";
		}
		
		//Print the current byte to the terminal
		std::cout << toHexString(memPtr[ offset ], 2) << " ";
		
	
		++offset;
		
		//Incriment cPrintByte and limit the end byte
		if(++cPrintByte > 25) cPrintByte = 0;
	}
	
	//Flush the std::cout buffer and new line
	std::cout << std::endl;
	
}

/*** RAM management ***********************************************************/
int binman::allocMem(const size_t bytes) {
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

int binman::resizeMem(const size_t newBytes) {
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

int binman::incMem(const size_t incBytes) {
	//TODO 
	
	return 0;
}

int binman::decMem(const size_t decBytes) {
	return 0;
}

/*** Util functions ***********************************************************/
//Convert a string to a hex string, with string padding
std::string binman::toHexString(const size_t val, unsigned int pad) {
	std::stringstream stream;
	
	//Push a hex converted value to the stream
	stream << std::uppercase << std::hex << val;
	
	//Pad the string
	std::string outStr = stream.str();
	
	unsigned int delta = pad -  outStr.size();
	if(delta != 0) {
		outStr.insert(outStr.begin(), delta, '0');
	}
	
	//Done
	return outStr;
}

