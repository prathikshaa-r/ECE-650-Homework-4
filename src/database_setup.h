#ifndef __DATABASE_SETUP__
#define __DATABASE_SETUP__

#include <iostream>
#include <pqxx/pqxx>

#include "query_funcs.h"

void drop_tables(pqxx::connection *C);

void create_tables(pqxx::connection *C);

void populate_tables_from_src_files(pqxx::connection *C);

void update_color(pqxx::connection *C, std::istream &color_istream);
void update_state(pqxx::connection *C, std::istream &state_istream);
void update_team(pqxx::connection *C, std::istream &team_istream);
void update_player(pqxx::connection *C, std::istream &player_istream);

std::vector<std::string> read_line(std::string curr);

pqxx::result execute_stmt(pqxx::connection *C, std::string sql,
                          std::string desc);

#endif // __DATABASE_SETUP__
