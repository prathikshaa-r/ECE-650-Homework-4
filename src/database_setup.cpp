#include "database_setup.h"
#include <fstream>
#include <string>

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
  //  std::cerr << "Success: " << desc << std::endl;
  return r;
}

void drop_tables(pqxx::connection *C) {
  std::string drop = "DROP TABLE IF EXISTS ";
  // drop player
  execute_stmt(C, drop + "Player", "drop table player");

  // drop team
  execute_stmt(C, drop + "Team", "drop table team");

  // drop state
  execute_stmt(C, drop + "State", "drop table state");

  // drop color
  execute_stmt(C, drop + "Color", "drop table color");
}

void create_tables(pqxx::connection *C) {
  // create color
  std::string create_color = "CREATE TABLE Color ("
                             "color_id             SERIAL PRIMARY KEY,"
                             "name                 TEXT    NOT NULL"
                             ");";
  execute_stmt(C, create_color, "create table color");

  // create state
  std::string create_state = "CREATE TABLE State ("
                             "state_id             SERIAL PRIMARY KEY,"
                             "name                 TEXT    NOT NULL"
                             ");";
  execute_stmt(C, create_state, "create table state");

  // create team
  std::string create_team =
      "CREATE TABLE Team ("
      "team_id             SERIAL PRIMARY KEY,"
      "name                TEXT    NOT NULL,"
      "state_id            INT     NOT NULL,"
      "color_id            INT     NOT NULL,"
      "wins                INT     NOT NULL,"
      "losses              INT     NOT NULL,"
      "FOREIGN KEY(state_id) REFERENCES State(state_id) ON DELETE CASCADE,"
      "FOREIGN KEY(color_id) REFERENCES Color(color_id) ON DELETE CASCADE"
      ");";
  execute_stmt(C, create_team, "create table team");

  // create player
  std::string create_player =
      "CREATE TABLE Player ("
      "player_id             SERIAL PRIMARY KEY,"
      "team_id               INT     NOT NULL,"
      "uniform_num           INT     NOT NULL,"
      "first_name            TEXT    NOT NULL,"
      "last_name             TEXT    NOT NULL,"
      "mpg                   INT     NOT NULL,"
      "ppg                   INT     NOT NULL,"
      "rpg                   INT     NOT NULL,"
      "apg                   INT     NOT NULL,"
      "spg                   REAL    NOT NULL,"
      "bpg                   REAL    NOT NULL,"
      "FOREIGN KEY(team_id) REFERENCES Team(team_id) ON DELETE CASCADE"
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

  if (state_src.is_open() && (!(state_src.eof()))) {
    update_state(C, state_src);
    state_src.close();
  } else {
    std::cerr << "Failed to open state.txt" << std::endl;
    // throw exception instead of exiting
    exit(EXIT_FAILURE);
  }

  if (team_src.is_open() && (!(team_src.eof()))) {
    update_team(C, team_src);
    team_src.close();
  } else {
    std::cerr << "Failed to open team.txt" << std::endl;
    // throw exception instead of exiting
    exit(EXIT_FAILURE);
  }

  if (player_src.is_open() && (!(player_src.eof()))) {
    update_player(C, player_src);
    player_src.close();
  } else {
    std::cerr << "Failed to open player.txt" << std::endl;
    // throw exception instead of exiting
    exit(EXIT_FAILURE);
  }
}

void update_state(pqxx::connection *C, std::istream &state_istream) {
  std::string curr;

  std::vector<std::string> values;

  while (std::getline(state_istream, curr)) {
    //    std::cout << curr << std::endl;
    values = read_line(curr);
    // todo: add error checking
    // todo: check no. of columns extracted
    add_state(C, values[0]);
  }
}

void update_color(pqxx::connection *C, std::istream &color_istream) {
  std::string curr;

  std::vector<std::string> values;

  while (std::getline(color_istream, curr)) {
    //    std::cout << curr << std::endl;
    values = read_line(curr);
    // todo: add error checking
    // todo: check no. of columns extracted
    add_color(C, values[0]);
  }
}

void update_team(pqxx::connection *C, std::istream &team_istream) {
  std::string curr;
  std::vector<std::string> values;

  while (std::getline(team_istream, curr)) {
    //    std::cout << curr << std::endl;
    values = read_line(curr);
    // todo: add error checking
    // todo: check no. of columns extracted
    try {
      add_team(C, values[0], std::stoi(values[1], nullptr),
               std::stoi(values[2], nullptr), std::stoi(values[3], nullptr),
               std::stoi(values[4], nullptr));
    } catch (std::exception &e) {
      std::cerr << "update_team: " << e.what() << std::endl;
      throw;
    }
  }
}

void update_player(pqxx::connection *C, std::istream &player_istream) {
  std::string curr;
  std::vector<std::string> values;

  while (std::getline(player_istream, curr)) {
    //    std::cout << curr << std::endl;
    values = read_line(curr);
    // todo: add error checking
    // todo: check no. of columns extracted
    try {
      add_player(C, std::stoi(values[0], nullptr), // int team_id
                 std::stoi(values[1], nullptr),    // int uniform_num
                 values[2], values[3],             // first_name, last_name
                 std::stoi(values[4], nullptr),
                 std::stoi(values[5], nullptr), // mpg, ppg
                 std::stoi(values[6], nullptr),
                 std::stoi(values[7], nullptr), // rpg, apg
                 std::stod(values[8], nullptr),
                 std::stod(values[9], nullptr) // spg, bpg
      );
    } catch (std::exception &e) {
      std::cerr << "update_player: " << e.what() << std::endl;
      throw;
    }
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
