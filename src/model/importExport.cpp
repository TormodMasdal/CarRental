#include "model/importExport.h"

#include <iostream>
#include <fstream>
#include <string>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>

// Denne funksjonen eksporterer all informasjon fra databasen til en JSON fil
bool importExport::ExportJSON(SQLite::Database &db) {

    const std::string filePath = "resources/carRental.json";

    // Lager et JSON dokument
    rapidjson::Document databaseJSON;
    databaseJSON.SetObject();
    rapidjson::Document::AllocatorType& memoryAllocator = databaseJSON.GetAllocator();

    // Lager arrays for hver tabell
    rapidjson::Value carsArray(rapidjson::kArrayType);
    rapidjson::Value customersArray(rapidjson::kArrayType);
    rapidjson::Value leasesArray(rapidjson::kArrayType);

    // Eksporterer cars tabellen
    SQLite::Statement queryCars(db, "SELECT * FROM cars");
    while (queryCars.executeStep()) {
        rapidjson::Value carObject(rapidjson::kObjectType);

        // Legger til bil registrerings nummer i bil objektet
        rapidjson::Value regNrValue;
        std::string regNr = queryCars.getColumn("RegNr").getString();
        regNrValue.SetString(regNr.c_str(), regNr.length(), memoryAllocator);
        carObject.AddMember("RegNr", regNrValue, memoryAllocator);

        // Legger til bil modell nummer i bil objektet
        rapidjson::Value modelValue;
        std::string model = queryCars.getColumn("model").getString();
        modelValue.SetString(model.c_str(), model.length(), memoryAllocator);
        carObject.AddMember("model", modelValue, memoryAllocator);
        carObject.AddMember("year", queryCars.getColumn("year").getInt(), memoryAllocator);
        carObject.AddMember("odometerKm", queryCars.getColumn("odometerKm").getInt(), memoryAllocator);

        // Legger til bil merke i bil objektet
        rapidjson::Value brandValue;
        std::string brand = queryCars.getColumn("brand").getString();
        brandValue.SetString(brand.c_str(), brand.length(), memoryAllocator);
        carObject.AddMember("brand", brandValue, memoryAllocator);
        carObject.AddMember("pricePrDay", queryCars.getColumn("pricePrDay").getInt(), memoryAllocator);
        carObject.AddMember("availability", queryCars.getColumn("availability").getInt(), memoryAllocator);

        // Legger til bil objektet i bil arrayet
        carsArray.PushBack(carObject, memoryAllocator);
    }

    // Eksporterer customers tabellen
    SQLite::Statement queryCustomers(db, "SELECT * FROM customers");
    while (queryCustomers.executeStep()) {
        rapidjson::Value customerObject(rapidjson::kObjectType);

        // Legger til customers egenskaper i kunde objektet
        customerObject.AddMember("ssn", queryCustomers.getColumn("ssn").getInt(), memoryAllocator);

        // Legger til fornavn i kunde objektet
        rapidjson::Value firstNameValue;
        std::string firstName = queryCustomers.getColumn("firstName").getString();
        firstNameValue.SetString(firstName.c_str(), firstName.length(), memoryAllocator);
        customerObject.AddMember("firstName", firstNameValue, memoryAllocator);

        // Legger til etternavn i kunde objektet
        rapidjson::Value lastNameValue;
        std::string lastName = queryCustomers.getColumn("lastName").getString();
        lastNameValue.SetString(lastName.c_str(), lastName.length(), memoryAllocator);
        customerObject.AddMember("lastName", lastNameValue, memoryAllocator);
        customerObject.AddMember("phoneNumber", queryCustomers.getColumn("phoneNumber").getInt(), memoryAllocator);

        // Legger til epost i kunde i objektet
        rapidjson::Value emailValue;
        std::string email = queryCustomers.getColumn("email").getString();
        emailValue.SetString(email.c_str(), email.length(), memoryAllocator);
        customerObject.AddMember("email", emailValue, memoryAllocator);

        // Legger til kunde objektet i kunde arrayet
        customersArray.PushBack(customerObject, memoryAllocator);
    }

    // Eksporterer leases tabellen
    SQLite::Statement queryLeases(db, "SELECT * FROM leases");
    while (queryLeases.executeStep()) {
        rapidjson::Value leaseObject(rapidjson::kObjectType);

        leaseObject.AddMember("LeaseId", queryLeases.getColumn("LeaseId").getInt(), memoryAllocator);
        leaseObject.AddMember("ssn", queryLeases.getColumn("ssn").getInt(), memoryAllocator);

        // Legger til registreringsnummeret i lease objektet
        rapidjson::Value regNrValue;
        std::string regNr = queryLeases.getColumn("RegNr").getString();
        regNrValue.SetString(regNr.c_str(), regNr.length(), memoryAllocator);
        leaseObject.AddMember("RegNr", regNrValue, memoryAllocator);

        // Legger til start date, days of lease og status i lease objektet
        rapidjson::Value startDateValue;
        std::string startDate = queryLeases.getColumn("startDate").getString();
        startDateValue.SetString(startDate.c_str(), startDate.length(), memoryAllocator);

        leaseObject.AddMember("startDate", startDateValue, memoryAllocator);
        leaseObject.AddMember("daysOfLease", queryLeases.getColumn("daysOfLease").getInt(), memoryAllocator);
        leaseObject.AddMember("status", queryLeases.getColumn("status").getInt(), memoryAllocator);

        // Legger til lease objektet i lease arrayet
        leasesArray.PushBack(leaseObject, memoryAllocator);
    }

    // Legger til arrays i JSON filen
    databaseJSON.AddMember("cars", carsArray, memoryAllocator);
    databaseJSON.AddMember("customers", customersArray, memoryAllocator);
    databaseJSON.AddMember("leases", leasesArray, memoryAllocator);

    // Lager en StringBuffer for å lagre JSON strengen
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter writer(buffer);
    databaseJSON.Accept(writer);

    // Skriver JSON strengen til fil
    std::ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << filePath << std::endl;
    }

    outputFile << buffer.GetString();
    outputFile.close();

    std::cout << "Successfully exported database to " << filePath << std::endl;
    return true;
}

