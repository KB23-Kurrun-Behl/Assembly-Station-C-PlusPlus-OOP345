// Name: Kurrun Behl
// Seneca Student ID: 146622196
// Seneca Email: kbehl2@myseneca.ca
// Date Of Completion: 30-07-2021
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.


#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "LineManager.h"
#include "Workstation.h"
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;

namespace sdds {

    static size_t currentIterationNo = 0;  // Declaring the static global-variable with the purpose of representing the iteration-number inside the output 

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {  // The following two-argument constructor has several responsibilites to fulfill for the program such as extracting data, opening and closing files and more 

        Utilities theUtilsObj;  // Declaring the local Utilities object
        size_t thePosition = 0; // Declaring the local-variable 'thePosition' holding the position of the token
        size_t theIndex = 0;  // The variable containing the index of the line is declared here
        bool validation = true;  // // Declaring the bool local-variable 'validation' declaring whether or not extraction of the token is prohibited 

        std::string stringObj1 = "";  // The string-objects required for extraction 
        std::string stringObj2 = "";
        std::string stringObj3 = "";


        std::ifstream theFile(file);  // Creating and opening the file 'theFile' for reading

        if (!theFile) {  // If the file is not available for the program:

            cout << "ERROR: Cannot open file [" << file << "]." << endl;  // The folllowing error-message will be outputted by the program
            return;

        }
        while (!theFile.eof()) {  // If the file has not reached the end of the file: the program will run the following code: 

            validation = true;
            getline(theFile, stringObj1);  
            stringObj2 = theUtilsObj.extractToken(stringObj1, thePosition, validation);  // Extracting the tokens was easy for me to complete due to my work on the Station module from MS2

            auto i = std::find_if(stations.begin(), stations.end(), [=](Workstation* W) {return (W->getItemName() == stringObj2);});  // For each element inside the Workstation vector: the function will return the item-name and initialize the string-object with this value

            activeLine.push_back(*i);  // Here the function is adding the new element at the end of the vector 'activeLine' 

            if (validation) {  // If the 'validation' is true:

                stringObj3 = theUtilsObj.extractToken(stringObj1, thePosition, validation);  // The program will run the following code
                i = std::find_if(stations.begin(), stations.end(), [=](Workstation* W) {return (W->getItemName() == stringObj3);});  // The variable 'i' now contains the following 'find_if' function which I explained above
                activeLine[theIndex]->setNextStation(*i);  // For 'theIndex' declared inside [] of the 'activeLine' vector; the program will set the next station at the said index. 

            }

            theIndex++;  // Incrementing theIndex

        }

        theFile.close();  // Closing the file is important in order to ensure a 'safe' program
        m_firstStation = activeLine.front();  // The 'm_firstStation' is now initialized with the reference to the first element of the 'activeLine' vector
        m_cntCustomerOrder = pending.size();  // The 'm_cntCustomerOrder' is now initialized with the size of the 'pending' deque-container

    }

    void LineManager::linkStations() {  // The following function has the purpose of reordering the workstations and storing this modified collection inside the instance-variable 'm_firstStation'

        const Workstation* temporaryStationObj = m_firstStation;  // Declaring the temporary-object of Workstation* type initialized with the value of 'm_firstStation'
        auto i = 0;

        do {  // The program will run the code once, and if the condition below is true, the code will continue running the code

            activeLine[i++] = const_cast<Workstation*>(temporaryStationObj);  // Here the function is casting 'temporaryStationObj' to the type of 'Workstation*' 
            temporaryStationObj = temporaryStationObj->getNextStation();  // The 'temporaryStationObj' is being initialized with 'm_pNextStation' 


        } while (temporaryStationObj != nullptr);

    }

    bool LineManager::run(std::ostream& os) {

        os << "Line Manager Iteration: " << ++currentIterationNo << endl;

        if (!pending.empty()) {  // If the 'pending' deque is currently not empty and contains data:

            *m_firstStation += std::move(pending.front());  // The function will move '*m_firstStation' to the front of the pending container
            pending.pop_front();  // Removing the first-element of the 'pending' container 
            
            // I revisited the OOP345 course-notes for support on how to use 'deque' containers and the member-functions available: https://ict.senecacollege.ca/~oop345/pages/content/seque.html
        
        }

        for (auto& S : activeLine) {  // Here we have the 'range-for' statement: for each 'S' element inside the 'activeLine':

            S->fill(os);  // The function will fill each element 

        }

        for (auto& S : activeLine) {  // For each 'S' element inside the 'activeLine':

            S->attemptToMoveOrder();  // The function will move the CustomerOrders to each station

        }

        return completed.size() + incomplete.size() == m_cntCustomerOrder;  // If the following statement is true; the function will true. However, if false, the function will return false

    }

    void LineManager::display(std::ostream& os) const {  // The following function has the purpose of displaying the stations on the 'activeLine' 

        for (auto theStation : activeLine) {

            theStation->display(cout);

        }
    }
}