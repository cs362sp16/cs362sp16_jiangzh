：#include <iostream>
#include <string.h>
#include <cstdlib>

int main(int argc, char** argv){  // the value of argc is 3, an value of argv[0]is address, and the argv[1]is "cat", and the argv[2]is 'a'.  
	int i;
	char* str;
	char ch;
	bool found = false;

	if( argc != 3 ) {
		std::cout << "Usage: search <string> <character>" << std::endl;
		exit(-1);
	}
	str = argv[1];
	ch = argv[2][0];

	for(i = 0; i < strlen(str); i++ ) {        //previously, string is "cat", and the length is 3, so it loop three times, so we check the str[i]each time, first time, value of the str[i] is 'c', so is not equal to ch
                                                        //because value of ch is 'a', then found is false.second time, the value of str[i] is 'a', and the so str[i] is 'ch', so found is true. Thrid time, the value of [str] is equal to t, is not
                                                        //equal to ch, is found is false. 
		if( str[i] == ch ) {
			found = true;
		}
	}
	if( found ) {
		std::cout << ch << " found in " << str << std::endl;
	} else {
		std::cout << ch << " not found in " << str << std::endl;
	}
 	return 0;
}
