#include <iostream>
#include <pqxx/pqxx>

#include "query_funcs.h"

// using namespace std;
// using namespace pqxx;

#ifndef _EXERCISER_
#define _EXERCISER_

void exercise(pqxx::connection *C);

pqxx::result execute_stmt(pqxx::connection *C, std::string sql,
                          std::string desc);
#endif //_EXERCISER_
