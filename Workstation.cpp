// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 30-07-2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#include <iostream>
#include <deque>
#include <algorithm>
#include "Workstation.h"
#include "CustomerOrder.h"
using namespace std;

namespace sdds {

	deque<CustomerOrder> pending;
	deque<CustomerOrder> completed;
	deque<CustomerOrder> incomplete;

	Workstation::Workstation(const std::string& theString) : Station(theString) {}  // The following one-argument constructor has the purpose of passing 'theString' to the base-class Station

	void Workstation::fill(std::ostream& os) {  // The following function has the purpose of filling each element inside the CustomerOrders

		if (!m_orders.empty()) {

			for (auto& CO : m_orders) {  // For each element inside the 'm_orders' deque-container the function will fill them with the 'fillItem()' function

				CO.fillItem(*this, os);

			}
		}
	}

	bool Workstation::attemptToMoveOrder() {  // This function is attempting to move the order to the next station inside the assembly-line 
		
		if (m_orders.empty())  // If the 'm_orders' deque-container is currently empty:

			return false;  // The function will return false
		 
		CustomerOrder& temporaryOrderObj = m_orders.front();  // Creating the temporary CustomerOrder object which is intialized with the reference to the first element of the 'm_orders' container

		if (temporaryOrderObj.isItemFilled(this->getItemName()) || this->getQuantity() == 0) {  // If the following conditions are true: 
			
			if (m_pNextStation) { 

				*m_pNextStation += std::move(temporaryOrderObj);  // The function will now move the 'temporaryOrderObj' to the 'm_pNextStation' pointer 

			}

			else if (temporaryOrderObj.isFilled()) {  // Else if the following condition is true:

				completed.push_back(std::move(temporaryOrderObj));  // The function will move 'temporaryOrderObj' to the back of the container 'completed'

			}

			else {  // Else if none of the conditions above are true:

				incomplete.push_back(std::move(temporaryOrderObj));  // The function will move 'temporaryOrderObj' to the back of the container 'incomplete'

			}

			m_orders.pop_front();  // Removing the first-element of the 'm_orders' deque
			return true;

		}

		else {  // If (temporaryOrderObj.isItemFilled(this->getItemName()) || this->getQuantity() == 0) is not true:

			return false;

		}
	}

	void Workstation::setNextStation(Workstation* station) {  // This function is initializing the 'm_pNextStation' pointer with the 'station' argument

		m_pNextStation = station;

	}
	
	Workstation* Workstation::getNextStation() const {  // This function is only returning the 'm_pNextStation'

		return m_pNextStation;

	}

	void Workstation::display(std::ostream& os) const {  // The following display function is outputting the required information

		os << getItemName() << " --> ";  // Outputting the item name with the function 'getItemName()' 

		if (m_pNextStation == nullptr) {  // If the pointer 'm_pNextStation' is currently empty:

			os << "End of Line" << endl;  // Output the following line 

		}
		else {  // Else if the condition above is not true and 'm_pNextStation' 

			os << m_pNextStation->getItemName() << endl;  // Outputting the item name with the function 'getItemName()' inside Workstation

		}
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {  // The following operator+= function is moving the argument 'newOrder' at the end of the 'm_orders' container 

		m_orders.push_back(std::move(newOrder));
		return *this;

	}
}