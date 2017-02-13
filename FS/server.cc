#include "lib/fs.h"

int main() {
	cout << "This is the server\n";

	context ctx;
	socket s(ctx, socket_type::rep);

	cout << "Binding socket to tcp port 5555\n";
	s.bind("tcp://*:5555");
	system("mkdir files");
	json userFile;
	message m, response;
	string text;

	while (true) {
		cout << "Waiting for message to arrive!\n";
		s.receive(m);
		m >> text;

		if (text == "add") {
			cout << "ADDING FILE" << endl;
			response = "OK add";
			s.send(response);
			s.receive(m);
			m >> text;
			if (text == "NO") cout << "No existe el archivo";
			else {
				json file = json::parse(text);
				string user = file["user"], files = userFile[user].dump(2), fileName = file["name"];
				// system(("mkdir " + user).c_str());
				userFile = putFile(hex_to_string(file["file"]), fileName, user, userFile);
				cout << "Exist? ->" << logicFile(file["name"], files) << endl;
			}
			// cout << "Received " << text << endl;
			cout << userFile.dump(2) << endl;

			response = "ADDED FILE";
			s.send(response);
		} else if (text == "ls") {
			cout << "GET FILES" << endl;
			response = "OK ls";
			s.send(response);
			s.receive(m);
			m >> text;
			response = userFile[text].dump(2);
			s.send(response);
		} else if (text == "rm") {
			cout << "REMOVE FILE" << endl;
			response = "OK rm";
			s.send(response);
			s.receive(m);
			m >> text;
			response = userFile[text].dump(2);
			s.send(response);
	  } else {
			//RESPONSE
			response = "OK";
			s.send(response);
			cout << "Finished\n";
		}
	}
	return 0;
}
