#include "model/carDatabase.h"

#include <sqlite3.h>
#include <iostream>


// Insert ny rad i tabellen Cars
void carDatabase::CarInsert(const std::string &RegNr, const
    std::string &model, const int year, const int odometerKm, const std::string &brand,
    const int pricePrDay) const {

    // Sql kommando
    SQLite::Statement insert(AccessDB.db,
        "INSERT INTO cars "
        "(RegNr, model, year, odometerKm, brand, pricePrDay, availability) "
        "VALUES (?, ?, ?, ?, ?, ?, 1)"); // Nye biler skal alltid være tilgjengelig, dermed 1

    // Binder parametrene til values
    insert.bind(1, RegNr);
    insert.bind(2, model);
    insert.bind(3, year);
    insert.bind(4, odometerKm);
    insert.bind(5, brand);
    insert.bind(6, pricePrDay);


    // Eksekverer og sjekker om det går som det skal
    if (insert.exec() == 1) {
        std::cout << "Inserted car successfully" << std::endl;
    }
    else {
        std::cout << "Failed to insert car" << std::endl;
    }
}

// Oppdater bestemte rader i tabellen Cars
void carDatabase::CarUpdate(const std::string &RegNr, const int odometerKm,
    const int pricePrDay) const{

    // Sql kommando
    SQLite::Statement update(AccessDB.db, "UPDATE cars SET odometerKm = ?, "
                                 "pricePrDay = ? WHERE RegNr = ?");

    //Binder parametrene til Sql kommandoen
    update.bind(1, odometerKm);
    update.bind(2, pricePrDay);
    update.bind(3, RegNr);

    // Eksekverer og sjekker om det går som det skal
    if (update.exec() == 1) {
        std::cout << "Updated car successfully" << std::endl;
    }
    else {
        std::cout << "Failed to update car" << std::endl;
    }

}

// Fjern en bestemt bil fra tabellen Cars
void carDatabase::CarDelete(const std::string &RegNr) const{

    // Sql kommando
    SQLite::Statement remove(AccessDB.db, "DELETE FROM cars WHERE RegNr = ?");

    // Binder parameteret til Sql kommandoen
    remove.bind(1, RegNr);

    // Hvis antall endret rader = 1
    if (remove.exec() == 1) {
        std::cout << "Car was removed successfully" <<std::endl;
    }
    else {
        std::cout << "Car not found" << std::endl;
    }
}

// Vis alle rader i tabellen Cars
void carDatabase::CarSelectAll() const {

    // Sql kommando
    SQLite::Statement selectAll(AccessDB.db, "SELECT * FROM cars");

    // Henter alle rader fra tabellen
    if (selectAll.tryExecuteStep() == SQLITE_ROW) {
        int i = 1;
        do {
            //Hente kolonner
            std::string RegNr = selectAll.getColumn("RegNr");
            std::string model = selectAll.getColumn("model");
            int year = selectAll.getColumn("year");
            int odometerKm = selectAll.getColumn("odometerKm");
            std::string brand = selectAll.getColumn("brand");
            int pricePrDay = selectAll.getColumn("pricePrDay");
            int availability = selectAll.getColumn("availability");

            std::cout << i << ". RegNr: " << RegNr << ", model: " << model << ", year: " << year << ", odometerKm: "
            << odometerKm << "km, brand: " << brand << ", price per day: " << pricePrDay <<
                "$ , availability: " << availability << std::endl;
            i++;
        }
        while (selectAll.tryExecuteStep() == SQLITE_ROW);
    }
    else {
        std::cout << "No cars found" << std::endl;
    }
}

// Funksjon som teller alle biler
void carDatabase::countCar() const {

    // Sql kommando
    SQLite::Statement selectAll(AccessDB.db, "SELECT COUNT(*) FROM cars");

    if (selectAll.executeStep()) {
        int count = selectAll.getColumn(0);
        std::cout << "Number of cars: " << count << std::endl;
    }
    else {
        std::cout << "Failed" << std::endl;
    }
}

// Funksjon som sjekker om bilen eksiterer
bool carDatabase::checkCarExist(const std::string &RegNr) const {
    SQLite::Statement carExist(AccessDB.db, "SELECT RegNr FROM cars WHERE RegNr = ?");
    carExist.bind(1, RegNr);

    if (carExist.executeStep() != 1) {
        return false;
    }
    return true;
}

// Funksjon som sjekker om bilen er ledig
bool carDatabase::isCarAvailable(const std::string &RegNr) const{
    {
        SQLite::Statement carAvailable(AccessDB.db, "SELECT availability FROM cars WHERE RegNr = ?");
        carAvailable.bind(1, RegNr);

        carAvailable.executeStep();
        int availability = carAvailable.getColumn(0).getInt();

        if (availability == 1) {
            return true;
        }
        return false;
    }
}

// Funksjon som reserver biler til en status
void carDatabase::reserveCar(const std::string &RegNr) const{
    SQLite::Statement update(AccessDB.db, "UPDATE cars SET availability = 0 "
                                 "WHERE RegNr = ?");
    update.bind(1, RegNr);
    update.exec();
}

// Søker etter tilgjengelige biler
void carDatabase::searchCar(std::string search) const {
    SQLite::Statement Search(AccessDB.db, "SELECT * FROM cars WHERE model LIKE ? AND availability = 1");
    search = "%" + search + "%";
    Search.bind(1, search);

    // Henter alle rader fra tabellen
    if (Search.tryExecuteStep() == SQLITE_ROW) {
        int i = 1;
        do {
            //Hente kolonner fra bil tabellen
            std::string RegNr = Search.getColumn("RegNr");
            std::string model = Search.getColumn("model");
            int year = Search.getColumn("year");
            int odometerKm = Search.getColumn("odometerKm");
            std::string brand = Search.getColumn("brand");
            int pricePrDay = Search.getColumn("pricePrDay");
            int availability = Search.getColumn("availability");

            std::cout << i << ". RegNr: " << RegNr << ", model: " << model << ", year: " << year << ", odometerKm: "
            << odometerKm << "km, brand: " << brand << ", price per day: " << pricePrDay <<
                "$ , availability: " << availability << std::endl;
            i++;
        }
        while (Search.tryExecuteStep() == SQLITE_ROW);
    }
    else {
        std::cout << "No cars found" << std::endl;
    }
}