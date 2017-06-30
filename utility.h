#ifndef UTILITY_H
#define UTILITY_H

using namespace std;
#include <iostream>             // standard iostream operations
#include <limits>               // numeric limits
#include <cmath>                // mathematical functions
#include <cstdlib>              // C-string functions
#include <cstddef>              // C-library language support
#include <fstream>              // file input and output
#include <cctype>               // Character classification
#include <ctime>                // date and time functions
bool user_says_yes();

enum Error_code{success, fail, range_error, underflow, overflow, fatal,
 not_present, duplicate_error, entry_inserted, entry_found, internal_error
};

bool user_says_yes()
{
	int c;
	bool initial_response= true;
	do{
		if (initial_response)
		cout << "(y,n)?" << flush;
		else
		cout << "Respond with either 'y' or 'n'" << flush;
		do{
			c = cin.get();
		}while (c == '\n' || c == ' ' || c == '\t');
	}while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
	return (c == 'y' || c == 'Y');
}

#endif
