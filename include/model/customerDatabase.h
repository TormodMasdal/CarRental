#ifndef CUSTOMERDATABASE_H
#define CUSTOMERDATABASE_H

#include <SQLiteCpp/Database.h>
#include "accessDB.h"

// Klasse for all kommunikasjon med customer tabellen i databasen
class customerDatabase {
public:
    accessDB AccessDB;

    // Ingen av funksjonene skal endre på AccessDB, Dermed CONST
    void CustomerInsert(const int &ssn,
        const std::string &firstName,
        const std::string &lastName,
        const std::string &phoneNumber,
        const std::string &email) const;

    void CustomerUpdate(const int &ssn,
        const std::string &firstName,
        const std::string &lastName,
        const std::string &phoneNumber,
        const std::string &email) const;

    void CustomerDelete(const int &ssn) const;
    void CustomerSelectAll() const;
    void CustomerCount() const;
    void searchCustomer(std::string search) const;

    bool checkCustomerExist(const int &ssn) const;
};
#endif //CUSTOMERDATABASE_H