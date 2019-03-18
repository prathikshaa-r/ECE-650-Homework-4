/**
 * March 18, 2019
 * todo: bug - tables all created in lowercase
 */

#include "exerciser.h"

// using namespace std;
// using namespace pqxx;

void exercise(pqxx::connection *C) {
  std::string drop = "DROP TABLE IF EXISTS ";
  // drop player
  execute_stmt(C, drop + "PLAYER", "drop table player");

  // drop team
  execute_stmt(C, drop + "TEAM", "drop table team");

  // drop state
  execute_stmt(C, drop + "STATE", "drop table state");

  // drop color
  execute_stmt(C, drop + "COLOR", "drop table color");

  // create color
  std::string create_color = "CREATE TABLE COLOR ("
                             "COLOR_ID INT PRIMARY KEY     NOT NULL,"
                             "NAME           TEXT    NOT NULL"
                             ");";
  execute_stmt(C, create_color, "create table color");

  // create state
  std::string create_state = "CREATE TABLE STATE ("
                             "STATE_ID INT PRIMARY KEY     NOT NULL,"
                             "NAME                 TEXT    NOT NULL"
                             ");";
  execute_stmt(C, create_state, "create table state");

  // create team
  std::string create_team = "CREATE TABLE TEAM ("
                            "TEAM_ID INT PRIMARY KEY     NOT NULL,"
                            "NAME                TEXT    NOT NULL,"
                            "STATE_ID            INT     NOT NULL,"
                            "COLOR_ID            INT     NOT NULL,"
                            "WINS                INT     NOT NULL,"
                            "LOSSES              INT     NOT NULL,"
                            "FOREIGN KEY(STATE_ID) REFERENCES STATE(STATE_ID),"
                            "FOREIGN KEY(COLOR_ID) REFERENCES COLOR(COLOR_ID)"
                            ");";
  execute_stmt(C, create_team, "create table team");

  // create player
  std::string create_player = "CREATE TABLE PLAYER ("
                              "PLAYER_ID INT PRIMARY KEY     NOT NULL,"
                              "TEAM_ID               INT     NOT NULL,"
                              "UNIFORM_NUM           INT     NOT NULL,"
                              "FIRST_NAME            TEXT    NOT NULL,"
                              "LAST_NAME            TEXT    NOT NULL,"
                              "MPG               INT     NOT NULL,"
                              "PPG               INT     NOT NULL,"
                              "RPG               INT     NOT NULL,"
                              "APG               INT     NOT NULL,"
                              "SPG               REAL    NOT NULL,"
                              "BPG               REAL    NOT NULL,"
                              "FOREIGN KEY(TEAM_ID) REFERENCES TEAM(TEAM_ID)"
                              ");";
  execute_stmt(C, create_player, "create table player");
}

pqxx::result execute_stmt(pqxx::connection *C, std::string sql,
                          std::string desc) {
  pqxx::work w(*C);
  pqxx::result r;
  try {
    r = w.exec(sql.c_str());
    w.commit();
  } catch (const std::exception &e) {
    w.abort();
    std::cerr << "Error: " << desc << ": " << e.what() << std::endl;
    throw;
  }
  std::cerr << "Success: " << desc << std::endl;
  return r;
}

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
