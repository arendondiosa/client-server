#include <iostream>
#include <string>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;

bool isPrime(int x) {
	return false;
}

message messageHandler(message &m) {
	cout << "Parts -> " << m.parts() << endl;
	message response;
	string op;
	m >> op;
	int a, b;
	m >> a;
	m >> b;

	if(op == "add") {
		int r = a + b;
		response << r;
		return response;
	} else if(op == "sub") {
		int r = a - b;
		response << r;
		return response;
	} else if(op == "prime") {
		int a;
		m >> a;
		response << isPrime(a);
	}
	return response;
}

int main() {
	cout << "This is the server\n";

	context ctx;
	socket s(ctx, socket_type::rep);

	cout << "Binding socket to tcp port 5555\n";
	s.bind("tcp://*:5555");

	while(true) {
		cout << "Waiting for message to arrive!\n";
		message m;
		s.receive(m);
		message response = messageHandler(m);

		// cout << "Received " << operation << ", " << a << ", " << b << endl;
		//
		// message response;
		// // response << "OK";
		// response << (a + b);
		s.send(response);
	}
	cout << "Finished\n";
	return 0;
}
