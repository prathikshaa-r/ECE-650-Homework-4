#include <iostream>
#include <pqxx/pqxx>

#include "database_setup.h"
#include "exerciser.h"

// using namespace std;
// using namespace pqxx;
static int DEBUG_PRINT = 0;

int main(int argc, char *argv[]) {

  if (argc == 2) {
    DEBUG_PRINT = 1;
  }

  // Allocate & initialize a Postgres connection object
  pqxx::connection *C;

  try {
    // Establish a connection to the database
    // Parameters: database name, user name, user password
    C = new pqxx::connection("dbname=ACC_BBALL user=postgres password=passw0rd "
                             "hostaddr=0.0.0.0 port=5432");

    if (C->is_open()) {
      std::cout << "Opened database successfully: " << C->dbname() << std::endl;
    } else {
      std::cout << "Can't open database" << std::endl;
      return EXIT_FAILURE;
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  // TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL
  // database
  //      load each table with rows from the provided source txt files
  drop_tables(C);
  create_tables(C);

  populate_tables_from_src_files(C);

  exercise(C);

  // Close database connection
  C->disconnect();

  return EXIT_SUCCESS;
}
