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