// Denne funksjonen importerer data fra en JSON fil til databasen
void importExport::ImportJSON(SQLite::Database& db) {

    const std::string filePath = "resources/carRental.json";

    // Åpner JSON-filen
    std::ifstream databaseJSON(filePath);
    if (!databaseJSON.is_open()) {
        std::cerr << "Could not open JSON file" << filePath << std::endl;
        return;
    }

    // Bruker RapidJSON for å parse JSON-filen
    rapidjson::IStreamWrapper importStream(databaseJSON);
    rapidjson::Document document;
    document.ParseStream(importStream);

    if (document.HasParseError()) {
        std::cerr << "JSON parse error, JSON file is empty" << std::endl;
        return;
    }

    // Importerer biler
    if (document.HasMember("cars") && document["cars"].IsArray()) {
        const rapidjson::Value& cars = document["cars"];

        // Tømmer eksisterende cars tabell
        db.exec("DELETE FROM cars");

        // Legger til nye cars
        for (size_t i = 0; i < cars.Size(); i++) {
            const rapidjson::Value& car = cars[i];

            // Bruk av SQLiteCpp statement mønster basert på eksempler fra offisiell dokumentasjon
            SQLite::Statement insert(db,
                "INSERT INTO cars "
                "(RegNr, model, year, odometerKm, brand, pricePrDay, availability) "
                "VALUES (?, ?, ?, ?, ?, ?, ?)");

            // Binder en parameter til hver kolonne i SQL-setningen ("?" er 1, osv...)
            insert.bind(1, car["RegNr"].GetString());
            insert.bind(2, car["model"].GetString());
            insert.bind(3, car["year"].GetInt());
            insert.bind(4, car["odometerKm"].GetInt());
            insert.bind(5, car["brand"].GetString());
            insert.bind(6, car["pricePrDay"].GetInt());
            insert.bind(7, car["availability"].GetInt());
            insert.exec();
        }
        std::cout << "Imported: " << cars.Size() << " cars." << std::endl;
    }

    // Importerer kunder
    if (document.HasMember("customers") && document["customers"].IsArray()) {
        const rapidjson::Value& customers = document["customers"];

        // Tømmer eksisterende customers tabell
        db.exec("DELETE FROM customers");

        // Legger til nye kunder
        for (size_t i = 0; i < customers.Size(); i++) {
            const rapidjson::Value& customer = customers[i];

            SQLite::Statement insert(db,
                "INSERT INTO customers "
                "(ssn, firstName, lastName, phoneNumber, email) "
                "VALUES (?, ?, ?, ?, ?)");

            insert.bind(1, customer["ssn"].GetInt());
            insert.bind(2, customer["firstName"].GetString());
            insert.bind(3, customer["lastName"].GetString());
            insert.bind(4, customer["phoneNumber"].GetInt());
            insert.bind(5, customer["email"].GetString());

            insert.exec();
        }
        std::cout << "Imported: " << customers.Size() << " customers." << std::endl;
    }

    // Importerer utleier
    if (document.HasMember("leases") && document["leases"].IsArray()) {
        const rapidjson::Value& leases = document["leases"];

        // Tømmer eksisterende leases tabell
        db.exec("DELETE FROM leases");

        // Legger til nye utleier
        for (size_t i = 0; i < leases.Size(); i++) {
            const rapidjson::Value& lease = leases[i];

            SQLite::Statement insert(db,
                "INSERT INTO leases "
                "(LeaseId, ssn, RegNr, startDate, daysOfLease, status) "
                "VALUES (?, ?, ?, ?, ?, ?)");

            insert.bind(1, lease["LeaseId"].GetInt());
            insert.bind(2, lease["ssn"].GetInt());
            insert.bind(3, lease["RegNr"].GetString());
            insert.bind(4, lease["startDate"].GetString());
            insert.bind(5, lease["daysOfLease"].GetInt());
            insert.bind(6, lease["status"].GetInt());

            insert.exec();
        }
        std::cout << "Imported: " << leases.Size() << " leases." << std::endl;
    }
    std::cout << "--------------------------" << std::endl;
    std::cout << "Imported information to database from: " << filePath << std::endl;
}