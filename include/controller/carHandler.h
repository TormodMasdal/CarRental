#ifndef CARHANDLER_H
#define CARHANDLER_H

#include "model/carDatabase.h"
#include "model/accessDB.h"

// Håndterer brukerinput og setter det inn i car tabellen
class carHandler {
public:

    // Instanse av klasser
    accessDB AccessDB;
    carDatabase car;

    void handleAddCar() const;
    void handleUpdateCar() const;
    void handleDeleteCar() const;
    void handleSearchCar() const;

};
#endif
