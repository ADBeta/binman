#include <iostream>
#include "../binman.hpp"


binman file("../TestFiles/Example.jpg");


int main() {
	
	file.read();
	
	
	file.print(0, 250);
	
	std::cin.get();
	
	return 0;
}
