#ifndef CUSTOMERHANDLER_H
#define CUSTOMERHANDLER_H

#include "model/customerDatabase.h"
#include "model/accessDB.h"

// Håndterer brukerinput og setter det inn i customer tabellen
class customerHandler {
public:

    // Instanser av klasser
    accessDB AccessDB;
    customerDatabase customer;

    void handleAddCustomer() const;
    void handleUpdateCustomer() const;
    void handleDeleteCustomer() const;
    void handleSearchCustomer() const;

};
#endif //CUSTOMERHANDLER_H
