# CMAKE Version
cmake_minimum_required(VERSION 3.30)

# Project Name
project(CarRental)

# C++ 17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(sqlite3 sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC sqlite3)

# SQLiteCpp library
add_library(sqlitecpp
        sqlitecpp/src/Backup.cpp
        sqlitecpp/src/Column.cpp
        sqlitecpp/src/Database.cpp
        sqlitecpp/src/Exception.cpp
        sqlitecpp/src/Savepoint.cpp
        sqlitecpp/src/Statement.cpp
        sqlitecpp/src/Transaction.cpp
)
if (UNIX)
    target_link_libraries(sqlite3 pthread dl)
endif ()

target_include_directories(sqlitecpp PUBLIC sqlitecpp/include)
target_link_libraries(sqlitecpp sqlite3)

# Program executable
add_executable(CarRental
        main.cpp

        include/model/CarDatabase.h
        src/model/CarDatabase.cpp

        include/model/CustomerDatabase.h
        src/model/CustomerDatabase.cpp

        include/model/RentalDatabase.h
        src/model/RentalDatabase.cpp

        src/view/menu_view.cpp
        include/view/menu_view.h

        src/controller/menuHandler.cpp
        include/controller/menuHandler.h

        src/controller/carHandler.cpp
        include/controller/carHandler.h

        src/controller/customerHandler.cpp
        include/controller/customerHandler.h

        src/controller/rentalHandler.cpp
        include/controller/rentalHandler.h

        src/model/importExport.cpp
        include/model/importExport.h
)

# linker order: sqlitecpp first, then sqlite3
target_link_libraries(CarRental
        sqlitecpp
        sqlite3
)

# RapidJSON library
find_package(RapidJSON REQUIRED)
target_include_directories(CarRental PRIVATE ${RAPIDJSON_INCLUDE_DIRS})
target_include_directories(CarRental PRIVATE external/rapidjson/include)
target_include_directories(CarRental PRIVATE include)
