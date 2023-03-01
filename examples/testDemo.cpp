#include <iostream>
#include <chrono>
#include <thread>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;


#include "../binman.hpp"

binman file("../TestFiles/Example.jpg");


int main() {
	file.allocMem(1073741824);
	file.memPtr[0] = 69;
	
	std::cout << file.memBytes << std::endl;
	sleep_for(5s);
    
	for(int x = 0; x < 10; x++) {
		//Allocate huge heap
		file.resizeMem(1073741824 - (x * 104857600));
		
		//print heartbeat
		std::cout << "heartbeat" << std::endl;
		
		//wait
		sleep_for(5s);

	}
    

	return 0;
}
