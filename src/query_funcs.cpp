#include "query_funcs.h"

// using namespace std;
// using namespace pqxx;

void add_player(pqxx::connection *C, int team_id, int jersey_num,
                std::string first_name, std::string last_name, int mpg, int ppg,
                int rpg, int apg, double spg, double bpg) {
  pqxx::work w(*C);
  pqxx::result r;

  try {
    r = w.exec(
        "INSERT INTO Player (team_id, uniform_num, first_name, last_name, "
        "mpg, ppg, rpg, apg, spg, bpg) VALUES (" +
        w.quote(team_id) + ", " + w.quote(jersey_num) + ", " +
        w.quote(first_name) + ", " + w.quote(last_name) + ", " + w.quote(mpg) +
        ", " + w.quote(ppg) + ", " + w.quote(rpg) + ", " + w.quote(apg) + ", " +
        w.quote(spg) + ", " + w.quote(bpg) + ");");
    w.commit();
  } catch (std::exception &e) {
    w.abort();
    std::cerr << "add_player: " << e.what() << std::endl;
    throw;
  }
  std::cerr << "Added player  " + first_name + " " + last_name
            << std::endl; // remove
}

void add_team(pqxx::connection *C, std::string name, int state_id, int color_id,
              int wins, int losses) {
  pqxx::work w(*C);
  pqxx::result r;

  try {
    r = w.exec(
        "INSERT INTO Team (name, state_id, color_id, wins, losses) VALUES (" +
        w.quote(name) + ", " + w.quote(state_id) + ", " + w.quote(color_id) +
        ", " + w.quote(wins) + ", " + w.quote(losses) + ");");
    w.commit();
  } catch (std::exception &e) {
    w.abort();
    std::cerr << "add_team: " << e.what() << std::endl;
    throw;
  }
  std::cerr << "Added team  " + name << std::endl; // remove
}

void add_state(pqxx::connection *C, std::string name) {
  pqxx::work w(*C);
  pqxx::result r;

  try {
    r = w.exec("INSERT INTO State (name) VALUES (" + w.quote(name) + ");");
    w.commit();
  } catch (std::exception &e) {
    w.abort();
    std::cerr << "add_state: " << e.what() << std::endl;
    throw;
  }
  std::cerr << "Added state  " + name << std::endl; // remove
}

void add_color(pqxx::connection *C, std::string name) {
  pqxx::work w(*C);
  pqxx::result r;

  try {
    r = w.exec("INSERT INTO Color (name) VALUES (" + w.quote(name) + ");");
    w.commit();
  } catch (std::exception &e) {
    w.abort();
    std::cerr << "add_color: " << e.what() << std::endl;
    throw;
  }
  std::cerr << "Added color " + name << std::endl; // remove
}

void query1(pqxx::connection *C, int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg, int use_rpg, int min_rpg,
            int max_rpg, int use_apg, int min_apg, int max_apg, int use_spg,
            double min_spg, double max_spg, int use_bpg, double min_bpg,
            double max_bpg) {}

void query2(pqxx::connection *C, std::string team_color) {
  pqxx::work w(*C);
  pqxx::result r;
}

void query3(pqxx::connection *C, std::string team_name) {}

void query4(pqxx::connection *C, std::string team_state,
            std::string team_color) {}

void query5(pqxx::connection *C, int num_wins) {}
