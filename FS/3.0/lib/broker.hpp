#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <zmqpp/zmqpp.hpp>
// toHex
#include <algorithm>
#include <stdexcept>
#include "json.hpp"

using json = nlohmann::json;


using namespace std;
using namespace zmqpp;

string getServers(string file) {
  stringstream ostrm;

  ifstream fin(file, ios::binary);
  ostrm << fin.rdbuf();
  fin.close();

  return ostrm.str();
}

string searchFreeServer(json servers) {
  for (auto& element : servers) {
    if (element["state"] == "off")
      return element["ip"];
  }

  return "alejo";
}
