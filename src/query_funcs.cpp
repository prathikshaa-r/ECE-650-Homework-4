#include "query_funcs.h"
#include <iomanip>

// using namespace std;
// using namespace pqxx;

void add_player(pqxx::connection *C, int team_id, int jersey_num,
                std::string first_name, std::string last_name, int mpg, int ppg,
                int rpg, int apg, double spg, double bpg) {
  pqxx::work w(*C);
  pqxx::result r;

  // std::cout << "team_id:\t" << team_id << "\njersey_num:\t" << jersey_num
  //           << "\nfirst_name:\t" << first_name << "\nlast_name:\t" <<
  //           last_name
  //           << "\nmpg:\t" << mpg << "\nppg:\t" << ppg << "\nrpg:\t" << rpg
  //           << "\napg:\t" << apg << "\nspg:\t" << spg << "\nbpg:\t" << bpg
  //           << std::endl;

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
  // std::cerr << "Added player  " + first_name + " " + last_name
  //           << std::endl; // remove
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
  //  std::cerr << "Added team  " + name << std::endl; // remove
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
  //  std::cerr << "Added state  " + name << std::endl; // remove
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
  //  std::cerr << "Added color " + name << std::endl; // remove
}

void query1(pqxx::connection *C, int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg, int use_rpg, int min_rpg,
            int max_rpg, int use_apg, int min_apg, int max_apg, int use_spg,
            double min_spg, double max_spg, int use_bpg, double min_bpg,
            double max_bpg) {
  std::cout << std::left << std::setw(10) << "PLAYER_ID" << std::left
            << std::setw(10) << "TEAM_ID" << std::left << std::setw(15)
            << "UNIFORM_NUM" << std::left << std::setw(20) << "FIRST_NAME"
            << std::left << std::setw(20) << "LAST_NAME" << std::left
            << std::setw(5) << "MPG" << std::left << std::setw(5) << "PPG"
            << std::left << std::setw(5) << "RPG" << std::left << std::setw(5)
            << "APG" << std::left << std::setw(5) << "SPG" << std::left
            << std::setw(5) << "BPG" << std::endl;

  pqxx::nontransaction n(*C);
  size_t not_first_cond = 0;
  std::string sql = "SELECT * FROM Player";
  std::string cond = " WHERE ";
  if (use_mpg) {
    cond += "mpg>=" + n.quote(min_mpg) + " AND mpg<=" + n.quote(max_mpg);
    not_first_cond++;
  }
  if (use_ppg) {
    if (not_first_cond) {
      cond += " AND ";
    }
    cond += "ppg>=" + n.quote(min_ppg) + " AND ppg<=" + n.quote(max_ppg);
    not_first_cond++;
  }
  if (use_rpg) {
    if (not_first_cond) {
      cond += " AND ";
    }
    cond += "rpg>=" + n.quote(min_rpg) + " AND rpg<=" + n.quote(max_rpg);
    not_first_cond++;
  }
  if (use_apg) {
    if (not_first_cond) {
      cond += " AND ";
    }
    cond += "apg>=" + n.quote(min_apg) + " AND apg<=" + n.quote(max_apg);
    not_first_cond++;
  }
  if (use_spg) {
    if (not_first_cond) {
      cond += " AND ";
    }
    cond += "spg>=" + n.quote(min_spg) + " AND spg<=" + n.quote(max_spg);
    not_first_cond++;
  }
  if (use_bpg) {
    if (not_first_cond) {
      cond += " AND ";
    }
    cond += "bpg>=" + n.quote(min_bpg) + " AND bpg<=" + n.quote(max_bpg);
    not_first_cond++;
  }
  if (not_first_cond) {
    //    std::cout << "not_first_cond true: " << not_first_cond << std::endl;
    sql += cond;
  }
  sql += ";";
  try {
    pqxx::result r(n.exec(sql));

    for (pqxx::result::const_iterator iter = r.begin(); iter != r.end();
         iter++) {
      std::cout << std::left << std::setw(10) << iter[0].as<int>() // player_id
                << std::left << std::setw(10) << iter[1].as<int>() // team_id
                << std::left << std::setw(15) << iter[2].as<int>() // jersey_num
                << std::left << std::setw(20)
                << iter[3].as<std::string>() // first_name
                << std::left << std::setw(20)
                << iter[4].as<std::string>()                      // last_name
                << std::left << std::setw(5) << iter[5].as<int>() // mpg
                << std::left << std::setw(5) << iter[6].as<int>() // ppg
                << std::left << std::setw(5) << iter[7].as<int>() // rpg
                << std::left << std::setw(5) << iter[8].as<int>() // apg
                << std::left << std::setw(5) << iter[9].as<double>()  // spg
                << std::left << std::setw(5) << iter[10].as<double>() // bpg
                << std::endl;
    }
  } catch (std::exception &e) {
    std::cerr << "query5: " << e.what() << std::endl;
    throw;
  }
}

