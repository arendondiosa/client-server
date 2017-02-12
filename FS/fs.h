#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <zmqpp/zmqpp.hpp>
// toHex
#include <algorithm>
#include <stdexcept>


using namespace std;
using namespace zmqpp;

string getFile(string file) {
	stringstream ostrm;

	ifstream fin(file, ios::binary);
	ostrm << fin.rdbuf();
  fin.close();
	return ostrm.str();
}

void putFile(string file, string name, string user) {
	system(("mkdir src/" + user).c_str());
  ofstream fout("src/" + user + "/" + name);
  fout << file;
  fout.close();
}

bool checkFileExist(string file) {
  if(file != "") return true;
  else return false;
}

// http://stackoverflow.com/questions/3381614/c-convert-string-to-hexadecimal-and-vice-versa
string string_to_hex(const string& input) {
  static const char* const lut = "0123456789ABCDEF";
  size_t len = input.length();

  std::string output;
  output.reserve(2 * len);
  for (size_t i = 0; i < len; ++i) {
    const unsigned char c = input[i];
    output.push_back(lut[c >> 4]);
    output.push_back(lut[c & 15]);
  }
  return output;
}

string hex_to_string(const string& input) {
  static const char* const lut = "0123456789ABCDEF";
  size_t len = input.length();
  if (len & 1) throw std::invalid_argument("odd length");

  std::string output;
  output.reserve(len / 2);
  for (size_t i = 0; i < len; i += 2) {
    char a = input[i];
    const char* p = std::lower_bound(lut, lut + 16, a);
    if (*p != a) throw std::invalid_argument("not a hex digit");

    char b = input[i + 1];
    const char* q = std::lower_bound(lut, lut + 16, b);
    if (*q != b) throw std::invalid_argument("not a hex digit");

    output.push_back(((p - lut) << 4) | (q - lut));
  }
  return output;
}
