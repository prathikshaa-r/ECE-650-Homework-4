#include "query_funcs.h"

// using namespace std;
// using namespace pqxx;

void add_player(pqxx::connection *C, int team_id, int jersey_num,
                std::string first_name, std::string last_name, int mpg, int ppg,
                int rpg, int apg, double spg, double bpg) {}

void add_team(pqxx::connection *C, std::string name, int state_id, int color_id,
              int wins, int losses) {}

void add_state(pqxx::connection *C, std::string name) {}

void add_color(pqxx::connection *C, std::string name) {}

void query1(pqxx::connection *C, int use_mpg, int min_mpg, int max_mpg,
            int use_ppg, int min_ppg, int max_ppg, int use_rpg, int min_rpg,
            int max_rpg, int use_apg, int min_apg, int max_apg, int use_spg,
            double min_spg, double max_spg, int use_bpg, double min_bpg,
            double max_bpg) {}

void query2(pqxx::connection *C, std::string team_color) {}

void query3(pqxx::connection *C, std::string team_name) {}

void query4(pqxx::connection *C, std::string team_state,
            std::string team_color) {}

void query5(pqxx::connection *C, int num_wins) {}
