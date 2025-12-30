#include "controller/carHandler.h"

#include <iostream>

// Får opplysninger fra brukeren om bilen som skal legges til
void carHandler::handleAddCar() const{

    // Bruker input for å skrive inn registrerings nummer
    std::string RegNr;
    std::cout << "Enter Registration number: ";
    std::cin >> RegNr;

    // Bruker input for å skrive inn bil modell
    std::string model;
    std::cout << "Enter car model: ";
    std::cin >> model;

    // Bruker input for å skrive når bilen var solgt
    int year;
    std::cout << "Enter the year the car sold: ";
    std::cin >> year;

    // Bruker input for å skrive inn bilens totale kilometer avstand
    int odometerKm;
    std::cout << "Enter total km distance of the car: ";
    std::cin >> odometerKm;

    // Bruker input for å skrive bilens merke
    std::string brand;
    std::cout << "Enter the cars brand: ";
    std::cin >> brand;

    // Bruker input for å skrive bilens pris per dg
    int pricePerDay;
    std::cout << "Enter price per day for the vehicle: ";
    std::cin >> pricePerDay;

    // Kaller på insert bil funksjonen og bruker variablene som er blitt initialisert som parametere
    car.CarInsert(RegNr, model, year, odometerKm, brand, pricePerDay);
}

// Får opplysninger for å oppdatere odometeret og pris per dag
void carHandler::handleUpdateCar() const{

    // Bruker input for å finne registreringsnummeret til bilen
    std::string RegNr;
    std::cout << "Enter registration number: ";
    std::cin >> RegNr;

    // Sjekker om bilen eksisterer i databasen
    if (!car.checkCarExist(RegNr)) {
        std::cout << "Car not found, please enter a valid RegNr" << std::endl;
        return;
    }

    // Bruker input for å skrive inn den nye kilometeravstanden
    int odometerKm;
    std::cout << "Enter new distance traveled in km: ";
    std::cin >> odometerKm;

    // Bruker input for å skrive inn den nye prisen per dag
    int pricePerDay;
    std::cout << "Enter price per day for the vehicle: ";
    std::cin >> pricePerDay;

    // Kaller på update bil funksjonen, og bruker variablene som er blitt initialisert som parametere
    car.CarUpdate(RegNr, odometerKm, pricePerDay);
}

// Får opplysning om hvilken bil som skal fjernes
void carHandler::handleDeleteCar() const{

    // Bruker input for å finne registrerings nummer og slette
    std::string RegNr;
    std::cout << "Enter registration number to delete: ";
    std::cin >> RegNr;

    // Sjekker om bilen eksisterer
    if (!car.checkCarExist(RegNr)) {
        std::cout << "Car not found, please enter a valid RegNr" << std::endl;
        return;
    }

    // Kaller på slett bil funksjonen
    car.CarDelete(RegNr);
}

// Får opplysninger om hvilken bokstaver vi skal søke på
void carHandler::handleSearchCar() const {
    std::string model;
    std::cout << "Search car model: ";
    std::cin >> model;

    car.searchCar(model);
}
