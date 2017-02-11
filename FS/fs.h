#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <zmqpp/zmqpp.hpp>

using namespace std;
using namespace zmqpp;

string getFile(string file) {
	stringstream ostrm;

	ifstream fin(file, ios::binary);
	ostrm << fin.rdbuf();
  fin.close();
	return ostrm.str();
}

void putFile(string file) {
  ofstream fout("copy.png");
  fout << file;
  fout.close();
}

bool checkFileExist(string file) {
  if(file != "") return true;
  else return false;
}
