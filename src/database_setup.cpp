#include "database_setup.h"
#include <fstream>

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

void drop_tables(pqxx::connection *C) {
  std::string drop = "DROP TABLE IF EXISTS ";
  // drop player
  execute_stmt(C, drop + "PLAYER", "drop table player");

  // drop team
  execute_stmt(C, drop + "TEAM", "drop table team");

  // drop state
  execute_stmt(C, drop + "STATE", "drop table state");

  // drop color
  execute_stmt(C, drop + "COLOR", "drop table color");
}

void create_tables(pqxx::connection *C) {
  // create color
  std::string create_color = "CREATE TABLE COLOR ("
                             "COLOR_ID             SERIAL PRIMARY KEY,"
                             "NAME                 TEXT    NOT NULL"
                             ");";
  execute_stmt(C, create_color, "create table color");

  // create state
  std::string create_state = "CREATE TABLE STATE ("
                             "STATE_ID             SERIAL PRIMARY KEY,"
                             "NAME                 TEXT    NOT NULL"
                             ");";
  execute_stmt(C, create_state, "create table state");

  // create team
  std::string create_team = "CREATE TABLE TEAM ("
                            "TEAM_ID             SERIAL PRIMARY KEY,"
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
                              "PLAYER_ID             SERIAL PRIMARY KEY,"
                              "TEAM_ID               INT     NOT NULL,"
                              "UNIFORM_NUM           INT     NOT NULL,"
                              "FIRST_NAME            TEXT    NOT NULL,"
                              "LAST_NAME             TEXT    NOT NULL,"
                              "MPG                   INT     NOT NULL,"
                              "PPG                   INT     NOT NULL,"
                              "RPG                   INT     NOT NULL,"
                              "APG                   INT     NOT NULL,"
                              "SPG                   REAL    NOT NULL,"
                              "BPG                   REAL    NOT NULL,"
                              "FOREIGN KEY(TEAM_ID) REFERENCES TEAM(TEAM_ID)"
                              ");";
  execute_stmt(C, create_player, "create table player");
}

void populate_tables_from_src_files(pqxx::connection *C) {
  // while() { // reading file

  std::ifstream color_src("color.txt");
  std::ifstream state_src("state.txt");
  std::ifstream team_src("team.txt");
  std::ifstream player_src("player.txt");

  if (color_src.is_open() && (!(color_src.eof()))) {
    update_color(C, color_src);
    color_src.close();
  } else {
    std::cerr << "Failed to open color.txt" << std::endl;
    // throw exception instead of exiting
    exit(EXIT_FAILURE);
  }
}

void update_color(pqxx::connection *C, std::istream &color_istream) {
  std::string curr;

  std::vector<std::string> values;

  while (std::getline(color_istream, curr)) {
    std::cout << curr << std::endl;
    values = read_line(curr);
    add_color(C, values[0]);
  }
}

std::vector<std::string> read_line(std::string curr) {
  std::vector<std::string> values;
  std::string value;

  std::stringstream ss(curr);
  size_t column_num = 0;

  // space delimited
  while (ss >> value) {
    if (column_num != 0) {
      //        std::cout << value << std::endl;
      values.push_back(value);
    }
    column_num++;
  }

  return values;
}
