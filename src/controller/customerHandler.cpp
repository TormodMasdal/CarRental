#include "controller//customerHandler.h"
#include <SQLiteCpp/Database.h>

#include <iostream>

// Henter opplysninger om kunden som skal legges til
void customerHandler::handleAddCustomer() const{
    int ssn;
    std::cout << "Enter Social security number: ";
    std::cin >> ssn;

    std::string firstName;
    std::cout << "Enter first name: ";
    std::cin >> firstName;

    std::string lastName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;

    std::string phoneNumber;
    std::cout << "Enter phone number: ";
    std::cin >> phoneNumber;

    std::string email;
    std::cout << "Enter email: ";
    std::cin >> email;

    // Kaller på insert kunde funksjonen og bruker variablene som er blitt initialisert som parametere
    customer.CustomerInsert(ssn, firstName, lastName, phoneNumber, email);
}

// Henter opplysninger om kunden som skal redigeres på
void customerHandler::handleUpdateCustomer() const{
    int ssn;
    std::cout << "Enter Social security number: ";
    std::cin >> ssn;

    // Sjekker om kunden eksisterer i databasen
    if (!customer.checkCustomerExist(ssn)) {
        std::cout << "Customer not found, please enter a valid SSN" << std::endl;
        return;
    }

    std::string firstName;
    std::cout << "Enter first name: ";
    std::cin >> firstName;

    std::string lastName;
    std::cout << "Enter last name: ";
    std::cin >> lastName;

    std::string phoneNumber;
    std::cout << "Enter phone number: ";
    std::cin >> phoneNumber;

    std::string email;
    std::cout << "Enter email: ";
    std::cin >> email;

    // Kaller på oppdater kunde funksjonen og bruker variablene som er blitt initialisert som parametere
    customer.CustomerUpdate(ssn, firstName, lastName, phoneNumber, email);
}

// Henter informasjon om hvilken kunde som skal slettes
void customerHandler::handleDeleteCustomer() const{
    int ssn;
    std::cout << "Enter social security number of customer to delete: ";
    std::cin >> ssn;

    // Sjekker om kunden eksisterer i databasen
    if (!customer.checkCustomerExist(ssn)) {
        std::cout << "Customer not found, please enter a valid SSN" << std::endl;
        return;
    }
    customer.CustomerDelete(ssn);
}

void customerHandler::handleSearchCustomer() const {
    std::string lastName;
    std::cout << "\nSearch by last name:";
    std::cin >> lastName;
    std::cout << "\n";

    customer.searchCustomer(lastName);
}
