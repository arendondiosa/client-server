#include "lib/fs.h"

int main() {
	cout << "This is the server\n";

	context ctx;
	socket s(ctx, socket_type::rep);

	cout << "Binding socket to tcp port 5555\n";
	s.bind("tcp://*:5555");
	system("mkdir src");
	json userFile;

	while (true) {
		cout << "Waiting for message to arrive!\n";
		message m;
		s.receive(m);

		string text;
		m >> text;

		if (text == "NO") cout << "No existe el archivo";
		else {
			json file = json::parse(text);
			string user = file["user"];
			// system(("mkdir " + user).c_str());
			userFile = putFile(hex_to_string(file["file"]), file["name"], user, userFile);
		};
		// cout << "Received " << text << endl;
		cout << userFile.dump(2) << endl;

		//RESPONSE
		message response = "OK";
		s.send(response);
		cout << "Finished\n";
}
	return 0;
}
