#include "lib/fs.h"
#include "lib/json.hpp"

using json = nlohmann::json;

int main() {
  cout << "This is the Broker\n" << endl;
  context ctx;
  socket b(ctx, socket_type::rep);

  cout << "Binding socket to tcp port 6666\n";
  b.bind("tcp://*:6666");

  return 0;
}
