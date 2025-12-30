#include "controller/menuHandler.h"
#include "view/menu_view.h"
#include "model/importExport.h"

#include <iostream>
#include <limits>
#include <thread>

// Leser og validerer heltallsinput fra bruker
auto menuHandler::inputHelper(const std::string &input) {
    auto inputValue = 0;
    while (true) {
        std::cout << input;
        if (std::cin >> inputValue) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return inputValue;
        }
        std::cout << "Invalid input. Please enter a numerical value\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Hovedmeny
void menuHandler::run() {
    auto menuChoice = 0;
    while (true) {
        Menu::staffMenu();
        menuChoice = inputHelper("Choose an option between 1-7: ");
        switch (menuChoice) {
            case 1: handleCarMenu(); break;
            case 2: handleCustomerMenu(); break;
            case 3: handleRentalMenu(); break;
            case 4: handleStatisticsMenu(); break;
            case 5: importExport::ImportJSON(accessDB.db); waitTwoSec(); break;
            case 6: importExport::ExportJSON(accessDB.db); waitTwoSec(); break;
            case 7: std::cout << "Goodbye!\n"; return;
            default: std::cout << "Invalid input. Please enter a valid number\n";
            waitTwoSec();
        }
    }
}

// Car Meny
void menuHandler::handleCarMenu() const{
    auto carChoice = 0;
    while (true) {
        Menu::carMenu();
        carChoice = inputHelper("Enter an option between 1-5: ");
        if (carChoice == 5) break;
        switch (carChoice) {
            case 1: CarHandler.handleAddCar();
                    waitTwoSec();
                break;
            case 2: CarHandler.handleUpdateCar();
                    waitTwoSec();
                break;
            case 3: CarHandler.handleDeleteCar();
                    waitTwoSec();
                break;
            case 4: car.CarSelectAll();
                    waitAfterSelect();
                break;
            default: std::cout << "Invalid option, try again.\n";
            waitTwoSec();
        }
    }
}

// Customer Meny
void menuHandler::handleCustomerMenu() const{
    auto customerChoice = 0;
    while (true) {
        Menu::customerMenu();
        customerChoice = inputHelper("Enter an option between 1-5: ");
        if (customerChoice == 5) break;
        switch (customerChoice) {
            case 1: CustomerHandler.handleAddCustomer();
                    waitTwoSec();
                break;
            case 2: CustomerHandler.handleUpdateCustomer();
                    waitTwoSec();
                break;
            case 3: CustomerHandler.handleDeleteCustomer();
                    waitTwoSec();
                break;
            case 4: customer.CustomerSelectAll();
                    waitAfterSelect();
                break;
            default: std::cout << "Invalid option, try again.\n";
            waitTwoSec();
        }
    }
}

// Rental Meny
void menuHandler::handleRentalMenu() const{
    auto rentalChoice = 0;
    while (true) {
        Menu::rentalMenu();
        rentalChoice = inputHelper("Enter an option between 1-4: ");
        if (rentalChoice == 4) break;
        switch (rentalChoice) {
            case 1: handleRentalRegMenu();
                break;
            case 2: handleRentalStart_StopMenu();
                break;
            case 3: rental.RentalSelectAll();
                    waitAfterSelect();
                break;
            default: std::cout << "Invalid option, try again.\n";
            waitTwoSec();
        }
    }
}

// Sub meny av rental, på valg 1
void menuHandler::handleRentalRegMenu() const {
    auto searchChoice = 0;
    while (true) {
        Menu::rentalRegMenu();
        searchChoice = inputHelper("Enter an option between 1-3: ");
        if (searchChoice == 3) break;

        switch (searchChoice) {
            case 1: RentalHandler.registerLeases();
                    waitTwoSec();
                break;
            case 2: CarHandler.handleSearchCar();
                    CustomerHandler.handleSearchCustomer();
                    RentalHandler.registerLeases();
                    waitTwoSec();
                break;
            default: std::cout << "Invalid option, try again.\n";
            waitTwoSec();
        }
    }
}

// Sub meny av rental, på valg 2
void menuHandler::handleRentalStart_StopMenu() const{
    int searchChoice = 0;
    while (true) {
        Menu::rentalStart_StopMenu();
        searchChoice = inputHelper("Enter an option between 1-3: ");
        if (searchChoice == 3) break;
        switch (searchChoice) {
            case 1: RentalHandler.handleRegisteredLeases();
                    waitTwoSec();
                break;
            case 2: CarHandler.handleSearchCar();
                    CustomerHandler.handleSearchCustomer();
                    RentalHandler.handleRegisteredLeases();
                    waitTwoSec();
                break;
            default: std::cout << "Invalid option, try again.\n";
            waitTwoSec();
        }
    }
}

// Statistics Meny
void menuHandler::handleStatisticsMenu() const{
    auto statisticsChoice = 0;
    while (true) {
        Menu::statisticsMenu();
        statisticsChoice = inputHelper("Enter an option between 1-5: ");
        if (statisticsChoice == 5) break;

        switch (statisticsChoice) {
            case 1:
                customer.CustomerCount();
                waitTwoSec();
                break;
            case 2:
                car.countCar();
                waitTwoSec();
                break;
            case 3:
                rental.countActiveLease();
                waitTwoSec();
                break;
            case 4:
                rental.countCompletedLease();
                waitTwoSec();
                break;
            default: std::cout << "Invalid option, try again.\n";
            waitTwoSec();
        }
    }
}

void menuHandler::waitAfterSelect() {
    auto choice = 0;
    while (true) {
        std::cout << "\nPress 1 to exit: ";
        std::cin >> choice;
        if (choice == 1) {
            return;
        }
    }
}

void menuHandler::waitTwoSec() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

