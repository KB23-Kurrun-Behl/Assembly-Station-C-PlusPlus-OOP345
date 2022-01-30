// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 18-07-2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>

namespace sdds {

	class Station {  // Declaring the Station class:

		// The instance-variables of Station:

		int m_stationID;
		std::string m_itemName;
		std::string m_itemDesc;
		unsigned int m_serialNo;
		unsigned int m_noOfItems;

		// The class-variables of Station:

		static size_t m_widthField;
		static int id_generator;

	public:  // The public member-function prototypes for Station:

		Station(){};
		Station(const std::string& theString);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;

	};
}

#endif
