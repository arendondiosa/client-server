#include <iostream>
#include <string>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;

int main() {
	cout << "This is the client\n";

	context ctx;
	socket s(ctx, socket_type::req);

	cout << "Connecting to tcp port 5555\n";
	// s.connect("tcp://localhost:5555");
	// Server different to localhost
	s.connect("tcp://192.168.8.66:5555"); //Gustavo's PC

	cout << "Sending a hello message!\n";
	message m;
	// m << "Alejandro E. Rendon :)!!";
	// Other messages
	m<< "sub" <<  56 << 904;
	s.send(m);

	message answer;
	s.receive(answer);
	int result;
	answer >> result;

	cout << "Answer from server " << result << endl;

	int i;
	cin >> i;
 	cout << "Finished\n";
	return 0;
}
