# Basic API calls and what they do

First, you need to declare a binman object with a filename like this  
```C++
#include "binman.hpp"

//This is a binman object declaration
binman file("./example.jpg");

int main() {

	return 0;
};
```

From there you can use the API functions.  
```C++
file.read()
```
This will read the file using the filename into the RAM array. If this fails it
will return non-zero, and print an error message. you can detect failure like this
```C++
if( file.read() != 0) exit(EXIT_FAILURE);
```

To print the files data (Hex dump) to the terminal, you can use the `print()` 
function.
```C++
//This will print from (offset), (n) number of bytes
file.print(0, 200);

//This will print from (offset) until the end of file
file.print(1024);

//This will print the entire file from beginning to end
file.print();
```
