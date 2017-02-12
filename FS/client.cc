#include "fs.h"
#include "json.hpp"

using json = nlohmann::json;

int main() {
	cout << "This is the client\n";

	context ctx;
	socket s(ctx, socket_type::req);

	cout << "Connecting to tcp port 5555\n";
	s.connect("tcp://localhost:5555");

	cout << "Sending a hello message!\n";
	string name = "export";
	string test = getFile(name);
	message m;
	json file;

	if (checkFileExist(test)) {
		file["user"] = "test";
		file["name"] = name;
		file["file"] = string_to_hex(test);
		//JSON to string, to tabs
		m << file.dump(2);
	} else m << "NO";

	s.send(m);

	cout << "Finished\n";
	return 0;
}
