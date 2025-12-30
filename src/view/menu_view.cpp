#include "view/menu_view.h"

#include <iostream>

// Display Main Menu
void Menu::staffMenu() {
    std::cout
        << "---------------------------------\n"
        << "STAFF ADMINISTRATION\n"
        << "---------------------------------\n"
        << "[1] Car Administration \n"
        << "[2] Customer Administration \n"
        << "[3] Rental Administration \n"
        << "[4] Statistics Administration\n"
        << "[5] Import From JSON\n"
        << "[6] Export To JSON\n"
        << "[7] Exit Application\n"
        << "---------------------------------\n"
        << std::endl;
}

// Sub Menu: Car Admin
void Menu::carMenu() {
    std::cout
        << "---------------------------------\n"
        << "CAR ADMINISTRATION\n"
        << "---------------------------------\n"
        << "[1] Add Car\n"
        << "[2] Edit Car\n"
        << "[3] Remove Car\n"
        << "[4] Show all cars\n"
        << "[5] Return To Staff Administration\n"
        << "---------------------------------\n"
    << std::endl;
}

// Sub Menu: Customer Admin
void Menu::customerMenu() {
    std::cout
        << "---------------------------------\n"
        << "CUSTOMER ADMINISTRATION\n"
        << "---------------------------------\n"
        << "[1] Add Customer\n"
        << "[2] Edit Customer\n"
        << "[3] Remove Customer\n"
        << "[4] Show all customers\n"
        << "[5] Return To Staff Administration\n"
        << "---------------------------------\n"
    << std::endl;
}

// Sub Menu: Rental Admin
void Menu::rentalMenu() {
    std::cout
        << "---------------------------------\n"
        << "RENTAL ADMINISTRATION\n"
        << "---------------------------------\n"
        << "[1] Register lease\n"
        << "[2] Start or end lease\n"
        << "[3] Show all registered leases\n"
        << "[4] Return To Staff Administration\n"
        << "---------------------------------\n"
    << std::endl;
}

// Sub Menu av Rental, valg 1
void Menu::rentalRegMenu() {
    std::cout
        << "---------------------------------\n"
        << "LEASE REGISTRATION\n"
        << "---------------------------------\n"
        << "[1] Register lease via SSN and RegNr\n"
        << "[2] Register lease via Search\n"
        << "[3] Return to Rental Administration\n"
        << "---------------------------------\n"
    << std::endl;
}

// Sub Menu av Rental, valg 2
void Menu::rentalStart_StopMenu() {
    std::cout <<
        "---------------------------------\n"
        "LEASE UPDATE\n"
        "---------------------------------\n"
        "[1] Update lease via SSN and RegNr\n"
        "[2] Update lease via Search\n"
        "[3] Return to Rental Administration\n"
        "---------------------------------\n"
    << std::endl;
}



// Sub Menu: Statistics Admin
void Menu::statisticsMenu() {
    std::cout
        << "---------------------------------\n"
        << "STATISTIC ADMINISTRATION\n"
        << "---------------------------------\n"
        << "[1] Show total number of customer\n"
        << "[2] Show total number of cars\n"
        << "[3] Show total number of active rentals\n"
        << "[4] Show total number of completed rentals\n"
        << "[5] Return To Staff Administration\n"
        << "---------------------------------\n"
    << std::endl;
}