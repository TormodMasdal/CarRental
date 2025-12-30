#include "model/customerDatabase.h"

#include <sqlite3.h>
#include <iostream>

// Funksjon som legger til kunder i databasen
void customerDatabase::CustomerInsert(const int &ssn, const std::string &firstName, const std::string &lastName,
    const std::string &phoneNumber, const std::string &email) const{

    SQLite::Statement customerInsert(AccessDB.db,
        "INSERT INTO  customers (ssn, firstName, lastName, phoneNumber, email) VALUES (?, ?, ?, ?, ?)");

    customerInsert.bind(1, ssn);
    customerInsert.bind(2, firstName);
    customerInsert.bind(3, lastName);
    customerInsert.bind(4, phoneNumber);
    customerInsert.bind(5, email);

    if (customerInsert.exec() == 1) {
        std::cout << "Inserted customer successfully" << std::endl;
    }
    else {
        std::cout << "Failed to insert customer" << std::endl;
    }
}

// Funksjon som oppdaterer kunder i databasen
void customerDatabase::CustomerUpdate(const int &ssn, const std::string &firstName,
    const std::string &lastName, const std::string &phoneNumber, const std::string &email) const{

    SQLite::Statement customerUpdate(AccessDB.db,
        "UPDATE customers SET firstName = ?, lastName = ?, phoneNumber = ?, email = ? WHERE ssn = ?");

    customerUpdate.bind(1, firstName);
    customerUpdate.bind(2, lastName);
    customerUpdate.bind(3, phoneNumber);
    customerUpdate.bind(4, email);
    customerUpdate.bind(5, ssn);

    if (customerUpdate.exec() == 1) {
        std::cout << "Updated customer successfully" << std::endl;
    }
    else {
        std::cout << "Failed to update customer" << std::endl;
    }
}

// Funksjon som sletter kunder i databasen
void customerDatabase::CustomerDelete(const int &ssn) const{
    // Sql kommando
    SQLite::Statement removeCustomer(AccessDB.db, "DELETE FROM customers WHERE ssn = ?");
    removeCustomer.bind(1, ssn);

    // Hvis antall endret rader = 1
    if (removeCustomer.exec() == 1) {
        std::cout << "Customer was removed successfully" <<std::endl;
    }
    else {
        std::cout << "Failed to remove customer" << std::endl;
    }
}

// Funksjon som velger alle kunder og oppdaterer kundene
void customerDatabase::CustomerSelectAll() const{

    SQLite::Statement selectAllCustomers(AccessDB.db, "SELECT * FROM customers");


    if (selectAllCustomers.tryExecuteStep() == SQLITE_ROW) {
        int i = 1;
        do {

            //Hente kolonner fra kunde tabellen
            int ssn = selectAllCustomers.getColumn("ssn");
            std::string firstName = selectAllCustomers.getColumn("firstName");
            std::string lastName = selectAllCustomers.getColumn("lastName");
            std::string phoneNumber = selectAllCustomers.getColumn("phoneNumber");
            std::string email = selectAllCustomers.getColumn("email");

            std::cout << i << ". SSN: " << ssn << ", First Name: " << firstName
            << ", Last Name: " << lastName << ", Phone Number: " << phoneNumber << ", Email: " << email << std::endl;
            i++;
        }
        while (selectAllCustomers.tryExecuteStep() == SQLITE_ROW);
    }
    else {
        std::cout << "No customers found" << std::endl;
    }
}

// Funksjon som teller antall kunder
void customerDatabase::CustomerCount() const{

    // Sql kommando
    SQLite::Statement selectAll(AccessDB.db, "SELECT COUNT(*) FROM customers");

    if (selectAll.executeStep()) {
        int count = selectAll.getColumn(0);
        std::cout << "Number of customers: " << count << std::endl;
    }
    else {
        std::cout << "Failed to get number of customers" << std::endl;
    }
}

// Funksjon som sjekker at kunder eksiterer
bool customerDatabase::checkCustomerExist(const int &ssn) const{
    SQLite::Statement customerExist(AccessDB.db, "SELECT ssn FROM customers WHERE ssn = ?");
    customerExist.bind(1, ssn);

    if (customerExist.executeStep() != 1) {
        return false;
    }
    return true;
}

// Funksjon som søker etter kunder
void customerDatabase::searchCustomer(std::string search) const {
    SQLite::Statement Search(AccessDB.db, "SELECT * FROM customers WHERE lastName LIKE ? ");
    search = "%" + search + "%";
    Search.bind(1, search);

    if (Search.tryExecuteStep() == SQLITE_ROW) {
        int i = 1;
        do {
            //Hente kolonner fra kunde tabellen
            int ssn = Search.getColumn("ssn");
            std::string firstName = Search.getColumn("firstName");
            std::string lastName = Search.getColumn("lastName");
            std::string phoneNumber = Search.getColumn("phoneNumber");
            std::string email = Search.getColumn("email");

            std::cout << i << ". Social security number: " << ssn << ", First Name: " << firstName
            << ", Last Name: " << lastName << ", Phone Number: " << phoneNumber << ", Email: " << email << std::endl;
            i++;
        }
        while (Search.tryExecuteStep() == SQLITE_ROW);
    }
    else {
        std::cout << "No customers found" << std::endl;
    }
}
