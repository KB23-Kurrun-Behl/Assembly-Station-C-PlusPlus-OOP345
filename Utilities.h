// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 18-07-2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H
#include <iostream>

namespace sdds {

	class Utilities {  // Declaring the Utilities class:

		// The instance-variable of Utilities:

		size_t m_widthField = 1;

		// The class-variable of Utilities:

		static char m_delimiter;

	public:  // The public member-function prototypes for Utilities:

		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		// The class-function prototypes for Utilities:

		static void setDelimiter(char newDelimiter);
		static char getDelimiter();

	};
}

#endif
