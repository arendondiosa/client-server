#include "fs.h"

int main() {
	cout << "This is the client\n";

	context ctx;
	socket s(ctx, socket_type::req);

	cout << "Connecting to tcp port 5555\n";
	s.connect("tcp://localhost:5555");

	cout << "Sending a hello message!\n";
	string test = getFile("sirius.png");
	message m;
	// m << "Hello world server!!";
	m << test;

	s.send(m);

	cout << "Finished\n";
	return 0;
}
