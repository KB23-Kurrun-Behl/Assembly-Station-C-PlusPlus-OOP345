// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 24-07-2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#include <iostream>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;

namespace sdds {

	// I discovered how to set the default-values for class-variables through research as I explained inside my reflection
	// After testing: I understood that I am not allowed to initialize in-class variables inside the header-file

	size_t CustomerOrder::m_widthField = 0;

	CustomerOrder::CustomerOrder() {  // The default-constructor has the purpose of setting the default-values for the members of the CustomerOrder class

		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;

	}

	CustomerOrder::CustomerOrder(const std::string& theString) {  // The one-argument constructor of CustomerOrder has the role of extracting tokens from the string-argument 'theString' and supplying the current-instance

		if (!theString.empty()) {  // If the argument is not empty: the program must perform the following code:

			Utilities theUtilsObj;  // Declaring the local-Utilities object
			size_t thePosition = 0;  // 'thePosition' is holding the position of the token
			bool validation = true;  // 'validation' is declaring whether or not extraction of the token is prohibited 

			try {

				// I referred back to WS05 and even WS04 in order to remember how to extract correctly inside programs

				m_name = theUtilsObj.extractToken(theString, thePosition, validation);  // Extracting the token from the 'm_name'
				m_product = theUtilsObj.extractToken(theString, thePosition, validation);
				m_cntItem = count(theString.begin(), theString.end(), theUtilsObj.getDelimiter()) - 1;  // Because the following variable 'm_cntItem' is counting the number of items: the begin() and end() is required here for extraction 
				m_lstItem = new Item * [m_cntItem];  // Dynamically-allocating memory of type 'Item' to 'm_lstItem' with the number of elements being 'm_cntItem' 

				for (size_t i = 0; i < m_cntItem; i++) {  // Looping through the list of items: 

					m_lstItem[i] = new Item(theUtilsObj.extractToken(theString, thePosition, validation));  // For each-element inside the 'm_lstItem' array we must extract the token 
					m_widthField = max(theUtilsObj.getFieldWidth(), m_widthField);  // Setting the 'm_widthField': I had help throughout most of this function from WS04, WS05 and even MS1, as I mentioned before 

				}
			}

			catch (const string &theErrorMsg) {  // If the following-conditions above are not achieved: the following-exception error-message is outputted 

				cout << theErrorMsg;

			}
		}
	}

	CustomerOrder::CustomerOrder(const CustomerOrder& custOrder) { // The following copy-constructor has the purpose of throwing an exception if this is called 

		throw "The Copy-Operator Is Not Permitted Here";  // The copy-constructor is not prohibited

	}

	CustomerOrder::CustomerOrder(CustomerOrder&& custOrder) noexcept {  // As I explained inside CustomerOrder.h; the move-constructor will not throw any-exceptions and allows the movement of resources 

		m_lstItem = nullptr;
		*this = move(custOrder);

	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& custOrder) noexcept {   // As I explained inside CustomerOrder.h; the move assignment-operator will not throw any-exceptions and allows the trasnferring of the temporary-object to the new-object

		if (this != &custOrder) {

			if (m_lstItem != nullptr) {  // If the elements inside the array 'm_lstItem' is not empty and has values:

				for (size_t i = 0; i < m_cntItem; i++) {  // Loop through the array:

					delete m_lstItem[i];  // And delete each single-element inside the 'm_lstItem' array

				}

				delete[] m_lstItem;  // The following line of code is deleting the whole-array hence the '[]' after 'delete' 

			}

			this->m_lstItem = custOrder.m_lstItem;  // Transferring the value of 'm_lstItem' from the temporary-object to the 'm_lstItem' of the current-object 
			this->m_name = custOrder.m_name;
			this->m_product = custOrder.m_product;
			this->m_cntItem = custOrder.m_cntItem;

			custOrder.m_lstItem = nullptr;  // Setting the 'm_lstItem' of the temporary-object 'custOrder' to the safe-empty state 'nullptr' 
			custOrder.m_name = "";
			custOrder.m_product = "";
			custOrder.m_cntItem = 0;

		}

		return *this;  // Returning the reference to the current-object 

	}

	CustomerOrder::~CustomerOrder() {  // The destructor has the common-purpose of deallocating the memory from the array

		for (size_t i = 0; i < m_cntItem; i++) {  // Looping through the list of items 

			delete m_lstItem[i];  // Delete each single-element inside the 'm_lstItem' array

		}

		delete[] m_lstItem;  // The following line of code is deleting the whole-array hence the '[]' after 'delete' 

	}

	bool CustomerOrder::isFilled() const {  // The following-function has the purpose of returning true if all the items have been filled: false otherwise 

		bool itemFilled = true;  // Declaring the required bool-variable 

		for (size_t i = 0; i < m_cntItem; i++) {  // Looping through the list of items

			if (m_lstItem[i]->m_isFilled) {  // If 'm_isFilled' is set to true for each-element inside the array 'm_lstItem': 

				return itemFilled;  // Return true 

			}

			itemFilled = false;  // Else set 'itemFilled' to false

		}

		return itemFilled;  // Return the bool-variable 

	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {  // This function is quite like the previous-function: this will return true if all items specified by 'itemName' have been filled 

		bool itemFilled = true;  // Declaring the required bool-variable 

		for (size_t i = 0; i < m_cntItem; i++) {  // Looping through the list of items

			if (m_lstItem[i]->m_itemName == itemName) {    

				return m_lstItem[i]->m_isFilled;  // Returning the 'm_isFilled' variable which contains 'false' as the default-value 

			}

		}

		return itemFilled;  // Return true 

	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {  // The following-function 

		for (unsigned int i = 0; i < m_cntItem; i++) {  // Looping through the list of items

			if (m_lstItem[i]->m_itemName == station.getItemName()) {  // If the 'm_itemName' of each-element inside the array is equal to the 'itemName' of Station:

				if (station.getQuantity() > 0) {  // If the number of items inside Station is more than zero: the program will perform the following code 

					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();  // Incrementing 'm_serialNumber' of each-element using the  'getNextSerialNumber()' function from Station
					m_lstItem[i]->m_isFilled = true;  // 'm_isFilled' of each-element inside the array is set to 'true' 
					station.updateQuantity();  // The quantity is now changed with the new figure inside Station
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;  // Output the following-information stating that the items have successfully been filled 

				}
				else {  // Else if the conditions are not true: the program will output the following line:

					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;  // Output the following-information stating that the items were not successfully filled 

				}
			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const {  // The following display-function has the purpose of outputting the required-information with special-formatting 

		os << m_name << " - " << m_product << endl;  // Beginning with outputting the 'm_name' and the 'm_product' 

		for (size_t i = 0; i < m_cntItem; i++) {  // Looping through the list of items 

			// Outputting the information with special-formatting such as extra-width, aligning to the right, setting the empty-space with '0' and more 

			os << "[" << setw(6) << right << setfill('0') << m_lstItem[i]->m_serialNumber << "]" << " " << setw(m_widthField) << left << setfill(' ') << m_lstItem[i]->m_itemName << " - ";

			if (!m_lstItem[i]->m_isFilled) {  // If the 'm_isFilled' of each-element is not true:

				os << "TO BE FILLED" << endl;  // The program must output the following line 'TO BE FILLED' 

			}
			else {  // Else if the condition above is not true:

				os << "FILLED" << endl;  // The program will output this line 'FILLED' 

			}
		}
	}
}