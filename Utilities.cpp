// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 18-07-2021
//
// I have receive minimum help from online and the source is mentioned below: the remaining work was all completed by me and the OOP345 content such as the course-notes and lectures
// Source: https://github.com/pereiradaniel/OOP345_MS1/blob/master/Utilities.cpp


#include <iostream>
#include <algorithm>
#include "Utilities.h"
using namespace std;

namespace sdds {

	// I discovered how to set the default-values for class-variables through research as I explained inside my reflection
	// After testing: I understood that I am not allowed to initialize in-class variables inside the header-file

	char Utilities::m_delimiter = ' ';

	void  Utilities::setFieldWidth(size_t newWidth) {  // The following 'setFieldWidth' function has the purpose of assigning the current-object's 'm_widthField' with the value of the argument 'newWidth'

		this->m_widthField = newWidth;

	}

	size_t Utilities::getFieldWidth() const {  // The following 'getFieldWidth' function has the purpose of simply returning the 'm_widthField' of the current-object

		return this->m_widthField;

	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {  // Like the one-argument constructor of Station: here the program is also extracting the token from the string-parameter

		string temporaryString{};  // Creating the temporary-string variable where the token will be extracted from
		size_t startPosition = next_pos;

		next_pos = str.find(m_delimiter, startPosition);  // I had help here with this line of code from the source I mentioned above

		// The 'next_pos' argument is now holding the 'find' function with the parameters 'm_delimiter' and 'startPosition'
		// I believe the 'find' function has the purpose of finding the desired-delimiter and the position of the said-delimiter 

		if (next_pos == string::npos) {

			temporaryString = str.substr(startPosition);  // I had help with this line of code from the source I mentioned above

			m_widthField = max(temporaryString.length(), m_widthField);  // Here we are setting the 'm_widthField' as the max-length of both the 'temporaryString' and the 'm_widthField'
			more = false;

		}
		else if (startPosition == next_pos) {

			more = false;
			throw "ERROR: No Token";

		}
		else {

			temporaryString = str.substr(startPosition, next_pos - startPosition);  // I had help on this line of code from the source I mentioned above 
			m_widthField = max(temporaryString.length(), m_widthField);
			more = true;

		}

		next_pos++;
		return temporaryString;

	}

	void Utilities::setDelimiter(char newDelimiter) {  // The following 'setDelimiter' function has the purpose of setting the 'm_delimiter' of the current-object with the value of the argument 'newDelimiter'

		m_delimiter = newDelimiter;

	}

	char Utilities::getDelimiter() {  // The following 'getDelimiter' function has the role of returning the 'm_delimiter'

		return m_delimiter;

	}
}