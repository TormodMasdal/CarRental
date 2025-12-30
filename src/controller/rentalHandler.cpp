#include "controller/rentalHandler.h"
#include "controller/carHandler.h"

#include <iostream>

// Henter opplysninger om leieavtalen som skal registreres
void rentalHandler::registerLeases() const {

    // Bruker input for personnummer
    int ssn;
    std::cout << "Enter social security number of customer: ";
    std::cin >> ssn;

    if (!customer.checkCustomerExist(ssn)) {
        std::cout << "Customer not found, please enter a valid SSN" << std::endl;
        return;
    }

    std::string RegNr;
    std::cout << "Enter Registration number: ";
    std::cin >> RegNr;

    // Sjekker om bilen eksisterer
    if (!car.checkCarExist(RegNr)) {
        std::cout << "Car not found, please enter a valid RegNr" << std::endl;
        return;
    }

    // Sjekker om bilen allerede er i bruk
    if (!car.isCarAvailable(RegNr)) {
        std::cout << "Car is not available" << std::endl;
        return;
    }

    // Bruker input for start dato
    std::string startDate;
    std::cout << "Enter start date of lease in YYYY-MM-DD format: ";
    std::cin >> startDate;

    // Bruker input for daget bilen er utleid
    int daysOfLease;
    std::cout << "Enter number of days the car is on lease: ";
    std::cin >> daysOfLease;

    // 0 for aktive leier, 1 for ferdige leier, og 2 for planlagte leier
    int status;
    std::cout << "If lease start right away enter 0, else enter 2: ";
    std::cin >> status;

    // Hvis leien starter i dag, reserver bilen
   if (status == 0) {
        car.reserveCar(RegNr);
    }

    // Registrerer leien i databasen
    lease.RentalInsert(ssn, RegNr, startDate, daysOfLease, status);
}

// Stater og slutter lån av bil
void rentalHandler::handleRegisteredLeases() const {

    // Bruker input for å finne lease id
    int LeaseId;
    std::cout << "Enter id of the lease to finish or start: ";
    std::cin >> LeaseId;

    // Bruker input for å sette status for lease
    int status;
    std::cout << "If you want to start the lease, insert 0, if you want to end the lease, insert 1: ";
    std::cin >> status;

    // Sjekker om det er mulig å starte leien nå
    if (status == 0) {
        if (!lease.isLeaseAvailable(LeaseId)){
                std::cout << "Car is not available" << std::endl;
                return;
            }
        }

    // Gjør bilen utilgjengelig, hvis status = 0, gjør den tilgjengelig hvis status = 1
    lease.startAndEndLease(status, LeaseId);

    // Oppdaterer status på utleien
    lease.RentalUpdate(LeaseId, status);

}


