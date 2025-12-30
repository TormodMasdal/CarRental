#ifndef CARDATABASE_H
#define CARDATABASE_H

#include <SQLiteCpp/Database.h>
#include "accessDB.h"

// Klasse for all kommunikasjon med car tabellen i databasen
class carDatabase {
public:

    accessDB AccessDB;

    // Ingen av funksjonene skal endre på AccessDB, Dermed CONST
    void CarInsert(const std::string &RegNr,
        const std::string &model,
        int year,
        int odometerKm,
        const std::string &brand,
        int pricePrDay) const;

    void CarUpdate(const std::string &RegNr, int odometerKm, int pricePrDay) const;
    void CarDelete(const std::string &RegNr) const;
    void CarSelectAll() const;
    void countCar() const;
    void reserveCar(const std::string &RegNr) const;
    void searchCar(std::string search) const;

    bool checkCarExist(const std::string &RegNr) const;
    bool isCarAvailable(const std::string &RegNr) const;

};
#endif // CARDATABASE_H