void query2(pqxx::connection *C, std::string team_color) {
  std::cout << std::left << std::setw(20) << "NAME" << std::endl;

  pqxx::nontransaction n(*C);
  try {
    pqxx::result r(n.exec("SELECT Team.name FROM Team, Color WHERE "
                          "Team.color_id=Color.color_id AND color.name=" +
                          n.quote(team_color) + ";"));

    for (pqxx::result::const_iterator iter = r.begin(); iter != r.end();
         iter++) {
      std::cout << std::left << std::setw(20) << iter[0].as<std::string>()
                << std::endl;
    }

  } catch (std::exception &e) {
    std::cerr << "query2: " << e.what() << std::endl;
    throw;
  }
  //  std::cerr << "Queried teams with color " + team_color << std::endl; //
  //  remove
}

void query3(pqxx::connection *C, std::string team_name) {
  std::cout << std::left << std::setw(20) << "FIRST_NAME" << std::left
            << std::setw(20) << "LAST_NAME" << std::endl;

  pqxx::nontransaction n(*C);
  try {
    pqxx::result r(
        n.exec("SELECT Player.first_name, Player.last_name FROM Player, Team "
               "WHERE Player.team_id = Team.team_id AND team.name = " +
               n.quote(team_name) + ";"));

    for (pqxx::result::const_iterator iter = r.begin(); iter != r.end();
         iter++) {
      std::cout << std::left << std::setw(20) << iter[0].as<std::string>()
                << std::left << std::setw(20) << iter[1].as<std::string>()
                << std::endl;
    }

  } catch (std::exception &e) {
    std::cerr << "query3: " << e.what() << std::endl;
    throw;
  }
  // std::cerr << "Queried players in team " + team_name +
  //                  " based on descending order of ppg"
  //           << std::endl; // remove
}

void query4(pqxx::connection *C, std::string team_state,
            std::string team_color) {
  std::cout << std::left << std::setw(20) << "FIRST_NAME" << std::left
            << std::setw(20) << "LAST_NAME" << std::left << std::setw(20)
            << "UNIFORM_NUM" << std::endl;

  pqxx::nontransaction n(*C);
  try {

    pqxx::result r(n.exec("SELECT Player.first_name, Player.last_name, "
                          "Player.uniform_num FROM Player, "
                          "Color, Team, State "
                          "WHERE Player.team_id=Team.team_id AND "
                          "Team.state_id=State.state_id AND "
                          "Team.color_id=Color.color_id "
                          "AND State.name=" +
                          n.quote(team_state) +
                          " AND Color.name=" + n.quote(team_color) + ";"));

    for (pqxx::result::const_iterator iter = r.begin(); iter != r.end();
         iter++) {
      std::cout << std::left << std::setw(20) << iter[0].as<std::string>()
                << std::left << std::setw(20) << iter[1].as<std::string>()
                << std::left << std::setw(20) << iter[2].as<std::string>()
                << std::endl;
    }

  } catch (std::exception &e) {
    std::cerr << "query4: " << e.what() << std::endl;
    throw;
  }
  // std::cerr << "Queried players from state " + team_state + " and team color
  // " +
  //                  team_color
  //           << std::endl; // remove
}

void query5(pqxx::connection *C, int num_wins) {
  std::cout << std::left << std::setw(20) << "FIRST_NAME" << std::left
            << std::setw(20) << "LAST_NAME" << std::left << std::setw(20)
            << "TEAM_NAME" << std::left << std::setw(20) << "WINS" << std::endl;

  pqxx::nontransaction n(*C);
  try {
    pqxx::result r(n.exec(
        "SELECT Player.first_name, Player.last_name, Team.name, Team.wins "
        "FROM Player, Team "
        "WHERE Player.team_id=Team.team_id AND Team.wins>" +
        n.quote(num_wins) + ";"));

    for (pqxx::result::const_iterator iter = r.begin(); iter != r.end();
         iter++) {
      std::cout << std::left << std::setw(20) << iter[0].as<std::string>()
                << std::left << std::setw(20) << iter[1].as<std::string>()
                << std::left << std::setw(20) << iter[2].as<std::string>()
                << std::left << std::setw(20) << iter[3].as<int>() << std::endl;
    }
  } catch (std::exception &e) {
    std::cerr << "query5: " << e.what() << std::endl;
    throw;
  }
}
