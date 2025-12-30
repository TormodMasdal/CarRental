#ifndef RENTALHANDLER_H
#define RENTALHANDLER_H

#include "model/rentalDatabase.h"
#include "model/accessDB.h"
#include "model/carDatabase.h"
#include "model/customerDatabase.h"

// Håndterer brukerinput og setter det inn i rental tabellen
class rentalHandler {
public:

    // Instanse av klasser
    accessDB AccessDB;
    rentalDatabase lease;
    customerDatabase customer;
    carDatabase car;

    void registerLeases() const;
    void handleRegisteredLeases() const;
    void assignRentalBySearch() const;

};
#endif //RENTALHANDLER_H
