// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 18-07-2021
//
// I have receive minimum help from online and the source is mentioned below: the remaining work was all completed by me and the OOP345 content such as the course-notes and lectures
// Source: https://github.com/pereiradaniel/OOP345_MS1/blob/master/Station.cpp


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cstring>
#include "Utilities.h"
#include "Station.h"
using namespace std;

namespace sdds {

	// I discovered how to set the default-values for class-variables through research as I explained inside my reflection
	// After testing: I understood that I am not allowed to initialize in-class variables inside the header-file

	size_t Station::m_widthField = 0;
	int Station::id_generator = 1;

	Station::Station(const std::string& theString) {  // The one-argument constructor of Station has the role of extracting the token from the instance-variables

		m_stationID = id_generator;

		Utilities theUtilsObj;  // Declaring the local-Utilities object
		size_t thePosition = 0;  // Declaring the local-variable 'thePosition' holding the position of the token
		bool validation = true;  // Declaring the bool local-variable 'validation' declaring whether or not extraction of the token is prohibited 

		try {

			// I referred back to WS05 and even WS04 in order to remember how to extract correctly inside programs
			// As the MS1 specifications said: we must extract the token and for this reason 'extractToken' was used in-comparison to 'getline'

			m_itemName = theUtilsObj.extractToken(theString, thePosition, validation);  // Extracting the token from the 'm_itemName'
			m_serialNo = stoi(theUtilsObj.extractToken(theString, thePosition, validation));
			m_noOfItems = stoi(theUtilsObj.extractToken(theString, thePosition, validation));

			m_widthField = max(theUtilsObj.getFieldWidth(), m_widthField);  // I had help here with this one-line of code from the source I mentioned above

			m_itemDesc = theUtilsObj.extractToken(theString, thePosition, validation);

		}
		catch (const string &theErrorMsg) {  // If the following-conditions above are not achieved: the following-error message is outputted to the screen

			cout << theErrorMsg;

		}

		id_generator++;  // Incrementing the 'id_generator' variable is important because this function has created multiple new-instances of the Station class

	}

	const std::string& Station::getItemName() const {  // The following 'getItemName' function is simple and only returns the 'm_itemName' of the current-object

		return this->m_itemName;

	}

	size_t Station::getNextSerialNumber() {  // The following 'getNextSerialNumber' is also simple and returns the next serial-number as well as incrementing the serial-number

		return m_serialNo++;

	}

	size_t Station::getQuantity() const {  // The following 'getQuantity' function is returning the 'm_noOfItems' variable 

		return m_noOfItems;

	}

	void Station::updateQuantity() {  // The following 'updateQuantity' function has the purpose of subtracting one from the available-quantity

		m_noOfItems--;

		if (m_noOfItems < 0) {

			m_noOfItems = 0;

		}
	}

	void Station::display(std::ostream& os, bool full) const {  // The 'display' function has the purpose of outputting all the required-information with the special-formatting

		if (full == false) {  // If this condition is true: the program must perform the following code

			os << std::right << "[" << setw(3) << setfill('0') << m_stationID << "] " << std::left << "Item: " << setw(m_widthField) << setfill(' ') << m_itemName << std::right << " [" << setw(6) << setfill('0') << m_serialNo << "]" << std::left << endl;

		}
		else {  // Else if the condition above is false: the program must perform this code

			os << std::right << "[" << setw(3) << setfill('0') << m_stationID << "] " << std::left << "Item: " << setw(m_widthField) << setfill(' ') << m_itemName << std::right << " [" << setw(6) << setfill('0') << m_serialNo << "] " << std::left << "Quantity: " << setw(m_widthField) << setfill(' ') << m_noOfItems << " Description: " << m_itemDesc << endl;

		}
	}
}