#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include "SQLiteCpp/SQLiteCpp.h"

// Håndterer Export av databasen til en JSON fil og import fra JSON filen.
class importExport {

public:

    static void ImportJSON(SQLite::Database& db);
    static bool ExportJSON(SQLite::Database& db);

};
#endif //JSONHANDLER_H
