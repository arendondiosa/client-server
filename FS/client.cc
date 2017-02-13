#include "lib/fs.h"
#include "lib/json.hpp"

using json = nlohmann::json;

int main() {
	cout << "This is the client\n";

	context ctx;
	socket s(ctx, socket_type::req);

	cout << "Connecting to tcp port 5555\n";
	s.connect("tcp://localhost:5555");

	string name;
	string user;
	string command;

	cout << "Enter the username:  ";
	cin >> user;
	cout << "WELCOME " + user << endl;
	cout << "Enter a comand" << endl;

	while (true) {
		cout << ">> $  ";
		cin >> command;

		if (command == "add") {
			cin >> name;
			string test = getFile(name);
			message m;
			json file;

			if (checkFileExist(test)) {
				file["user"] = user;
				file["name"] = name;
				file["file"] = string_to_hex(test);
				//JSON to string, to tabs
				m << file.dump(2);
			} else m << "NO";

			s.send(m);

			//RESPONSE
			message response;
			s.receive(response);
			cout << "Finished\n";
		}
		else if (command == "ls") {
			cout << user + " files:" << endl;
		}
		else if (command == "exit") break;
		else cout << "Enter a correct command" << endl;


	}
	return 0;
}
