/**
 * March 18, 2019
 */

#include "exerciser.h"

// using namespace std;
// using namespace pqxx;

void exercise(pqxx::connection *C) {}

// ref:
// https://stackoverflow.com/questions/26464056/pqxx-reuse-reactivate-a-work-transaction

/*------------------------legacy-----------------------*/
// try {
//   /* Create a transactional object. */
//   pqxx::work drop_player_w(*C);

//   //    std::cerr << "Dropping table" << std::endl;
//   std::string sql = "DROP TABLE IF EXISTS COMPANY;";
//   try {
//     drop_player_w.exec(sql.c_str());
//     drop_player_w.commit();
//     //    std::cerr << "Dropped table" << std::endl;
//   } catch (const std::exception &e) {
//     drop_player_w.abort();
//     std::cerr << "Error: Drop Player: " << e.what() << std::endl;
//   }

//   pqxx::work create_player_w(*C);
//   sql = "CREATE TABLE COMPANY("
//         "ID INT PRIMARY KEY     NOT NULL,"
//         "NAME           TEXT    NOT NULL,"
//         "AGE            INT     NOT NULL,"
//         "ADDRESS        CHAR(50),"
//         "SALARY         REAL );";

//   try {
//     create_player_w.exec(sql.c_str());
//     create_player_w.commit();
//   } catch (const std::exception &e) {
//     create_player_w.abort();
//     std::cerr << "Error: Drop Player: " << e.what() << std::endl;
//   }

//   std::cout << "Table created successfully" << std::endl;
// } catch (const std::exception &e) {
//   std::cerr << e.what() << std::endl;
// }
