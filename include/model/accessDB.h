#ifndef ACCESSDB_H
#define ACCESSDB_H

#include <SQLiteCpp/Database.h>

// Klasse som kan kalles på for å få tilgang til databasen
class accessDB {
public:

    SQLite::Database db;

    // Konstruktør
    accessDB() : db("CarRental.sqlite", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {

        // Alle SQL insertions følger fremmed nøkkel regler
        db.exec("PRAGMA foreign_keys = ON;");
    };

};
#endif //ACCESSDB_H
