// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 30-07-2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds {

	// Declaring the required external deque-containers for the program
	// The containers are declared as 'external' as this was the only way I was able to access the containers in different modules

	extern std::deque<CustomerOrder> pending; 
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

	class Workstation : public Station {  // Declaring the Workstation class derived from the base-class Station:

		std::deque<CustomerOrder> m_orders;  // Declaring the deque-container 'm_orders' of CustomerOrder type 
		Workstation* m_pNextStation = nullptr;  // The Workstation pointer to the next available station 

	public:  // The public member-function prototypes for Workstation:

		Workstation(const Workstation& wrkStation) = delete;
		Workstation& operator=(const Workstation& wrkStation) = delete;
		Workstation(Workstation&& wrkStation) noexcept = delete;
		Workstation& operator=(Workstation&& wrkStation) noexcept = delete;
		~Workstation() {};

		Workstation(const std::string& theString);
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}

#endif
