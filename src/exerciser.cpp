/**
 * March 18, 2019
 */

#include "exerciser.h"

// using namespace std;
// using namespace pqxx;

void exercise(pqxx::connection *C) {
  query2(C, "Gold");
  query2(C, "Maroon");
  query3(C, "Duke");
  query3(C, "UNC");
  query4(C, "NC", "Gold");
  query4(C, "NC", "LightBlue");
  query4(C, "NC", "DarkBlue");
  query4(C, "NC", "Red");
  query5(C, 0);
  query5(C, 5);
  query5(C, 10);
  query5(C, 15);

  std::cout << std::endl;
  query1(C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  query1(C, 1, 20, 30, 1, 15, 20, 1, 0, 10, 1, 0, 10, 1, 0, 2.0, 1, 0, 1.5);
}
