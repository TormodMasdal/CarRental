#ifndef RENTALDATABASE_H
#define RENTALDATABASE_H

#include <SQLiteCpp/Database.h>
#include "accessDB.h"

// Klasse for all kommunikasjon med rental tabellen i databasen
class rentalDatabase {
public:
    accessDB AccessDB;

    // Ingen av funksjonene skal endre på AccessDB, Dermed CONST
    void RentalInsert(int ssn, const std::string &RegNr,
    const std::string &startDate, int daysOfLease, int status) const;

    void RentalUpdate(int LeaseId, int status) const;
    void RentalDelete(int LeaseId) const;
    void RentalSelectAll() const;
    void countActiveLease() const;
    void countCompletedLease() const;
    void startAndEndLease(int availability, int LeaseId) const;

    bool isLeaseAvailable(int LeaseId) const;

};
#endif //RENTALDATABASE_H
