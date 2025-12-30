#include "model/rentalDatabase.h"

#include <sqlite3.h>
#include <iostream>

// Funksjon som legger til utleie
void rentalDatabase::RentalInsert(const int ssn, const std::string &RegNr,
    const std::string &startDate, const int daysOfLease, const int status) const {

    // Sql kommandoen
    SQLite::Statement insert(AccessDB.db,
        "INSERT INTO leases "
        "(ssn, RegNr, startDate, daysOfLease, status) "
        "VALUES (?, ?, ?, ?, ?)");

    // Binder parametrene til verdiene
    insert.bind(1, ssn);
    insert.bind(2, RegNr);
    insert.bind(3, startDate);
    insert.bind(4, daysOfLease);
    insert.bind(5, status);


    // Eksekverer og sjekker om det går som det skal
    if (insert.exec() == 1) {
        std::cout << "inserted row" << std::endl;
    }
    else {
        std::cout << "Failed to insert row" << std::endl;
    }
}

void rentalDatabase::RentalUpdate(const int LeaseId, const int status) const {

    // Sql kommandoen
    SQLite::Statement update(AccessDB.db, "UPDATE leases SET status = ? "
                                 "WHERE LeaseId = ?");

    //Binder parametrene til Sql kommandoen
    update.bind(1, status);
    update.bind(2, LeaseId);


    // Eksekverer og sjekker om det går som det skal
    if (update.exec() == 1) {
        std::cout << "Edit successfull" << std::endl;
    }
    else {
        std::cout << "Error" << std::endl;
    }
}

// Funksjon som sletter utleier
void rentalDatabase::RentalDelete(const int LeaseId) const {

    // Sql kommandoen
    SQLite::Statement remove(AccessDB.db, "DELETE FROM leases WHERE LeaseId = ?");

    // Binder parameteret til Sql kommandoen
    remove.bind(1, LeaseId);

    // Hvis antall endret rader = 1
    if (remove.exec() == 1) {
        std::cout << "Car was removed successfully" <<std::endl;
    }
    else {
        std::cout << "Car not found" << std::endl;
    }

}

// Funksjon som velger alle utleier
void rentalDatabase::RentalSelectAll() const {

    // Sql kommando
    SQLite::Statement selectAll(AccessDB.db,
        "SELECT leases.*, (pricePrDay * daysOfLease) AS TotPrice "
        "FROM leases, cars "
        "WHERE leases.RegNr = cars.RegNr");


    // Henter alle rader fra tabellen
    if (selectAll.tryExecuteStep() == SQLITE_ROW) {
        int i = 1;
        do {
            //Hente kolonner fra databasen
            int LeaseId = selectAll.getColumn("LeaseId");
            int ssn = selectAll.getColumn("ssn");
            std::string RegNr = selectAll.getColumn("RegNr");
            std::string startDate = selectAll.getColumn("startDate");
            int daysOfLease = selectAll.getColumn("daysOfLease");
            int status = selectAll.getColumn("status");
            int TotPrice = selectAll.getColumn("TotPrice");

            std::cout << i << ". Lease id: " << LeaseId << ", Social security number: " << ssn <<
                ", Registration number: " << RegNr << ", Start of lease: "
                << startDate << ", Days of lease: " << daysOfLease << ", Status: " << status
                << ", Total price of lease: " << TotPrice << "$" << std::endl;
            i++;
        }
        while (selectAll.tryExecuteStep() == SQLITE_ROW);
    }
    else {
        std::cout << "No leases found" << std::endl;
    }
}

// Funksjon som teller antall aktive utleier
void rentalDatabase::countActiveLease() const{

    // Sql kommandoen
    SQLite::Statement selectActive(AccessDB.db, "SELECT COUNT(*) FROM leases WHERE status = 1");

    if (selectActive.executeStep()) {
        int count = selectActive.getColumn(0);
        std::cout << "Number of active leases: " << count << std::endl;
    }
    else {
        std::cout << "Failed" << std::endl;
    }
}

// Funksjon som teller alle fullførte utleier
void rentalDatabase::countCompletedLease() const{

    // Sql kommandoen
    SQLite::Statement selectCompletedLease(AccessDB.db, "SELECT COUNT(*) FROM leases WHERE status = 0");

    if (selectCompletedLease.executeStep()) {
        int count = selectCompletedLease.getColumn(0);
        std::cout << "Number of completed leases: " << count << std::endl;
    }
    else {
        std::cout << "Failed" << std::endl;
    }
}

// Funksjon som håndterer start og ending av en utleie
void rentalDatabase::startAndEndLease(const int availability, const int LeaseId) const {

    // Oppdaterer bil tabellen
    SQLite::Statement updateCar(AccessDB.db,
       "UPDATE cars SET availability = ? "
       "WHERE RegNr IN (SELECT RegNr FROM leases WHERE LeaseId = ?)");

    updateCar.bind(1, availability);
    updateCar.bind(2, LeaseId);
    if (updateCar.exec() == 1) {
        std::cout << "Car updated" << std::endl;
    }
    else {
        std::cout << "Car error" << std::endl;
    }
}

// Funksjon som sjekker om utleie er ledig
bool rentalDatabase::isLeaseAvailable(const int LeaseId) const {
    SQLite::Statement carAvailable(AccessDB.db,
        "SELECT availability FROM cars, leases WHERE leases.RegNr = cars.RegNr AND LeaseId = ?");
    carAvailable.bind(1, LeaseId);
    if (carAvailable.executeStep()) {
        int availability = carAvailable.getColumn(0).getInt();
        if (availability == 1) {
            return true;
        }
    }
    return false;
}



