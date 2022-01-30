// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 30-07-2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H
#include <iostream>
#include <vector>
#include "Workstation.h"

namespace sdds {

	class LineManager {  // Declaring the LineManager class:

		// The instance-variables of LineManager:

		std::vector<Workstation*> activeLine;  // The vector containing the collection of workstations
		size_t m_cntCustomerOrder;  // The variable counting the number of customer orders in total 
		Workstation* m_firstStation;  // The Workstation pointer with the purpose of pointing to the first station on the active-line 

	public:  // The public member-function prototypes for LineManager:

		LineManager(const LineManager& lineMger) = delete;
		LineManager& operator=(const LineManager& lineMger) = delete; 
		LineManager(LineManager&& lineMger) noexcept = delete;
		LineManager& operator=(LineManager&& lineMger) noexcept = delete;
		~LineManager() {};

		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;

	};
}

#endif


