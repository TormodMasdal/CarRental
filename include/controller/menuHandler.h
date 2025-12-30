#ifndef HANDLER_CONTROLLER_H
#define HANDLER_CONTROLLER_H

#include <string>

#include "model/customerDatabase.h"
#include "model/carDatabase.h"
#include "model/rentalDatabase.h"
#include "controller/carHandler.h"
#include "controller/customerHandler.h"
#include "controller/rentalHandler.h"

// Håndterer brukerinput og sender brukeren til bestemt meny
class menuHandler {
public:

    static auto inputHelper(const std::string &input);
    void run();

private:

    // Lager instanse av alle Database relaterte klasser
    customerHandler CustomerHandler;
    carHandler CarHandler;
    customerDatabase customer;
    carDatabase car;
    rentalHandler RentalHandler;
    rentalDatabase rental;
    accessDB accessDB;

    void handleCarMenu() const;
    void handleCustomerMenu() const;
    void handleRentalMenu() const;
    void handleRentalRegMenu() const;
    void handleRentalStart_StopMenu() const;
    void handleStatisticsMenu() const;

    static void waitAfterSelect();
    static void waitTwoSec();
};
#endif // HANDLER_CONTROLLER_H
