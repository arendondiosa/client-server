#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <zmqpp/zmqpp.hpp>
// toHex
#include <algorithm>
#include <stdexcept>
#include "json.hpp"

#define CHUNK 50

using json = nlohmann::json;


using namespace std;
using namespace zmqpp;

string getFile(string fileName) {
  stringstream ostrm;

  ifstream fin(fileName, ios::binary);
  ostrm << fin.rdbuf();
  fin.close();

  FILE *file = NULL;
  unsigned char buffer[CHUNK];  // array of bytes, not pointers-to-bytes
  size_t bytesRead = 0;

  file = fopen(fileName.c_str(), "rb");

  if (file != NULL) {
    // read up to sizeof(buffer) bytes
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
      cout << "-----------------Chunk" << endl;
      cout << string(buffer, find(buffer, buffer + bytesRead, '\0')) << endl;
      // cout << bytesRead << endl;
      // cout << string (buffer, bytesRead) << endl;
    }
  }

  cout << endl;
  cout << "-----------------FILE" << endl;
  cout << ostrm.str() << endl;
  // return ostrm.str();
  return ostrm.str();
}

string getFileServer(string user, string file) {
  stringstream ostrm;

  ifstream fin(user + "/" + file, ios::binary);
  ostrm << fin.rdbuf();
  fin.close();
  return ostrm.str();
}

string getUserfile(string user, string file) {
  stringstream ostrm;

  ifstream fin("files/" + user + "/" + file, ios::binary);
  ostrm << fin.rdbuf();
  fin.close();
  return ostrm.str();
}

bool checkFileExist(string file) {
  if(file != "") return true;
  else return false;
}

bool logicFile(string fileName, string files) {
  json list = json::parse(files);
  for (auto& element : list) {
    if (element == fileName)
      return true;
  }
  return false;
}

json deleteUserFile(string user, string fileName, json files) {
  system(("rm files/" + user + "/" + fileName).c_str());

  json aux;
  aux[user] = files[user];
  files[user] = {};

  for (auto& element : aux[user]) {
    if (element != fileName) {
      cout << element << endl;
      files[user].push_back(element);
    }
  }
  return files;
}

json putFile(string file, string name, string user, json userFile, string files) {
  system(("mkdir files/" + user).c_str());
  ofstream fout("files/" + user + "/" + name);
  fout << file;
  fout.close();

  if (!logicFile(name, files))
    userFile[user].push_back(name);
  // userFile["file"] = {name};
  // vector<string> files;
  // if (!logicFile(name, files))
  cout << userFile[user] << endl;

  return userFile;
}

void putFileClient(string name, string file) {
  ofstream fout("downloads/" + name);
  fout << file;
  fout.close();
}

// string loadDB() {
//   stringstream DB;
//   ifstream DBtoLoad;
//   DBtoLoad.open("DB.abc");
//   DBtoLoad >> DB;
//   DBtoLoad.close();
//
//   return DB.c_str();
// }

void saveDB(string DBtoSave) {
  ofstream DB;
  DB.open("DB.abc");
  DB << DBtoSave;
  DB.close();
}

// Encrypt
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
