// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 24-07-2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <iostream>
#include "Station.h"

namespace sdds {

	class CustomerOrder {  // Declaring the CustomerOrder class:

		// Declaring the structure 'Item' inside the 'CustomerOrder' class with the following-members:

		struct Item {

			std::string m_itemName;
			size_t m_serialNumber{0};
			bool m_isFilled{false};
			Item(const std::string& src) : m_itemName(src) {};

		};

		// The instance-variables of CustomerOrder:

		std::string m_name;
		std::string m_product;
		size_t m_cntItem;
		Item** m_lstItem;

		// The class-variable of CustomerOrder:

		static size_t m_widthField;

	public:  // The public member-function prototypes for CustomerOrder (including the rule-of-five):

		CustomerOrder();
		CustomerOrder(const CustomerOrder& custOrder);
		CustomerOrder& operator=(const CustomerOrder& custOrder) = delete;  // The implementation for the copy operator= is not required and has been deleted hence the keyword 'delete' 
		CustomerOrder(CustomerOrder&& custOrder) noexcept;  // The 'noexcept' keyword promises that no-exceptions will be thrown 
		CustomerOrder& operator=(CustomerOrder&& custOrder) noexcept;  // The 'noexcept' keyword promises that no-exceptions will be thrown 
		~CustomerOrder();

		CustomerOrder(const std::string& theString);
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;

	};
}

#endif
